#ifndef BRICK_H
#define BRICK_H

#include "object.h"

class Brick : public Object
{
public:

    Brick();

    Brick(double x, double y);

    void update(Uint32 dt){}; // không làm gì cả không thay đổi collision_rect

    void bulletHit(Direction bullet_direction);
private:

    int m_collision_count;

    int m_state_code;
};

#endif // BRICK_H
