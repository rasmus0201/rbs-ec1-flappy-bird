#include "mbed.h"
#include "stm32746g_discovery_lcd.h"
#include "Globals.h"
#include "Bird.h"

/**
 * @brief Construct a new Bird:: Bird object
 * 
 */
Bird::Bird() {
    this->velocity = 0;
};

/**
 * @brief Initialize the bird object
 * 
 * @param xPos 
 * @param yPos 
 * @param size 
 * @param gravity 
 * @param lift 
 */
void Bird::Init(int xPos, int yPos, int size, float gravity, float lift) {
    this->x = xPos;
    this->y = yPos;
    this->size = size;
    this->g = gravity;
    this->l = lift;
    
    this->velocity = 0;
};

/**
 * @brief Get x-position
 * 
 * @return int 
 */
int Bird::GetX() {
    return this->x;
};

/**
 * @brief Get y-position
 * 
 * @return int 
 */
int Bird::GetY() {
    return this->y;
};

/**
 * @brief Get size (width/height)
 * 
 * @return int 
 */
int Bird::GetSize() {
    return this->size;
};

/**
 * @brief Make the bird fly (add lift)
 * 
 */
void Bird::Up() {
    this->velocity += this->l;
};

/**
 * @brief Update the bird - this does the basic physics
 * 
 */
void Bird::Update() {
    this->velocity += this->g;
    this->y += int(this->velocity);

    if (this->y > (SCREEN_HEIGHT - this->size)) {
        this->y = (SCREEN_HEIGHT - this->size);
        this->velocity = 0;
    }

    if (this->y < 0) {
        this->y = 0;
        this->velocity = 0;
    }
};

/**
 * @brief Draw the bird to the LCD screen
 * 
 */
void Bird::Draw() {
    uint32_t prevColor = BSP_LCD_GetBackColor();
    BSP_LCD_SetBackColor(LCD_COLOR_WHITE);

    // Draw it
    BSP_LCD_FillRect(this->x, this->y, this->size, this->size);

    // Restore back color
    BSP_LCD_SetBackColor(prevColor);
};
