#ifndef BULLET_H
#define BULLET_H
#include<SDL.h>
#include"object.h"
#include<SDL_mixer.h>
class Bullet : public Object
{
public:

    Bullet();

    Bullet(double x, double y, bool from_player = false);

    void update(Uint32 dt);

    void destroy();

    double speed;

    bool collide;

    bool increased_damage;

    Direction direction;

    static bool loadAssets();
    static void cleanupAssets();

private:
    static Mix_Chunk* sfx_shoot;
    bool is_player_bullet;
};

#endif // BULLET_H
