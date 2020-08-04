/**
 * @file GameData.h
 * @author Rasmus Sørensen (bundsgaard.rasmus@gmail.com)
 * @brief Game data definitions
 * @version 0.1
 * @date 2020-08-04
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef GAME_DATA_H
#define GAME_DATA_H

#include "stm32746g_discovery_ts.h"

/**
 * @brief data to make the states sync
 * 
 */
class GameData
{
    public:
        /**
         * @brief Construct a new Game Data object
         * 
         */
        GameData();

    public:
        int gameScore;
        int frameCount;
        int frameDelay;
        int pipeSpawnFrame;
        int pipeSpacing;
        int pipeSpeed;
        int pipeWidth;
        int flappyXPos;
        int flappyYPos;
        float gravity;
        float lift;
        int flappySize;
};

#endif
