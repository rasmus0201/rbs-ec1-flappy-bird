#ifndef GLOBALS_H
#define GLOBALS_H

#include "mbed.h"

#define SCREEN_HEIGHT 272
#define SCREEN_WIDTH 480

class Globals
{
    public:
        static InterruptIn FLY_BUTTON;
        static DigitalOut LED;
};

#endif