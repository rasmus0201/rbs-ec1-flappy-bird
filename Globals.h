/**
 * @file Globals.h
 * @author Rasmus Sørensen (bundsgaard.rasmus@gmail.com)
 * @brief Globals class definition
 * @version 0.1
 * @date 2020-08-04
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef GLOBALS_H
#define GLOBALS_H

#include "mbed.h"

#define SCREEN_HEIGHT 272
#define SCREEN_WIDTH 480

/**
 * @brief Global static variables 
 * 
 */
class Globals
{
    public:
        static InterruptIn FLY_BUTTON;
        static DigitalOut LED;
};

#endif
