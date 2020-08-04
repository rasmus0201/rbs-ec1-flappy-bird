/**
 * @file Globals.cpp
 * @author Rasmus Sørensen (bundsgaard.rasmus@gmail.com)
 * @brief Globals
 * @version 0.1
 * @date 2020-08-04
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "mbed.h"
#include "Globals.h"

InterruptIn Globals::FLY_BUTTON(D2);
DigitalOut Globals::LED(D3);
