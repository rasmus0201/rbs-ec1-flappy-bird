#ifndef PROGRAM_STATE_H
#define PROGRAM_STATE_H

#include "stm32746g_discovery_ts.h"

class ProgramState
{
    public:
        ProgramState();

        void UpdateScreenState();
    
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
};

#endif