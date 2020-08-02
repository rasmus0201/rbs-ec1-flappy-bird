#include "mbed.h"
#include "stm32746g_discovery_lcd.h"
#import "bird.h"

Bird::Bird() {
    this->velocity = 0;
}

void Bird::Init(int xPos, int yPos, int size, float gravity, float lift) {
    this->x = xPos;
    this->y = yPos;
    this->size = size;
    this->g = gravity;
    this->l = lift;
    
    this->velocity = 0;
    this->SCREEN_HEIGHT = BSP_LCD_GetYSize();
};

int Bird::GetX() {
    return this->x;
};

int Bird::GetY() {
    return this->y;
};

int Bird::GetSize() {
    return this->size;
};

void Bird::Up() {
    this->velocity += this->l;
};

void Bird::Update() {
    this->velocity += this->g;
    this->y += int(this->velocity);

    if (this->y > (this->SCREEN_HEIGHT - this->size)) {
        this->y = (this->SCREEN_HEIGHT - this->size);
        this->velocity = 0;
    }

    if (this->y < 0) {
        this->y = 0;
        this->velocity = 0;
    }
};

void Bird::Draw() {
    uint32_t prevColor = BSP_LCD_GetBackColor();
    BSP_LCD_SetBackColor(LCD_COLOR_WHITE);

    // Draw it
    BSP_LCD_FillRect(this->x, this->y, this->size, this->size);

    // Restore back color
    BSP_LCD_SetBackColor(prevColor);
};