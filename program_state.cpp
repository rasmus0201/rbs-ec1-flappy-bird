#include "mbed.h"
#include "stm32746g_discovery_lcd.h"
#include "stm32746g_discovery_ts.h"
#include "program_state.h"

ProgramState::ProgramState() {
    // BSP_TS_GetState(&this->screenState);
    
    this->programState = 0;
    this->gameScore = 0;
    this->frameCount = 0;
    this->frameDelay = 100;
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

void ProgramState::UpdateScreenState() {
    // BSP_TS_GetState(&this->screenState);
}