#include "mbed.h"
#include "stm32746g_discovery_lcd.h"
#include "stm32746g_discovery_ts.h"
#include "InteractiveButton.h"

InteractiveButton::InteractiveButton(int xPos, int yPos, int width, int height)
{
    this->xPos = xPos;
    this->yPos = yPos;
    this->width = width;
    this->height = height;
};

bool InteractiveButton::IsPressed() {
    TS_StateTypeDef screenState;
    BSP_TS_GetState(&screenState);

    if (!screenState.touchDetected) {
        return false;
    }

    if (!(screenState.touchX[0] > this->xPos && screenState.touchX[0] < (this->xPos + this->width))) {
        return false;
    }

    if (!(screenState.touchY[0] > this->yPos && screenState.touchY[0] < (this->yPos + this->height))) {
        return false;
    }

    return true;
};

int InteractiveButton::GetX() {
    return this->xPos;
};

int InteractiveButton::GetY() {
    return this->yPos;
};

int InteractiveButton::GetWidth() {
    return this->width;
};

int InteractiveButton::GetHeight() {
    return this->height;
};