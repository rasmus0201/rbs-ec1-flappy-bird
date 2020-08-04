/**
 * @file InteractiveButton.cpp
 * @author Rasmus Sørensen (bundsgaard.rasmus@gmail.com)
 * @brief Code for class
 * @version 0.1
 * @date 2020-08-03
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "mbed.h"
#include "stm32746g_discovery_lcd.h"
#include "stm32746g_discovery_ts.h"
#include "InteractiveButton.h"

/**
 * @brief Construct a new Interactive Button:: Interactive Button object
 *
 */
InteractiveButton::InteractiveButton()
{
};

/**
 * @brief Construct a new Interactive Button:: Interactive Button object
 * 
 * @param xPos 
 * @param yPos 
 * @param width 
 * @param height 
 */
InteractiveButton::InteractiveButton(int xPos, int yPos, int width, int height)
{
    this->xPos = xPos;
    this->yPos = yPos;
    this->width = width;
    this->height = height;
};

/**
 * @brief This method only works for the 1st finger on the touch display
 * 
 * @return true 
 * @return false 
 */
bool InteractiveButton::IsPressed()
{
    TS_StateTypeDef screenState;
    BSP_TS_GetState(&screenState);

    // If there is no touches, early exit
    if (!screenState.touchDetected) {
        return false;
    }

    // If the touch's x-position is out of bounds with the button, then exit
    // Example which returns false (x marks a touch):
    //     ----------------------
    //     |   x                |
    //     |      x  BTN        |
    //     |               x    |
    //
    // Example which returns true (x marks a touch)
    //     ----------------------
    //     |         x          |
    //     |         BTN        |
    //     |           x        |
    if (!(
        screenState.touchX[0] > this->xPos &&
        screenState.touchX[0] < (this->xPos + this->width)
    )) {
        return false;
    }

    // If the touch's y-position is out of bounds with the button, then exit
    // Example which returns false (x marks a touch):
    //     ----------------------
    //     |   x            x   |
    //     |         BTN        |
    //     |          x         |
    //
    // Example which returns true (x marks a touch):
    //     ----------------------
    //     |                    |
    //     |        x BTN    x  |
    //     |                    |
    if (!(
        screenState.touchY[0] > this->yPos &&
        screenState.touchY[0] < (this->yPos + this->height)
    )) {
        return false;
    }

    // Otherwise we know they must be within the bounds of the button
    return true;
};

/**
 * @brief Get the button's x-position
 * 
 * @return int 
 */
int InteractiveButton::GetX()
{
    return this->xPos;
};

/**
 * @brief Get the button's y-position
 * 
 * @return int 
 */
int InteractiveButton::GetY()
{
    return this->yPos;
};

/**
 * @brief Get the button's width
 * 
 * @return int 
 */
int InteractiveButton::GetWidth()
{
    return this->width;
};

/**
 * @brief Get the button's height
 * 
 * @return int 
 */
int InteractiveButton::GetHeight()
{
    return this->height;
};
