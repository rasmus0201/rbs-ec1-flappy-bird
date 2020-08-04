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
#include "Globals.h"
#include "GameData.h"
#include "GameEngine.h"
#include "PlayState.h"
#include "GameOverState.h"

/**
 * @brief Helper - get the number of digits in an integer
 * 
 * @param i 
 * @return unsigned
 */
unsigned number_of_digits(unsigned i)
{
    return i > 0 ? (int) log10 ((double) i) + 1 : 1;
}

GameOverState GameOverState::state;

/**
 * @brief Init gameover
 * 
 * @param game 
 */
void GameOverState::Init(GameEngine *game)
{
    this->button = InteractiveButton(
        int(480 / 2 - 55),
        int(272 / 2),
        100,
        50
    );

    GameData* gameData = game->GetGameData();
    
    uint8_t scoreStr[13 + number_of_digits(gameData->gameScore)];
    BSP_LCD_SetFont(&Font20);
    sprintf((char *)scoreStr, "Your score: %d", gameData->gameScore);

    BSP_LCD_Clear(LCD_COLOR_RED);
    BSP_LCD_SetBackColor(LCD_COLOR_RED);
    BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
    BSP_LCD_DisplayStringAt(0, LINE(3), (uint8_t *)"GAMEOVER", CENTER_MODE);
    BSP_LCD_DisplayStringAt(0, LINE(4), (uint8_t *)scoreStr, CENTER_MODE);

    BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
    BSP_LCD_SetTextColor(LCD_COLOR_BLACK);

    BSP_LCD_FillRect(this->button.GetX(), this->button.GetY(), this->button.GetWidth(), this->button.GetHeight());
    
    BSP_LCD_SetFont(&Font16);
    BSP_LCD_SetBackColor(LCD_COLOR_TRANSPARENT);
    BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
    BSP_LCD_DisplayStringAt(0, this->button.GetY() + 16, (uint8_t *)"RESTART", CENTER_MODE);

    BSP_LCD_SetFont(&Font20);
};

/**
 * @brief Cleanup
 * 
 * @param game 
 */
void GameOverState::Cleanup(GameEngine *game)
{
    Globals::LED.write(0);
};


/**
 * @brief Pause
 * 
 * @param game 
 */
void GameOverState::Pause(GameEngine *game)
{
    printf("GameOverState Pause\n");
};

/**
 * @brief Resume
 * 
 * @param game 
 */
void GameOverState::Resume(GameEngine *game)
{
    printf("GameOverState Resume\n");
};

/**
 * @brief Handle events
 * 
 * @param game 
 */
void GameOverState::HandleEvents(GameEngine *game)
{    
    if (this->button.IsPressed()) {
        GameData* gameData = game->GetGameData();
        gameData->gameScore = 0;   
        
        game->ChangeState(PlayState::Instance());
    }
};

/**
 * @brief Update
 * 
 * @param game 
 */
void GameOverState::Update(GameEngine *game)
{

};

/**
 * @brief Draw
 * 
 * @param game 
 */
void GameOverState::Draw(GameEngine *game)
{

};
