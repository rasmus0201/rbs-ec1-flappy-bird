#include "mbed.h"
#include "stm32746g_discovery_lcd.h"
#include "stm32746g_discovery_ts.h"
#include "Bird.h"
#include "Pipe.h"
#include "GameData.h"
#include "GameEngine.h"
#include "StartState.h"

InterruptIn fly_btn(D2);
DigitalOut builtin_led(LED1);

void fly_btn_activator_rise(GameData gameData)
{
    gameData.flappy.Up();
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

void show_gameover(GameData gameData) {
    uint8_t scoreStr[13 + number_of_digits(gameData.gameScore)];
    BSP_LCD_SetFont(&Font20);
    sprintf((char *)scoreStr, "Your score: %d", gameData.gameScore);

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

    if (gameData.screenState.touchDetected) {
        bool pressed = true;

        if (!(gameData.screenState.touchX[0] > btnX && gameData.screenState.touchX[0] < (btnX + btnWidth))) {
            pressed = false;
        }
        
        if (!(gameData.screenState.touchY[0] > btnY && gameData.screenState.touchY[0] < (btnY + btnHeight))) {
            pressed = false;
        }

        if (pressed) {
            gameData.programState = 1;
            gameData.gameScore = 0;
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
    BSP_LCD_DisplayStringAt(
        0,
        LINE(5),
        (uint8_t *)"Welcome to flappy bird",
        CENTER_MODE
    );
    BSP_LCD_SetFont(&Font20);
    HAL_Delay(2000);
    BSP_LCD_Clear(LCD_COLOR_GREEN);

    GameEngine game;
    GameData gameData;

    gameData.flappy.Init(
        gameData.flappyXPos,
        gameData.flappyYPos,
        gameData.flappySize,
        gameData.gravity,
        gameData.lift
    );

    fly_btn.rise(&fly_btn_activator_rise(gameData));

    game.Init(gameData);

    // Load the start state
    game.ChangeState(StartState::Instance());

    // Main loop
    while (game.Running()) {
        game.HandleEvents();
        game.Update();
        game.Draw();
    }

    game.Cleanup();

    int pipeIndex = 0;
    Pipe *pipes[gameData.pipeCount];

    pipes[pipeIndex++] = new Pipe(
        gameData.pipeWidth,
        gameData.pipeSpacing,
        gameData.pipeSpeed
    );
    
    for (int i = 1; i < gameData.pipeCount; i++) {
        pipes[i] = nullptr;
    }

    while(1) {
        gameData.Update();

        if (gameData.programState == 0) {
            // show_start
        }

        if (gameData.programState == 1) {
            BSP_LCD_Clear(LCD_COLOR_GREEN);

            if (gameData.screenState.touchDetected) {
                gameData.flappy.Up();
            }

            for(int i = 0; i < gameData.pipeCount; i++) {
                if (pipes[i] == nullptr) {
                    continue;
                }

                pipes[i]->Draw();
                pipes[i]->Update();

                if (pipes[i]->Collides(gameData.flappy)) {
                    gameData.programState = 2;
                    pipeIndex = 0;
                    pipes[pipeIndex++] = new Pipe(
                        gameData.pipeWidth,
                        gameData.pipeSpacing,
                        gameData.pipeSpeed
                    );

                    for (int i = 1; i < gameData.pipeCount; i++) {
                        pipes[i] = nullptr;
                    }

                    gameData.flappy.Init(
                        gameData.flappyXPos,
                        gameData.flappyYPos,
                        gameData.flappySize,
                        gameData.gravity,
                        gameData.lift
                    );
                }
            }

            gameData.flappy.Update();
            gameData.flappy.Draw();

            if (
                gameData.frameCount % gameData.pipeSpawnFrame == 0 && gameData.frameCount != 0
            ) {
                gameData.gameScore += 1;
                
                pipes[pipeIndex] = new Pipe(
                    gameData.pipeWidth,
                    gameData.pipeSpacing,
                    gameData.pipeSpeed
                );

                if (pipeIndex < (gameData.pipeCount - 1)) {
                    pipeIndex++;
                } else {
                    pipeIndex = 0;
                }
            }

            gameData.frameCount++;
        }

        if (gameData.programState == 2) {
            gameData.frameCount = 0;
            gameData.gameScore -= 1;

            show_gameover(gameData);
        }

        HAL_Delay(gameData.frameDelay);
    }
}


