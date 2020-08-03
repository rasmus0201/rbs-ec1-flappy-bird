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

#include "GameEngine.h"
#include "PlayState.h"

PlayState PlayState::state;

void PlayState::Init()
{
    printf("PlayState Init\n");
};

void PlayState::Cleanup()
{
    printf("PlayState Cleanup\n");
};

void PlayState::Pause()
{
    printf("PlayState Pause\n");
};

void PlayState::Resume()
{
    printf("PlayState Resume\n");
};

void PlayState::HandleEvents(GameEngine *game)
{

};

void PlayState::Update(GameEngine *game)
{

};

void PlayState::Draw(GameEngine *game)
{

};