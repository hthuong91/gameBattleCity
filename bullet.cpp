#include "bullet.h"
#include "game.h"
bullet::bullet(int startX, int startY, int dirX, int dirY)
{
    x = startX;
    y = startY;
    dx = dirX;
    dy = dirY;
    active = true;
    rect = {x, y, 10, 10} ;
}
void bullet::move () {
    x += dx;
    y += dy;
    rect.x = x;
    rect.y = y;
    if (x < TILE_SIZE || x > SCREEN_WIDTH - TILE_SIZE ||
        y < TILE_SIZE || y > SCREEN_HEIGHT - TILE_SIZE) {
            active = false;
        }
}
void bullet::render (SDL_Renderer* renderer) {
    if (active) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255) ;
        SDL_RenderFillRect (renderer, &rect);
    }
}

