#include "mbed.h"
#include "stm32746g_discovery_lcd.h"
#include "stm32746g_discovery_ts.h"
#include "Bird.h"
#include "Pipe.h"
#include "GameData.h"
#include "GameEngine.h"
#include "StartState.h"

GameData gameData;
InterruptIn fly_btn(D2);
DigitalOut builtin_led(LED1);

void fly_btn_activator_rise()
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

    gameData.flappy.Init(
        gameData.flappyXPos,
        gameData.flappyYPos,
        gameData.flappySize,
        gameData.gravity,
        gameData.lift
    );

    fly_btn.rise(&fly_btn_activator_rise);

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

    return 0;

    // int pipeIndex = 0;
    // Pipe *pipes[gameData.pipeCount];

    // pipes[pipeIndex++] = new Pipe(
    //     gameData.pipeWidth,
    //     gameData.pipeSpacing,
    //     gameData.pipeSpeed
    // );
    
    // for (int i = 1; i < gameData.pipeCount; i++) {
    //     pipes[i] = nullptr;
    // }

    // while(1) {
    //     gameData.Update();

    //     if (gameData.programState == 0) {
    //         // show_start
    //     }

    //     if (gameData.programState == 1) {
    //         BSP_LCD_Clear(LCD_COLOR_GREEN);

    //         if (gameData.screenState.touchDetected) {
    //             gameData.flappy.Up();
    //         }

    //         for(int i = 0; i < gameData.pipeCount; i++) {
    //             if (pipes[i] == nullptr) {
    //                 continue;
    //             }

    //             pipes[i]->Draw();
    //             pipes[i]->Update();

    //             if (pipes[i]->Collides(gameData.flappy)) {
    //                 gameData.programState = 2;
    //                 pipeIndex = 0;
    //                 pipes[pipeIndex++] = new Pipe(
    //                     gameData.pipeWidth,
    //                     gameData.pipeSpacing,
    //                     gameData.pipeSpeed
    //                 );

    //                 for (int i = 1; i < gameData.pipeCount; i++) {
    //                     pipes[i] = nullptr;
    //                 }

    //                 gameData.flappy.Init(
    //                     gameData.flappyXPos,
    //                     gameData.flappyYPos,
    //                     gameData.flappySize,
    //                     gameData.gravity,
    //                     gameData.lift
    //                 );
    //             }
    //         }

    //         gameData.flappy.Update();
    //         gameData.flappy.Draw();

    //         if (
    //             gameData.frameCount % gameData.pipeSpawnFrame == 0 && gameData.frameCount != 0
    //         ) {
    //             gameData.gameScore += 1;
                
    //             pipes[pipeIndex] = new Pipe(
    //                 gameData.pipeWidth,
    //                 gameData.pipeSpacing,
    //                 gameData.pipeSpeed
    //             );

    //             if (pipeIndex < (gameData.pipeCount - 1)) {
    //                 pipeIndex++;
    //             } else {
    //                 pipeIndex = 0;
    //             }
    //         }

    //         gameData.frameCount++;
    //     }

    //     if (gameData.programState == 2) {
    //         gameData.frameCount = 0;
    //         gameData.gameScore -= 1;

    //         show_gameover(gameData);
    //     }

    //     HAL_Delay(gameData.frameDelay);
    // }
}


