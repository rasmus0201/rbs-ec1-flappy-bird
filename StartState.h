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

/**
 * @brief Start state - used when starting the game
 * 
 */
class StartState : public AbstractGameState
{
    public:
        void Init();
        void Cleanup();

        void Pause();
        void Resume();

        void HandleEvents(GameEngine *game);
        void Update(GameEngine *game);
        void Draw(GameEngine *game);

        static StartState* Instance()
        {
            return &state;
        }

    protected:
        StartState() {}

    private:
        static StartState state;
        int btnX;
        int btnY;
        int btnWidth;
        int btnHeight;
};

#endif