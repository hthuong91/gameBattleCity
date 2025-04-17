#ifndef PLAYERTANK_H
#define PLAYERTANK_H

#include <SDL.h>
#include <vector>
#include "Wall.h"

class playertank
{
public:
    playertank(int startX, int startY);
    int x, y;
    int dirX, dirY;
    SDL_Rect rect;
    void move(int dx, int dy, const std::vector<wall>& walls);
    void render(SDL_Renderer* renderer);
};

#endif // PLAYERTANK_H
