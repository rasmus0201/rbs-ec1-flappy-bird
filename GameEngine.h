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
        /**
         * @brief Init game engine with data object pointer
         * 
         * @param gameData 
         */
        void Init(GameData* gameData);

        /**
         * @brief Cleanup
         * 
         */
        void Cleanup();

        /**
         * @brief Change state
         * 
         * @param state 
         */
        void ChangeState(AbstractGameState *state);

        /**
         * @brief Push state
         * 
         * @param state 
         */
        void PushState(AbstractGameState *state);

        /**
         * @brief Pop state
         * 
         */
        void PopState();

        /**
         * @brief Handle events
         * 
         */
        void HandleEvents();

        /**
         * @brief Handle updates
         * 
         */
        void Update();

        /**
         * @brief Draw to display
         * 
         */
        void Draw();

        /**
         * @brief Check the status (if it is running)
         * 
         * @return true 
         * @return false 
         */
        bool Running();

        /**
         * @brief Get the Game Data object (pointer)
         * 
         * @return GameData* 
         */
        GameData* GetGameData();

        /**
         * @brief Quit the engine
         * 
         */
        void Quit();

    private:
        std::vector<AbstractGameState *> states;
        GameData* gameData;
        bool isRunning;
};

#endif
