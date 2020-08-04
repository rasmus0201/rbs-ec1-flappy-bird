#include "stm32746g_discovery_ts.h"
#include "GameData.h"

GameData::GameData()
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

