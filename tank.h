#ifndef TANK_H
#define TANK_H
//#include "object.h"
#include "bullet.h"
//#include "type.h"

#include <vector>

typedef unsigned TankStateFlags;


class Tank : public Object // quản lý cơ chế cơ bản của xe tăng: di chuyển, bắn
{
public:
    Tank(); //tạo xe tăng ở vị trí đầu tiên của kẻ địch
    Tank(double x, double y, SpriteType type); // x vtri ban đầu ngang, y vtri ban dau doc, kieu xe tang
    virtual ~Tank();
    void draw();
    void update(Uint32 dt);
    virtual Bullet* fire();
    SDL_Rect nextCollisionRect(Uint32 dt);
    void setDirection(Direction d);
    void collide(SDL_Rect &intersect_rect);
    virtual void respawn();
    virtual void destroy();
    void setFlag(TankStateFlag flag);
    void clearFlag(TankStateFlag flag);
    bool testFlag(TankStateFlag flag);
    double default_speed;
    double speed;
    bool stop;
    Direction direction;
    std::vector<Bullet*> bullets;
    int lives_count;

protected:
    TankStateFlags m_flags;
    Sint32 m_slip_time;
    Direction new_direction;
    unsigned m_bullet_max_size;
    Object* m_shield;
    Object* m_boat;
    Uint32 m_shield_time;
    Uint32 m_frozen_time;
};

#endif // TANK_H
