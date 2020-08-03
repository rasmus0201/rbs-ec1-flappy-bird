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

#include "GameEngine.h"
#include "AbstractGameState.h"

/**
 * @brief Play state - the state when playing the game
 * 
 */
class PlayState : public AbstractGameState
{
    public:
        void Init(GameEngine *game);
        void Cleanup(GameEngine *game);

        void Pause(GameEngine *game);
        void Resume(GameEngine *game);

        void HandleEvents(GameEngine *game);
        void Update(GameEngine *game);
        void Draw(GameEngine *game);

        static PlayState* Instance()
        {
            return &state;
        }

    protected:
        PlayState() {}

    private:
        static PlayState state;
};

#endif