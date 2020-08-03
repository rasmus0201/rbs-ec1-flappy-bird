/**
 * @file GameEngine.h
 * @author Rasmus Sørensen (bundsgaard.rasmus@gmail.com)
 * @brief Definitions of the game engine class
 * @version 0.1
 * @date 2020-08-02
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include "mbed.h"
#include <vector>
#include "GameData.h"

class AbstractGameState;

class GameEngine
{
    public:
        void Init(GameData gameData);
        void Cleanup();

        void ChangeState(AbstractGameState *state);
        void PushState(AbstractGameState *state);
        void PopState();
        void HandleEvents();
        void Update();
        void Draw();
        bool Running();
        GameData GetGameData();
        void Quit();

    private:
        std::vector<AbstractGameState *> states;
        GameData gameData;
        bool isRunning;
};

#endif