/**
 * @file GameOverState.cpp
 * @author Rasmus Sørensen (bundsgaard.rasmus@gmail.com)
 * @brief Start state code
 * @version 0.1
 * @date 2020-08-02
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "mbed.h"
#include "stm32746g_discovery_lcd.h"
#include "stm32746g_discovery_ts.h"
#include "GameData.h"
#include "GameEngine.h"
#include "GameOverState.h"

unsigned number_of_digits(unsigned i)
{
    return i > 0 ? (int) log10 ((double) i) + 1 : 1;
}

GameOverState GameOverState::state;

void GameOverState::Init(GameEngine *game)
{
    printf("GameOverState Init\n");

    this->btnX = int(480/2 - 55); // 185 - 285
    this->btnY = int(272/2); // 136 - 186
    this->btnWidth = 100;
    this->btnHeight = 50;

    GameData gameData = game->GetGameData();
    
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

    BSP_LCD_FillRect(this->btnX, this->btnY, this->btnWidth, this->btnHeight);
    
    BSP_LCD_SetFont(&Font16);
    BSP_LCD_SetBackColor(LCD_COLOR_TRANSPARENT);
    BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
    BSP_LCD_DisplayStringAt(0, this->btnY + 16, (uint8_t *)"RESTART", CENTER_MODE);

    BSP_LCD_SetFont(&Font20);
};

void GameOverState::Cleanup(GameEngine *game)
{
    printf("GameOverState Cleanup\n");
};

void GameOverState::Pause(GameEngine *game)
{
    printf("GameOverState Pause\n");
};

void GameOverState::Resume(GameEngine *game)
{
    printf("GameOverState Resume\n");
};

void GameOverState::HandleEvents(GameEngine *game)
{
    GameData gameData = game->GetGameData();

    if (gameData.screenState.touchDetected) {
        bool pressed = true;

        if (!(
            gameData.screenState.touchX[0] > this->btnX && 
            gameData.screenState.touchX[0] < (this->btnX + this->btnWidth)
        )) {
            pressed = false;
        }

        if (!(
            gameData.screenState.touchY[0] > this->btnY &&
            gameData.screenState.touchY[0] < (this->btnY + this->btnHeight))
        ) {
            pressed = false;
        }

        if (pressed) {
            gameData.programState = 1;
            gameData.gameScore = 0;
        }
    }
};

void GameOverState::Update(GameEngine *game)
{

};

void GameOverState::Draw(GameEngine *game)
{

};
