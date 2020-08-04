#include "GameData.h"
#include "GameEngine.h"
#include "AbstractGameState.h"

void GameEngine::Init(GameData* gameData)
{
    this->gameData = gameData;
    this->isRunning = true;
};

void GameEngine::Cleanup()
{
    // Cleanup the all states
    while (!this->states.empty()) {
        this->states.back()->Cleanup(this);
        this->states.pop_back();
    }
};

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

void GameEngine::HandleEvents()
{
    this->states.back()->HandleEvents(this);
}

void GameEngine::Update()
{
    this->states.back()->Update(this);
}

void GameEngine::Draw()
{
    this->states.back()->Draw(this);
}

bool GameEngine::Running()
{
    return this->isRunning;
}

GameData* GameEngine::GetGameData()
{
    return this->gameData;
}

void GameEngine::Quit()
{
    this->isRunning = false;
}