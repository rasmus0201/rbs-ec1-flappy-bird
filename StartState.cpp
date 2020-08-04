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
#include "PlayState.h"
#include "StartState.h"

StartState StartState::state;

void StartState::Init(GameEngine *game)
{
    printf("StartState Init\n");

    this->button = InteractiveButton(
        int(480 / 2 - 55),
        int(272 / 2),
        100,
        50
    );

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

    BSP_LCD_FillRect(button.GetX(), button.GetY(), button.GetWidth(), button.GetHeight());

    BSP_LCD_SetFont(&Font16);
    BSP_LCD_SetBackColor(LCD_COLOR_TRANSPARENT);
    BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
    BSP_LCD_DisplayStringAt(0, button.GetY() + 16, (uint8_t *)"PLAY", CENTER_MODE);

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
    if (this->button.IsPressed()) {
        printf("Button was pressed");
        
        game->ChangeState(PlayState::Instance());
    }
};

void StartState::Update(GameEngine *game)
{

};

void StartState::Draw(GameEngine *game)
{

};
