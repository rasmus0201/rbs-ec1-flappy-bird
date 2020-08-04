/**
 * @file main.cpp
 * @author Rasmus Sørensen (bundsgaard.rasmus@gmail.com)
 * @brief Main
 * @version 0.1
 * @date 2020-08-04
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "mbed.h"
#include "stm32746g_discovery_lcd.h"
#include "stm32746g_discovery_ts.h"
#include "Globals.h"
#include "InteractiveButton.h"
#include "Bird.h"
#include "Pipe.h"
#include "GameData.h"
#include "GameEngine.h"
#include "StartState.h"

GameData gameData;

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

int main()
{
    srand(time(NULL));

    init_lcd();

    if (!init_touch()) {
        exit(-1);
    }

    Globals::LED.write(0);

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
    game.Init(&gameData);

    // Load the start state
    game.ChangeState(StartState::Instance());

    // Main loop
    while (game.Running()) {
        game.HandleEvents();
        game.Update();
        game.Draw();

        // HAL_Delay(gameData.frameDelay);
        HAL_Delay(100);
    }

    game.Cleanup();

    return 0;
}
