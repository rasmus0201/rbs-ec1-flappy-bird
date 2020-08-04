#include "mbed.h"
#include "stm32746g_discovery_lcd.h"
#include "stm32746g_discovery_ts.h"
#include "ProgramState.h"
#include "InteractiveButton.h"
#include "Bird.h"
#include "Pipe.h"

#define SCREEN_HEIGHT 272
#define SCREEN_WIDTH 480

InterruptIn flyBtn(D2);
DigitalOut led(D3);

Bird flappy;

void fly_btn_activator_rise()
{
    flappy.Up();
}

void init_lcd()
{
    BSP_LCD_Init();
    BSP_LCD_LayerDefaultInit(LTDC_ACTIVE_LAYER, LCD_FB_START_ADDRESS);
    BSP_LCD_SelectLayer(LTDC_ACTIVE_LAYER);
}

bool init_touch()
{
    uint8_t status = BSP_TS_Init(BSP_LCD_GetXSize(), BSP_LCD_GetYSize());
    if (status != TS_OK) {
        BSP_LCD_Clear(LCD_COLOR_RED);
        BSP_LCD_SetBackColor(LCD_COLOR_RED);
        BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
        BSP_LCD_DisplayStringAt(0, LINE(5), (uint8_t *)"TOUCHSCREEN FAILED", CENTER_MODE);

        return false;
    }

    return true;
}

unsigned number_of_digits(unsigned i)
{
    return i > 0 ? (int) log10 ((double) i) + 1 : 1;
}

void show_start(ProgramState *state, InteractiveButton btn)
{
    BSP_LCD_SetFont(&Font20);

    BSP_LCD_Clear(LCD_COLOR_GREEN);
    BSP_LCD_SetBackColor(LCD_COLOR_GREEN);
    BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
    BSP_LCD_DisplayStringAt(0, LINE(4), (uint8_t *)"Press play to start", CENTER_MODE);

    BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
    BSP_LCD_SetTextColor(LCD_COLOR_BLACK);

    BSP_LCD_FillRect(btn.GetX(), btn.GetY(), btn.GetWidth(), btn.GetHeight());
    
    BSP_LCD_SetFont(&Font16);
    BSP_LCD_SetBackColor(LCD_COLOR_TRANSPARENT);
    BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
    BSP_LCD_DisplayStringAt(0, btn.GetY() + 16, (uint8_t *)"PLAY", CENTER_MODE);

    BSP_LCD_SetFont(&Font20);
}


void show_gameover(ProgramState *state, InteractiveButton btn)
{
    int score = state->gameScore;
    
    uint8_t scoreStr[13 + number_of_digits(score)];
    BSP_LCD_SetFont(&Font20);
    sprintf((char *)scoreStr, "Your score: %d", score);

    BSP_LCD_Clear(LCD_COLOR_RED);
    BSP_LCD_SetBackColor(LCD_COLOR_RED);
    BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
    BSP_LCD_DisplayStringAt(0, LINE(3), (uint8_t *)"GAMEOVER", CENTER_MODE);
    BSP_LCD_DisplayStringAt(0, LINE(4), (uint8_t *)scoreStr, CENTER_MODE);

    BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
    BSP_LCD_SetTextColor(LCD_COLOR_BLACK);

    BSP_LCD_FillRect(btn.GetX(), btn.GetY(), btn.GetWidth(), btn.GetHeight());
    
    BSP_LCD_SetFont(&Font16);
    BSP_LCD_SetBackColor(LCD_COLOR_TRANSPARENT);
    BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
    BSP_LCD_DisplayStringAt(0, btn.GetY() + 16, (uint8_t *)"RESTART", CENTER_MODE);

    BSP_LCD_SetFont(&Font20);
}

int main()
{
    srand(time(NULL));

    init_lcd();

    if (!init_touch()) {
        exit(-1);
    }

    led.write(0);

    BSP_LCD_Clear(LCD_COLOR_GREEN);
    BSP_LCD_SetBackColor(LCD_COLOR_GREEN);
    BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
    BSP_LCD_DisplayStringAt(0, LINE(5), (uint8_t *)"Welcome to flappy bird", CENTER_MODE);
    BSP_LCD_SetFont(&Font20);
    HAL_Delay(2000);

    BSP_LCD_Clear(LCD_COLOR_GREEN);

    flyBtn.rise(&fly_btn_activator_rise);

    ProgramState state;

    flappy.Init(
        state.flappyXPos,
        state.flappyYPos,
        state.flappySize,
        state.gravity,
        state.lift
    );

    int pipeIndex = 0;
    Pipe *pipes[state.pipeCount];

    pipes[pipeIndex++] = new Pipe(
        state.pipeWidth,
        state.pipeSpacing,
        state.pipeSpeed
    );
    
    for (int i = 1; i < state.pipeCount; i++) {
        pipes[i] = nullptr;
    }

    InteractiveButton startBtn(
        int(SCREEN_WIDTH/2 - 55),
        int(SCREEN_HEIGHT/2),
        100,
        50
    );

    InteractiveButton restartBtn(
        int(SCREEN_WIDTH/2 - 55),
        int(SCREEN_HEIGHT/2),
        100,
        50
    );

    TS_StateTypeDef screenState;

    while(1) {
        BSP_TS_GetState(&screenState);
        
        // START STATE
        if (state.programState == 0) {
            if (state.stateChanged) {
                show_start(&state, startBtn);

                state.stateChanged = false;
            }

            if (startBtn.IsPressed()) {
                state.programState = 1;
                state.gameScore = 0;

                state.stateChanged = true;
            }
        }

        // PLAY STATE
        if (state.programState == 1) {
            BSP_LCD_Clear(LCD_COLOR_GREEN);

            // Lift the bird if there is a touch on screen
            if (screenState.touchDetected) {
                flappy.Up();
            }

            for(int i = 0; i < state.pipeCount; i++) {
                if (pipes[i] == nullptr) {
                    continue;
                }

                pipes[i]->Draw();
                pipes[i]->Update();

                // Check if the bird hit the pipe
                if (pipes[i]->Collides(flappy)) {
                    state.programState = 2;
                    state.frameCount = 0;
                    state.stateChanged = true;
                    state.gameScore--; // They did not get through, so to compensate for the follwing ++ we decrement here
                    
                    pipeIndex = 0;
                    pipes[pipeIndex++] = new Pipe(
                        state.pipeWidth,
                        state.pipeSpacing,
                        state.pipeSpeed
                    );

                    for (int i = 1; i < state.pipeCount; i++) {
                        pipes[i] = nullptr;
                    }

                    flappy.Init(
                        state.flappyXPos,
                        state.flappyYPos,
                        state.flappySize,
                        state.gravity,
                        state.lift
                    );

                    led.write(1);
                }
            }
            
            // Game-over if bird is below screen
            if ((flappy.GetY() + flappy.GetSize()) >= SCREEN_HEIGHT) {
                state.programState = 2;
                state.frameCount = 0;
                state.stateChanged = true;
                
                pipeIndex = 0;
                pipes[pipeIndex++] = new Pipe(
                    state.pipeWidth,
                    state.pipeSpacing,
                    state.pipeSpeed
                );

                for (int i = 1; i < state.pipeCount; i++) {
                    pipes[i] = nullptr;
                }

                flappy.Init(
                    state.flappyXPos,
                    state.flappyYPos,
                    state.flappySize,
                    state.gravity,
                    state.lift
                );

                led.write(1);
            }

            flappy.Update();
            flappy.Draw();

            // Add more pipes every x frames
            if (state.frameCount % state.pipeSpawnFrame == 0 && state.frameCount != 0) {
                state.gameScore += 1;
                
                pipes[pipeIndex] = new Pipe(
                    state.pipeWidth,
                    state.pipeSpacing,
                    state.pipeSpeed
                );

                if (pipeIndex < (state.pipeCount - 1)) {
                    pipeIndex++;
                } else {
                    pipeIndex = 0;
                }
            }

            state.frameCount++;
        }

        // GAMEOVER STATE
        if (state.programState == 2) {
            if (state.stateChanged) {
                show_gameover(&state, restartBtn);

                state.stateChanged = false;
            }

            if (restartBtn.IsPressed()) {
                state.programState = 1;
                state.gameScore = 0;

                state.stateChanged = true;
                led.write(0);
            }
        }

        HAL_Delay(state.frameDelay);
    }
}
