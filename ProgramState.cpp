/**
 * @file ProgramState.cpp
 * @author Rasmus Sørensen (bundsgaard.rasmus@gmail.com)
 * @brief Code for class
 * @version 0.1
 * @date 2020-08-03
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "ProgramState.h"

/**
 * @brief Construct a new Program State:: Program State object
 *
 */
ProgramState::ProgramState()
{
    this->programState = 0;
    this->stateChanged = true;
    this->gameScore = 0;
    this->frameCount = 0;
    this->frameDelay = 50;
    this->pipeCount = 16;
    this->pipeSpawnFrame = 40;
    this->pipeSpacing = 80;
    this->pipeSpeed = 5;
    this->pipeWidth = 40;
    this->flappyXPos = 160;
    this->flappyYPos = 136;
    this->gravity = 0.8;
    this->lift = -5;
    this->flappySize = 10;
};
