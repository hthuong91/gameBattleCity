
#ifndef WALL_H
#define WALL_H
#include <SDL.h>

class wall
{
public:
    int x, y;
    SDL_Rect rect;
    bool active;

    wall(int startX, int startY);
    void render(SDL_Renderer* renderer);
};

#endif
