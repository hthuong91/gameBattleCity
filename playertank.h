#ifndef PLAYERTANK_H
#define PLAYERTANK_H
#include<algorithm>
#include <SDL.h>
#include <vector>
#include "Wall.h"
#include "bullet.h"
using namespace std;
class Game;
class playertank
{
public:
    playertank(int startX, int startY);
    int x, y;
    int dirX, dirY;
    SDL_Rect rect;
    vector<bullet> bullets;
    void move(int dx, int dy, const vector<wall>& walls);
    void render(SDL_Renderer* renderer);
    void shoot();
    void updateBullets();

};

#endif // PLAYERTANK_H
