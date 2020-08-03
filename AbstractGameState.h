/**
 * @file GameState.h
 * @author Rasmus Sørensen (bundsgaard.rasmus@gmail.com)
 * @brief Definitions of the game state class
 * @version 0.1
 * @date 2020-08-02
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef ABSTRACT_GAME_STATE_H
#define ABSTRACT_GAME_STATE_H

#include "mbed.h"
#include "GameEngine.h"

/**
 * @brief Abstract Game state class.
 *        A state will always only be needed as a single instance,
 *        therefor we should make them singletons (protected constructor)
 * 
 */
class AbstractGameState
{
    public:
        virtual void Init() = 0;
        virtual void Cleanup() = 0;

        virtual void Pause() = 0;
        virtual void Resume() = 0;

        virtual void HandleEvents(GameEngine *game) = 0;
        virtual void Update(GameEngine *game) = 0;
        virtual void Draw(GameEngine *game) = 0;

        void ChangeState(GameEngine *game, AbstractGameState *state)
        {
            game->ChangeState(state);
        }

    protected:
        GameState() {}
};

#endif