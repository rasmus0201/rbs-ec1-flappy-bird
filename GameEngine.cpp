/**
 * @file GameEngine.cpp
 * @author Rasmus Sørensen (bundsgaard.rasmus@gmail.com)
 * @brief Game engine implementation
 * @version 0.1
 * @date 2020-08-04
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "GameData.h"
#include "GameEngine.h"
#include "AbstractGameState.h"

/**
 * @brief Init the game engine
 * 
 * @param gameData 
 */
void GameEngine::Init(GameData* gameData)
{
    this->gameData = gameData;
    this->isRunning = true;
};

/**
 * @brief Cleanups
 * 
 */
void GameEngine::Cleanup()
{
    // Cleanup the all states
    while (!this->states.empty()) {
        this->states.back()->Cleanup(this);
        this->states.pop_back();
    }
};

/**
 * @brief Change to a different state, also clears any current state
 * 
 * @param state 
 */
void GameEngine::ChangeState(AbstractGameState *state)
{
    // Cleanup the current state
    if (!this->states.empty()) {
        this->states.back()->Cleanup(this);
        this->states.pop_back();
    }

    // Store and init the new state
    this->states.push_back(state);
    this->states.back()->Init(this);
};

/**
 * @brief Push a state - will pause current state
 * 
 * @param state 
 */
void GameEngine::PushState(AbstractGameState *state)
{
    // Pause current state
    if (!states.empty()) {
        states.back()->Pause(this);
    }

    // Store and initialize the new state
    states.push_back(state);
    states.back()->Init(this);
};

/**
 * @brief Remove state - will resume the first previously paused state
 * 
 */
void GameEngine::PopState()
{
    // Remove & clean up the latest state
    if (!states.empty()) {
        states.back()->Cleanup(this);
        states.pop_back();
    }

    // If there is more states, resume the latest of them
    if (!states.empty()) {
        states.back()->Resume(this);
    }
}

/**
 * @brief Handle the last state's events
 * 
 */
void GameEngine::HandleEvents()
{
    this->states.back()->HandleEvents(this);
}

/**
 * @brief Handle the last state's updates
 * 
 */
void GameEngine::Update()
{
    this->states.back()->Update(this);
}

/**
 * @brief Handle the last state's draws
 * 
 */
void GameEngine::Draw()
{
    this->states.back()->Draw(this);
}

/**
 * @brief Check if game is running
 * 
 * @return true 
 * @return false 
 */
bool GameEngine::Running()
{
    return this->isRunning;
}

/**
 * @brief Get the game data object pointer
 * 
 * @return GameData* 
 */
GameData* GameEngine::GetGameData()
{
    return this->gameData;
}

/**
 * @brief Quit the game
 * 
 */
void GameEngine::Quit()
{
    this->isRunning = false;
}
