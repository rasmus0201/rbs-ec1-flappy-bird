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

class GameEngine;

/**
 * @brief Abstract Game state class.
 *        A state will always only be needed as a single instance,
 *        therefor we should make them singletons (protected constructor)
 * 
 */
class AbstractGameState
{
    public:
        /**
         * @brief Init the state
         * 
         * @param game 
         */
        virtual void Init(GameEngine *game) = 0;
        
        /**
         * @brief Cleanup the state
         * 
         * @param game 
         */
        virtual void Cleanup(GameEngine *game) = 0;

        /**
         * @brief Pause a state
         * 
         * @param game 
         */
        virtual void Pause(GameEngine *game) = 0;
        
        /**
         * @brief Resume a state
         * 
         * @param game 
         */
        virtual void Resume(GameEngine *game) = 0;

        /**
         * @brief Handle any events
         * 
         * @param game 
         */
        virtual void HandleEvents(GameEngine *game) = 0;
       
        /**
         * @brief Update the state
         * 
         * @param game 
         */
        virtual void Update(GameEngine *game) = 0;
        
        /**
         * @brief Draw the state
         * 
         * @param game 
         */
        virtual void Draw(GameEngine *game) = 0;

        /**
         * @brief Change state to another state
         * 
         * @param game 
         * @param state 
         */
        void ChangeState(GameEngine *game, AbstractGameState *state);

    protected:
        /**
         * @brief Construct a new Abstract Game State object
         * 
         */
        AbstractGameState() {}
};

#endif
