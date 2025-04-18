#ifndef BULLET_H
#define BULLET_H
#include<SDL.h>
#include<vector>
class playertank;
class Game;
class bullet
{
    public:
        int x, y;
        int dx, dy;
        SDL_Rect rect;
        bool active;
        bullet(int startX, int startY, int dirX, int dirY);
        void move();
        void render(SDL_Renderer* renderer);
};

#endif // BULLET_H
