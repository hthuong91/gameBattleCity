
#ifndef ENEMYTANK_H
#define ENEMYTANK_H
#include<SDL.h>
#include<vector>
#include "bullet.h"
#include "wall.h"
using namespace std;
class Game;
class playertank;
class bullet;

class enemytank
{
    public:
        int x, y;
        int dirX, dirY;
        int moveDelay, shootDelay;
        SDL_Rect rect;
        bool active;
        vector<bullet> bullets;
        enemytank(int startX, int startY);
        void move(const vector<wall>& walls);
        void shoot();
        void updateBullets() ;
        void render(SDL_Renderer* renderer);
};

#endif // ENEMYTANK_H
