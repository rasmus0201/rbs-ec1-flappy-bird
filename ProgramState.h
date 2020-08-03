/**
 * @file ProgramState.h
 * @author Rasmus Sørensen (bundsgaard.rasmus@gmail.com)
 * @brief Class definitions for ProgramState
 * @version 0.1
 * @date 2020-08-03
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef PROGRAM_STATE_H
#define PROGRAM_STATE_H

/**
 * @brief Class to hold different set of values used across the program
 * 
 */
class ProgramState
{
    public:
        /**
         * @brief Construct a new Program State object
         * 
         */
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