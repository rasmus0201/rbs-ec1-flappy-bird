#ifndef GAME_DATA_H
#define GAME_DATA_H

#include "stm32746g_discovery_ts.h"
#include "Bird.h"

class GameData
{
    public:
        GameData();
        void Update();

    public:
        int programState;
        int gameScore;
        TS_StateTypeDef screenState;
        int frameCount;
        int frameDelay;
        int pipeCount;
        int pipeSpawnFrame;
        int pipeSpacing;
        int pipeSpeed;
        int pipeWidth;
        int flappyXPos;
        int flappyYPos;
        float gravity;
        float lift;
        int flappySize;

        Bird flappy;
};

#endif