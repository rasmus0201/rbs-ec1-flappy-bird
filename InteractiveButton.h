/**
 * @file InteractiveButton.h
 * @author Rasmus Sørensen (bundsgaard.rasmus@gmail.com)
 * @brief Class definitions for InteractiveButton
 * @version 0.1
 * @date 2020-08-03
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef INTERACTIVE_BUTTON_H
#define INTERACTIVE_BUTTON_H

/**
 * @brief Interact with a button on the touch screen
 * 
 */
class InteractiveButton
{
    public:
        /**
         * @brief Construct a new Interactive Button object
         * 
         * @param xPos 
         * @param yPos 
         * @param width 
         * @param height 
         */
        InteractiveButton(int xPos, int yPos, int width, int height);

        /**
         * @brief Check if the button is pressed according
         * 
         * @return true 
         * @return false 
         */
        bool IsPressed();

        /**
         * @brief Get the x position of the button
         * 
         * @return int 
         */
        int GetX();

        /**
         * @brief Get the y position of the button
         * 
         * @return int 
         */
        int GetY();

        /**
         * @brief Get the width of the button
         * 
         * @return int 
         */
        int GetWidth();

        /**
         * @brief Get the Height of the button
         * 
         * @return int 
         */
        int GetHeight();

    private:
        int xPos;
        int yPos;
        int height;
        int width;
};

#endif
