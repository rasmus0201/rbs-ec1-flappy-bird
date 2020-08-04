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

/*
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
*/

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
