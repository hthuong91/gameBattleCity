#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <iostream>
#include <vector>
#include "Wall.h"
#include "Playertank.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int TILE_SIZE = 40;
const int MAP_WIDTH = SCREEN_WIDTH / TILE_SIZE;
const int MAP_HEIGHT = SCREEN_HEIGHT / TILE_SIZE;

class Game
{
public:
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool running;
    std::vector<wall> walls;
    playertank player;

    Game();
    void generateWalls();
    void render();
    void run();
    void handlEvents();
    ~Game();
};

#endif
