/**
 * @file StartState.cpp
 * @author Rasmus Sørensen (bundsgaard.rasmus@gmail.com)
 * @brief Start state code
 * @version 0.1
 * @date 2020-08-02
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "stm32746g_discovery_lcd.h"
#include "stm32746g_discovery_ts.h"
#include "GameData.h"
#include "GameEngine.h"
#include "StartState.h"

StartState StartState::state;

void StartState::Init(GameEngine *game)
{
    printf("StartState Init\n");
    BSP_LCD_SetFont(&Font20);

    BSP_LCD_Clear(LCD_COLOR_GREEN);
    BSP_LCD_SetBackColor(LCD_COLOR_GREEN);
    BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
    BSP_LCD_DisplayStringAt(
        0,
        LINE(4),
        (uint8_t *)"Press play to start",
        CENTER_MODE
    );

    BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
    BSP_LCD_SetTextColor(LCD_COLOR_BLACK);

    this->btnX = int(480 / 2 - 55);
    this->btnY = int(272 / 2);
    this->btnWidth = 100;
    this->btnHeight = 50;
    BSP_LCD_FillRect(this->btnX, this->btnY, this->btnWidth, this->btnHeight);

    BSP_LCD_SetFont(&Font16);
    BSP_LCD_SetBackColor(LCD_COLOR_TRANSPARENT);
    BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
    BSP_LCD_DisplayStringAt(0, btnY + 16, (uint8_t *)"PLAY", CENTER_MODE);

    BSP_LCD_SetFont(&Font20);
};

void StartState::Cleanup(GameEngine *game)
{
    printf("StartState Cleanup\n");
};

void StartState::Pause(GameEngine *game)
{
    printf("StartState Pause\n");
};

void StartState::Resume(GameEngine *game)
{
    printf("StartState Resume\n");
};

void StartState::HandleEvents(GameEngine *game)
{
    GameData gameData = game->GetGameData();

    if (gameData.screenState.touchDetected) {
        bool pressed = true;

        if (
            !(gameData.screenState.touchX[0] > btnX && gameData.screenState.touchX[0] < (btnX + btnWidth))
        ) {
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
};

void StartState::Update(GameEngine *game)
{

};

void StartState::Draw(GameEngine *game)
{

};
