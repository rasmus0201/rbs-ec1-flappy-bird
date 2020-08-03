/**
 * @file bird.h
 * @author Rasmus Sørensen (bundsgaard.rasmus@gmail.com)
 * @brief Definitions of the bird class
 * @version 0.1
 * @date 2020-08-02
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef BIRD_H
#define BIRD_H

/**
 * @brief Construct a bird to show on LCD screen
 *        The bird moves up with the provided the lift,
 *        and on each frame update gravity will be applied
 *        to force the bird accelerate down.
 * 
 */
class Bird
{
    public:
        /**
         * @brief Construct a new Bird object
         */
        Bird();

        /**
         * @brief Reset the bird with values
         * 
         * @param xPos      The x-position of the bird
         * @param yPos      The y-posigtion of the bird
         * @param size      The size (height/width)
         * @param gravity   How much down-wards force to apply (gravity)
         * @param lift      How much up-wards force to apply (lift/thrust)
         */
        void Init(int xPos, int yPos, int size, float gravity, float lift);

        /**
         * @brief Get x-position
         * 
         * @return int 
         */
        int GetX();
        
        /**
         * @brief Get y-position
         * 
         * @return int 
         */
        int GetY();

        /**
         * @brief Get the size 
         * 
         * @return int 
         */
        int GetSize();

        /**
         * @brief Make the bird go up
         * 
         */
        void Up();

        /**
         * @brief Used for every frame update
         * 
         */
        void Update();

        /**
         * @brief Draw the bird
         * 
         */
        void Draw();

    private:
        int x;
        int y;
        int size;
        float g;
        float l;
        float velocity;
        int SCREEN_HEIGHT;
};

#endif