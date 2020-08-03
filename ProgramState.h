#ifndef PROGRAM_STATE_H
#define PROGRAM_STATE_H

class ProgramState
{
    public:
        ProgramState();
    
    public:
        int programState;
        bool stateChanged;
        int gameScore;
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