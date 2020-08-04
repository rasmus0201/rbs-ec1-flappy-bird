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
#include "GameOverState.h"
#include "PlayState.h"

PlayState PlayState::state;

/**
 * @brief Init playing state
 * 
 * @param game 
 */
void PlayState::Init(GameEngine *game)
{
    Globals::FLY_BUTTON.rise(callback(this, &PlayState::FlyButtonCallback));

    GameData* gameData = game->GetGameData();
    this->flappy.Init(
        gameData->flappyXPos,
        gameData->flappyYPos,
        gameData->flappySize,
        gameData->gravity,
        gameData->lift
    );

    this->pipes.push_back(new Pipe(
        gameData->pipeWidth,
        gameData->pipeSpacing,
        gameData->pipeSpeed
    ));

    BSP_LCD_SetFont(&Font20);
    BSP_LCD_Clear(LCD_COLOR_GREEN);
};

/**
 * @brief Cleanup
 * 
 * @param game 
 */
void PlayState::Cleanup(GameEngine *game)
{
    printf("PlayState Cleanup\n");
    
    GameData* gameData = game->GetGameData();
    
    this->pipes.clear();
    gameData->frameCount = 0;
};

/**
 * @brief Pause
 * 
 * @param game 
 */
void PlayState::Pause(GameEngine *game)
{
    printf("PlayState Pause\n");
};

/**
 * @brief Resume
 * 
 * @param game 
 */
void PlayState::Resume(GameEngine *game)
{
    printf("PlayState Resume\n");
};

/**
 * @brief Callback for button
 * 
 */
void PlayState::FlyButtonCallback()
{
    this->flappy.Up();
}

/**
 * @brief Handle button + touch display events
 * 
 * @param game 
 */
void PlayState::HandleEvents(GameEngine *game)
{
    TS_StateTypeDef touchState;
    BSP_TS_GetState(&touchState);
    
    // Lift the bird if there is a touch on screen
    if (touchState.touchDetected) {
        this->flappy.Up();
    }
};

/**
 * @brief Update bird + pipes
 * 
 * @param game 
 */
void PlayState::Update(GameEngine *game)
{
    GameData* gameData = game->GetGameData();

    std::vector<Pipe *>::iterator it;
    for(it = this->pipes.begin(); it != this->pipes.end();) {
        Pipe *pipe = *it;
        
        pipe->Update();

        // Add score if the pipe's right-most edge is equal to the birds left-most edge
        // This will ensure that once the bird have passed through the pipe
        // The user will get an extra scorepoint
        if (this->flappy.GetX() == (pipe->GetX() + pipe->GetWidth())) {
            gameData->gameScore += 1;
        }

        // Check if the bird hit the pipe
        if (pipe->Collides(this->flappy)) {
            Globals::LED.write(1);
            return game->ChangeState(GameOverState::Instance());
        }

        // Remove the pipe if it is of to the left
        if (pipe->OffScreen() && pipe->GetX() < SCREEN_WIDTH) {
            it = this->pipes.erase(it);
        } else {
            it++;
        }
    }

    // Game-over if bird is below screen
    if ((this->flappy.GetY() + this->flappy.GetSize()) >= SCREEN_HEIGHT) {
        Globals::LED.write(1);
        return game->ChangeState(GameOverState::Instance());
    }

    this->flappy.Update();
};

/**
 * @brief Draw bird + pipes
 * 
 * @param game 
 */
void PlayState::Draw(GameEngine *game)
{
    GameData* gameData = game->GetGameData();
    BSP_LCD_Clear(LCD_COLOR_GREEN);

    for (auto & pipe : this->pipes) {
        pipe->Draw();
    }

    this->flappy.Draw();

    // Add more pipes every x frames
    if (gameData->frameCount % gameData->pipeSpawnFrame == 0 && gameData->frameCount != 0) {
        this->pipes.push_back(new Pipe(
            gameData->pipeWidth,
            gameData->pipeSpacing,
            gameData->pipeSpeed
        ));
    }

    gameData->frameCount++;
};
