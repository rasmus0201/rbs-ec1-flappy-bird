/**
 * @file PlayState.h
 * @author Rasmus Sørensen (bundsgaard.rasmus@gmail.com)
 * @brief Definitions of the play state class
 * @version 0.1
 * @date 2020-08-02
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef PLAY_STATE_H
#define PLAY_STATE_H

#include "Pipe.h"
#include "Bird.h"
#include "GameEngine.h"
#include "AbstractGameState.h"

/**
 * @brief Play state - the state when playing the game
 * 
 */
class PlayState : public AbstractGameState
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
         * @brief Callback for peripheral button 
         * 
         */
        void FlyButtonCallback();

        /**
         * @brief Get the instance of singleton
         * 
         * @return PlayState* 
         */
        static PlayState* Instance()
        {
            return &state;
        }

    protected:
        /**
         * @brief Make singleton object
         * 
         */
        PlayState() {}

    private:
        static PlayState state;
        Bird flappy;
        std::vector<Pipe *> pipes;
};

#endif
