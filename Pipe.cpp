#include "mbed.h"
#include "stm32746g_discovery_lcd.h"
#include "Bird.h"
#include "Pipe.h"

/**
 * @brief Construct a new Pipe:: Pipe object
 * 
 * @param width 
 * @param spacingHole 
 * @param movingSpeed 
 */
Pipe::Pipe(int width, int spacingHole, int movingSpeed)
{
    this->SCREEN_WIDTH = BSP_LCD_GetXSize();
    this->SCREEN_HEIGHT = BSP_LCD_GetYSize();
    this->EDGE_THRESHOLD = 20;
    
    this->spacing = spacingHole; // Space between top and bottom pipe
    this->w = width; // width of pipe
    this->speed = movingSpeed; // How fast it moves
    this->x = this->SCREEN_WIDTH - width; // x position
    this->color = LCD_COLOR_WHITE; // Fill color of pipe

    // Random number between 20 - 252 of the screens height (272px)
    // Height of the top pipe, Gets drawn from yPos: 0
    this->top = rand() % (this->SCREEN_HEIGHT - this->EDGE_THRESHOLD - this->spacing) + this->EDGE_THRESHOLD;

    // TODO REMOVE?
    if (this->top < this->EDGE_THRESHOLD) {
        this->top = this->EDGE_THRESHOLD;
    } else if (this->top > (this->SCREEN_HEIGHT - this->EDGE_THRESHOLD - this->spacing)) {
        this->top = this->SCREEN_HEIGHT - this->EDGE_THRESHOLD - this->spacing;
    }

    // Height of the bottom pipe, Gets drawn from yPos: SCREEN_HEIGHT - bottom
    this->bottom = this->SCREEN_HEIGHT - (this->top + this->spacing);
};

/**
 * @brief Check if bird hit pipe
 * 
 * @param r 
 * @return true 
 * @return false 
 */
bool Pipe::Collides(Bird r)
{
    if (r.GetY() < top || r.GetY() > (this->SCREEN_HEIGHT - this->bottom)) {
        if (r.GetX() > this->x && r.GetX() < this->x + this->w) {
            return true;
        }
    }

    return false;
};

/**
 * @brief Calculates if the pipe is off the screen
 * 
 * @return true 
 * @return false 
 */
bool Pipe::OffScreen()
{
    // The screen can't halfy print stuff
    // This will return true if some of the rect is outside the screen

    // Outside to the right
    if ((this->x + this->w) > this->SCREEN_WIDTH) {
        return true;
    }

    // Outside to the left
    if (this->x < 0) {
        return true;
    }

    return false;
};

/**
 * @brief Update - updates physics (moves pipe to the left)
 * 
 */
void Pipe::Update()
{
    this->x -= this->speed;
};

/**
 * @brief Draw the pipe to the screen
 * 
 */
void Pipe::Draw()
{
    if (OffScreen()) {
        return;
    }
    
    uint32_t prevColor = BSP_LCD_GetBackColor();
    BSP_LCD_SetBackColor(this->color);

    // Draw to top and bottom of the pipe
    BSP_LCD_FillRect(this->x, 0, this->w, this->top);
    BSP_LCD_FillRect(this->x, this->SCREEN_HEIGHT - this->bottom, this->w, this->bottom);

    // Restore back color
    BSP_LCD_SetBackColor(prevColor);
};
