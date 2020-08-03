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

/**
 * @brief Game over state - used when user dies
 * 
 */
class GameOverState : public AbstractGameState
{
    public:
        void Init(GameEngine *game);
        void Cleanup(GameEngine *game);

        void Pause(GameEngine *game);
        void Resume(GameEngine *game);

        void HandleEvents(GameEngine *game);
        void Update(GameEngine *game);
        void Draw(GameEngine *game);

        static GameOverState* Instance()
        {
            return &state;
        }

    protected:
        GameOverState() {}

    private:
        static GameOverState state;
        int btnX;
        int btnY;
        int btnWidth;
        int btnHeight;
};

#endif