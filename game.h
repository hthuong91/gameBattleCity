#ifndef GAME_H
#define GAME_H
using namespace std;
#include <SDL.h>
#include <iostream>
#include <vector>
#include "Wall.h"
#include "playertank.h"
#include "enemytank.h"

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
    vector<wall> walls;
    playertank player;
    int enemyNumber = 3;
    vector<enemytank> enemies;
    Game();
    void generateWalls();
    void render();
    void run();
    void handleEvents();
    void update();
    void spawnenemies();
    ~Game();
};

#endif
