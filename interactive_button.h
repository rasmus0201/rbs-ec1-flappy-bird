#ifndef INTERACTIVE_BUTTON_H
#define INTERACTIVE_BUTTON_H

#include "program_state.h"

class InteractiveButton
{
    public:
        InteractiveButton(int xPos, int yPos, int width, int height);
        
        bool IsPressed(ProgramState *state);

        int GetX();

        int GetY();

        int GetWidth();

        int GetHeight();

    private:
        int xPos;
        int yPos;
        int height;
        int width;
};

#endif