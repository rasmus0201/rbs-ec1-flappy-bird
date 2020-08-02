#include "mbed.h"
#include "stm32746g_discovery_lcd.h"
#include "stm32746g_discovery_ts.h"
#include "bird.h"
#include "pipe.h"

InterruptIn fly_btn(D2);
DigitalOut builtin_led(LED1);

Bird flappy;
// int PROGRAM_STATE = 0;
// int GAME_SCORE = 0;

class ProgramState
{
    public:
        ProgramState() {
            BSP_TS_GetState(&this->screenState);
            
            this->programState = 0;
            this->gameScore = 0;
            this->frameCount = 0;
            this->frameDelay = 50;
            this->pipeCount = 16;
            this->pipeSpawnFrame = 40;
            this->pipeSpacing = 80;
            this->pipeSpeed = 5;
            this->pipeWidth = 40;
            this->flappyXPos = 160;
            this->flappyYPos = 136;
            this->gravity = 0.8;
            this->lift = -5;
            this->flappySize = 10;
        }

        void UpdateScreenState() {
            BSP_TS_GetState(&this->screenState);
        }
    
    public:
        int programState;
        int gameScore;
        TS_StateTypeDef screenState;
        int frameCount;
        int frameDelay;
        int pipeCount;
        int pipeSpawnFrame;
        int pipeSpacing;
        int pipeSpeed;
        int pipeWidth;
        int flappyXPos;
        int flappyYPos;
        float gravity;
        float lift;
        int flappySize;
};

void fly_btn_activator_rise()
{
    flappy.Up();
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

unsigned number_of_digits(unsigned i)
{
    return i > 0 ? (int) log10 ((double) i) + 1 : 1;
}

void show_start(ProgramState state) {
    BSP_LCD_SetFont(&Font20);

    BSP_LCD_Clear(LCD_COLOR_GREEN);
    BSP_LCD_SetBackColor(LCD_COLOR_GREEN);
    BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
    BSP_LCD_DisplayStringAt(0, LINE(4), (uint8_t *)"Press play to start", CENTER_MODE);

    BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
    BSP_LCD_SetTextColor(LCD_COLOR_BLACK);

    int btnX = int(480/2 - 55);
    int btnY = int(272/2);
    int btnWidth = 100;
    int btnHeight = 50;
    BSP_LCD_FillRect(btnX, btnY, btnWidth, btnHeight);
    
    BSP_LCD_SetFont(&Font16);
    BSP_LCD_SetBackColor(LCD_COLOR_TRANSPARENT);
    BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
    BSP_LCD_DisplayStringAt(0, btnY + 16, (uint8_t *)"PLAY", CENTER_MODE);

    BSP_LCD_SetFont(&Font20);

    if (state.screenState.touchDetected) {
        bool pressed = true;

        if (!(state.screenState.touchX[0] > btnX && state.screenState.touchX[0] < (btnX + btnWidth))) {
            pressed = false;
        }
        
        if (!(state.screenState.touchY[0] > btnY && state.screenState.touchY[0] < (btnY + btnHeight))) {
            pressed = false;
        }

        if (pressed) {
            state.programState = 1;
            state.gameScore = 0;
        }
    }
}

void show_gameover(ProgramState state) {
    uint8_t scoreStr[13 + number_of_digits(state.gameScore)];
    BSP_LCD_SetFont(&Font20);
    sprintf((char *)scoreStr, "Your score: %d", state.gameScore);

    BSP_LCD_Clear(LCD_COLOR_RED);
    BSP_LCD_SetBackColor(LCD_COLOR_RED);
    BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
    BSP_LCD_DisplayStringAt(0, LINE(3), (uint8_t *)"GAMEOVER", CENTER_MODE);
    BSP_LCD_DisplayStringAt(0, LINE(4), (uint8_t *)scoreStr, CENTER_MODE);

    BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
    BSP_LCD_SetTextColor(LCD_COLOR_BLACK);

    int btnX = int(480/2 - 55); // 185 - 285
    int btnY = int(272/2); // 136 - 186
    int btnWidth = 100;
    int btnHeight = 50;
    BSP_LCD_FillRect(btnX, btnY, btnWidth, btnHeight);
    
    BSP_LCD_SetFont(&Font16);
    BSP_LCD_SetBackColor(LCD_COLOR_TRANSPARENT);
    BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
    BSP_LCD_DisplayStringAt(0, btnY + 16, (uint8_t *)"RESTART", CENTER_MODE);

    BSP_LCD_SetFont(&Font20);

    if (state.screenState.touchDetected) {
        bool pressed = true;

        if (!(state.screenState.touchX[0] > btnX && state.screenState.touchX[0] < (btnX + btnWidth))) {
            pressed = false;
        }
        
        if (!(state.screenState.touchY[0] > btnY && state.screenState.touchY[0] < (btnY + btnHeight))) {
            pressed = false;
        }

        if (pressed) {
            state.programState = 1;
            state.gameScore = 0;
        }
    }
}

int main()
{
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

    ProgramState state;

    // TS_StateTypeDef TS_State;
    // int FRAME_COUNT = 0;
    // int FRAME_DELAY = 50;
    // int PIPE_COUNT = 16;
    // int PIPE_SPAWN_FRAME = 50;
    // int PIPE_SPACING = 90;
    // int PIPE_SPEED = 5;
    // int PIPE_WIDTH = 40;

    // int FLAPPY_X_POS = 160;
    // int FLAPPY_Y_POS = 136;
    // float GRAVITY = 0.7;
    // float LIFT = -5;
    // int FLAPPY_SIZE = 10;

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

    while(1) {
        state.UpdateScreenState();

        if (state.programState == 0) {
            show_start(state);
        }

        if (state.programState == 1) {
            BSP_LCD_Clear(LCD_COLOR_GREEN);

            if (state.screenState.touchDetected) {
                flappy.Up();
            }

            for(int i = 0; i < state.pipeCount; i++) {
                if (pipes[i] == nullptr) {
                    continue;
                }

                pipes[i]->Draw();
                pipes[i]->Update();

                if (pipes[i]->Collides(flappy)) {
                    state.programState = 2;
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

        if (state.programState == 2) {
            state.frameCount = 0;
            state.gameScore -= 1;

            show_gameover(state);
        }

        HAL_Delay(state.frameDelay);
    }
}

