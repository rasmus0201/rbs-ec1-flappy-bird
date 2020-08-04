/**
 * @file StartState.h
 * @author Rasmus Sørensen (bundsgaard.rasmus@gmail.com)
 * @brief Start state class definitions
 * @version 0.1
 * @date 2020-08-02
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
 * @brief Start state - used when starting the game
 * 
 */
class StartState : public AbstractGameState
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
         * @return StartState* 
         */
        static StartState* Instance()
        {
            return &state;
        }

    protected:
        /**
         * @brief Make singleton object
         * 
         */
        StartState() {}

    private:
        static StartState state;
        InteractiveButton button;
};

#endif
