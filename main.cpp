#include "mbed.h"
#include "stm32746g_discovery_lcd.h"
#include "stm32746g_discovery_ts.h"
#include "my_utils.h"
#include "program_state.h"
#include "interactive_button.h"
#include "bird.h"
#include "pipe.h"

InterruptIn fly_btn(D2);
DigitalOut builtin_led(LED1);
DigitalOut statusLed(D3);

ProgramState state;
Bird flappy;

void fly_btn_activator_rise()
{
    if (state.programState == 1) {
        statusLed.write(1);
        flappy.Up();
    }
}

void init_lcd() {
    BSP_LCD_Init();
    BSP_LCD_LayerDefaultInit(LTDC_ACTIVE_LAYER, LCD_FB_START_ADDRESS);
    BSP_LCD_SelectLayer(LTDC_ACTIVE_LAYER);
}

bool init_touch() {
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

void show_start(ProgramState* state, InteractiveButton btn) {
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

void show_gameover(ProgramState* state, InteractiveButton btn) {
    int actualScore = state->gameScore - 1;
    uint8_t scoreStr[13 + number_of_digits(actualScore)];
    BSP_LCD_SetFont(&Font20);
    sprintf((char *)scoreStr, "Your score: %d", actualScore);

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
    statusLed.write(0);
    srand(time(NULL));
    init_lcd();

    if (!init_touch()) {
        exit(-1);
    }

    BSP_LCD_Clear(LCD_COLOR_GREEN);
    BSP_LCD_SetBackColor(LCD_COLOR_GREEN);
    BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
    BSP_LCD_DisplayStringAt(0, LINE(5), (uint8_t *)"Welcome to flappy bird", CENTER_MODE);
    BSP_LCD_SetFont(&Font20);
    HAL_Delay(2000);

    BSP_LCD_Clear(LCD_COLOR_GREEN);

    fly_btn.rise(&fly_btn_activator_rise);

    InteractiveButton startBtn(
        int(480/2 - 55), // 185 - 285
        int(272/2), // 136 - 186
        100,
        50
    );

    InteractiveButton restartBtn(
        int(480/2 - 55), // 185 - 285
        int(272/2), // 136 - 186
        100,
        50
    );

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

    bool needsRedraw = true;
    TS_StateTypeDef TS_State;

    while(1) {
        BSP_TS_GetState(&TS_State);
        statusLed.write(!statusLed.read());
        
        state.UpdateScreenState();

        if (state.programState == 0) {
            printf("draw start");
            BSP_LCD_Clear(LCD_COLOR_GREEN);
            show_start(&state, startBtn);

            if (startBtn.IsPressed(&state)) {
                printf("startbtn is pressed");
                state.programState = 1;
                state.gameScore = 0;
            }
        }

        if (state.programState == 1) {
            BSP_LCD_Clear(LCD_COLOR_GREEN);

            if (state.screenState.touchDetected) {
                statusLed.write(1);
                flappy.Up();
            }

            for(int i = 0; i < state.pipeCount; i++) {
                if (pipes[i] == nullptr) {
                    continue;
                }

                pipes[i]->Draw();
                pipes[i]->Update();

                if (pipes[i]->Collides(flappy)) {
                    needsRedraw = true;
                    state.programState = 2;
                    state.frameCount = 0;
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
                }
            }

            if (state.programState == 1) {
                flappy.Update();
                flappy.Draw();

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
        }

        if (state.programState == 2) {
            if (needsRedraw) {
                BSP_LCD_Clear(LCD_COLOR_RED);
                show_gameover(&state, restartBtn);
                needsRedraw = false;
            }

            if (restartBtn.IsPressed(&state)) {
                state.programState = 1;
                state.gameScore = 0;

                needsRedraw = true;
            }
        }

        // HAL_Delay(state.frameDelay);
        // wait_us(100 * 1000);
        HAL_Delay(100);
    }
}


