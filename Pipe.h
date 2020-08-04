/**
 * @file Pipe.h
 * @author Rasmus Sørensen (bundsgaard.rasmus@gmail.com)
 * @brief Definitions of the pipe class
 * @version 0.1
 * @date 2020-08-02
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef PIPE_H
#define PIPE_H

#include "mbed.h"
#include "Bird.h"

/**
 * @brief Construct a pipe object to show it on the LCD screen
 *        This will make a random pipe which will start on the
 *        right side of the screen on update it will move to the left.
 * 
 */
class Pipe
{
    public:
        /**
         * @brief Construct a new Pipe object
         * 
         * @param width         The width on x-axis
         * @param spacingHole   Height of the hole seperating top/bottom half
         * @param movingSpeed   How many pixels it moves pr. update
         */
        Pipe(int width, int spacingHole, int movingSpeed);

        /**
         * @brief Check if this pipe if colldiing with a bird object.
         * 
         * @param r     The bird object to compare to.
         * @return true 
         * @return false 
         */
        bool Collides(Bird r);

        /**
         * @brief 
         * 
         * @return true 
         * @return false 
         */
        bool OffScreen();

        /**
         * @brief Used for every frame update
         * 
         */
        void Update();

        /**
         * @brief Draw the pipe
         * 
         */
        void Draw();
    
    private:
        int speed;
        int spacing;
        int top;
        int bottom;
        int x;
        int w;
        uint32_t color;
        int SCREEN_HEIGHT;
        int SCREEN_WIDTH;
        int EDGE_THRESHOLD;
};

#endif
