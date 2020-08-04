/**
 * @file GameOverState.h
 * @author Rasmus Sørensen (bundsgaard.rasmus@gmail.com)
 * @brief Gameover state class definitions
 * @version 0.1
 * @date 2020-08-03
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef START_STATE_H
#define START_STATE_H

#include "GameEngine.h"
#include "AbstractGameState.h"
#include "InteractiveButton.h"

/**
 * @brief Game over state - used when user dies
 * 
 */
class GameOverState : public AbstractGameState
{
    public:
        /**
         * @inheritdoc
         */
        void Init(GameEngine *game);

        /**
         * @inheritdoc
         */
        void Cleanup(GameEngine *game);

        /**
         * @inheritdoc
         */
        void Pause(GameEngine *game);

        /**
         * @inheritdoc
         */
        void Resume(GameEngine *game);

        /**
         * @inheritdoc
         */
        void HandleEvents(GameEngine *game);

        /**
         * @inheritdoc
         */
        void Update(GameEngine *game);

        /**
         * @inheritdoc
         */
        void Draw(GameEngine *game);

        /**
         * @brief Get the instance of singleton
         * 
         * @return GameOverState* 
         */
        static GameOverState* Instance()
        {
            return &state;
        }

    protected:
        /**
         * @brief Make singleton object
         * 
         */
        GameOverState() {}

    private:
        static GameOverState state;
        InteractiveButton button;
};

#endif
