#ifndef BIRD_H
#define BIRD_H

class Bird
{
    public:
        Bird();

        void Init(int xPos, int yPos, int size, float gravity, float lift);

        int GetX();
        
        int GetY();

        int GetWidth();

        int GetHeight();

        void Up();

        void Update();

        void Draw();

    private:
        int x;
        int y;
        int h;
        int w;
        float g;
        float l;
        float velocity;
        int SCREEN_HEIGHT;
};

#endif