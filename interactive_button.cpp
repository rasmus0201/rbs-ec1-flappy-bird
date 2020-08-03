#include "stm32746g_discovery_ts.h"
#include "program_state.h"
#include "interactive_button.h"

InteractiveButton::InteractiveButton(int xPos, int yPos, int width, int height)
{
    this->xPos = xPos;
    this->yPos = yPos;
    this->width = width;
    this->height = height;
};

bool InteractiveButton::IsPressed(ProgramState *state) {
    if (!state->screenState.touchDetected) {
        return false;
    }

    if (!(state->screenState.touchX[0] > this->xPos && state->screenState.touchX[0] < (this->xPos + this->width))) {
        return false;
    }

    if (!(state->screenState.touchY[0] > this->yPos && state->screenState.touchY[0] < (this->yPos + this->height))) {
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
