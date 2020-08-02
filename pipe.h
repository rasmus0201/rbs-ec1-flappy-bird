#ifndef PIPE_H
#define PIPE_H

#include "mbed.h"
#include "bird.h"

class Pipe
{
    public:
        Pipe(int width, int spacingHole, int movingSpeed);

        bool Collides(Bird r);

        bool OffScreen();

        void Update();

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