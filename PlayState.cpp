/**
 * @file PlayState.cpp
 * @author Rasmus Sørensen (bundsgaard.rasmus@gmail.com)
 * @brief Play state code
 * @version 0.1
 * @date 2020-08-02
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "stm32746g_discovery_lcd.h"
#include "stm32746g_discovery_ts.h"
#include "Globals.h"
#include "GameEngine.h"
#include "PlayState.h"

PlayState PlayState::state;

void PlayState::Init(GameEngine *game)
{
    printf("PlayState Init\n");

    GameData* gameData = game->GetGameData();
    gameData->flappy->Init(
        gameData->flappyXPos,
        gameData->flappyYPos,
        gameData->flappySize,
        gameData->gravity,
        gameData->lift
    );

    BSP_LCD_SetFont(&Font20);
    BSP_LCD_Clear(LCD_COLOR_GREEN);
};

void PlayState::Cleanup(GameEngine *game)
{
    printf("PlayState Cleanup\n");
};

void PlayState::Pause(GameEngine *game)
{
    printf("PlayState Pause\n");
};

void PlayState::Resume(GameEngine *game)
{
    printf("PlayState Resume\n");
};

void PlayState::HandleEvents(GameEngine *game)
{
    // Check if game-over
};

void PlayState::Update(GameEngine *game)
{
    GameData* gameData = game->GetGameData();
    
    for (auto & pipe : this->pipes) {
        pipe->Update();

        // Add score if the pipe's right-most edge is equal to the birds left-most edge
        // This will ensure that once the bird have passed through the pipe
        // The user will get an extra scorepoint
        if (gameData->flappy->GetX() == (pipe->GetX() + pipe->GetWidth())) {
            gameData->gameScore += 1;
        }

        // Check if the bird hit the pipe
        if (pipe->Collides(*gameData->flappy)) {
            gameData->programState = 2;
            gameData->frameCount = 0;
            gameData->stateChanged = true;
            
            pipeIndex = 0;
            pipes[pipeIndex++] = new Pipe(
                gameData->pipeWidth,
                gameData->pipeSpacing,
                gameData->pipeSpeed
            );

            for (int i = 1; i < gameData->pipeCount; i++) {
                pipes[i] = nullptr;
            }

            gameData->flappy->Init(
                gameData->flappyXPos,
                gameData->flappyYPos,
                gameData->flappySize,
                gameData->gravity,
                gameData->lift
            );

            // led.write(1);
            return;
        }
    }

    // Game-over if bird is below screen
    if ((gameData->flappy->GetY() + gameData->flappy->GetSize()) >= SCREEN_HEIGHT) {
        gameData->programState = 2;
        gameData->frameCount = 0;
        gameData->stateChanged = true;
        
        pipeIndex = 0;
        pipes[pipeIndex++] = new Pipe(
            gameData->pipeWidth,
            gameData->pipeSpacing,
            gameData->pipeSpeed
        );

        for (int i = 1; i < gameData->pipeCount; i++) {
            pipes[i] = nullptr;
        }

        // led.write(1);
    }

    gameData->flappy->Update();
};

void PlayState::Draw(GameEngine *game)
{
    GameData* gameData = game->GetGameData();
    BSP_LCD_Clear(LCD_COLOR_GREEN);

    for (auto & pipe : this->pipes) {
        pipe->Draw();
    }

    gameData->flappy->Draw();
};