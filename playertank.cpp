#include "playertank.h"
#include "game.h"
#include "bullet.h"
using namespace std;
playertank::playertank(int startX, int startY) {
    x = startX;
    y = startY;
    rect = {x, y, TILE_SIZE, TILE_SIZE};
    dirX = 0;
    dirY = -1;
}
void playertank::move(int dx, int dy, const vector<wall>& walls) {
    int newX = x + dx;
    int newY = y + dy;
    this->dirX = dx;
    this->dirY = dy;
    SDL_Rect newRect = {newX, newY, TILE_SIZE, TILE_SIZE};

    for (size_t i = 0; i < walls.size(); i++) {
        if (walls[i].active && SDL_HasIntersection(&newRect, &walls[i].rect)) {
            return;
        }
    }

    if (newX >= TILE_SIZE && newX <= SCREEN_WIDTH - TILE_SIZE * 2 &&
        newY >= TILE_SIZE && newY <= SCREEN_HEIGHT - TILE_SIZE * 2) {
        x = newX;
        y = newY;
        rect.x = x;
        rect.y = y;
    }
}

void playertank::render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    SDL_RenderFillRect(renderer, &rect);
    for (auto &bullet : bullets) {
        bullet.render(renderer) ;
    }
}
void playertank::shoot() {
    bullets.push_back(bullet (x + TILE_SIZE / 2 -5,y + TILE_SIZE /2 -5,
                              this->dirX, this->dirY));
}
void playertank::updateBullets() {
    for (auto &bullet : bullets) {
        bullet.move();
    }
    bullets.erase(remove_if(bullets.begin(),bullets.end(),
                                 [](bullet &b) {return !b.active;}), bullets.end());
}











