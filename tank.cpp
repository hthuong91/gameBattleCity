#include "tank.h"
#include "appconfig.h"
#include <algorithm>
Tank::Tank() //khởi tạo xe tăng ở vị trí và loại mặc định
    : Object(AppConfig::enemy_starting_point.at(0).x, AppConfig::enemy_starting_point.at(0).y, ST_TANK_A)
{
    // khởi tạo giá trị mặc định
    direction = D_UP;
    m_slip_time = 0;
    default_speed = AppConfig::tank_default_speed;
    speed = 0.0;
    m_shield = nullptr; //khiên bảo vệ
    m_shield_time = 0;
}

Tank::Tank(double x, double y, SpriteType type)
    : Object(x, y, type)
{
    direction = D_UP;
    m_slip_time = 0;
    default_speed = AppConfig::tank_default_speed;
    speed = 0.0;
    m_shield = nullptr;
    m_shield_time = 0;
}

Tank::~Tank()
{
    for(auto bullet : bullets) delete bullet;
    bullets.clear();

    if(m_shield != nullptr)
    {
        delete m_shield;
        m_shield = nullptr;
    }
}

void Tank::draw()
{
    if(to_erase) return;
    Object::draw();

    if(testFlag(TSF_SHIELD) && m_shield != nullptr) m_shield->draw();

    for(auto bullet : bullets)
        if(bullet != nullptr) bullet->draw();
}

void Tank::update(Uint32 dt) //cập nhật vị trí, trạng thái xử lí va chạm quản lí thời gian các hiệu ứng, xóa đạn đã bị hủy
{
    if(to_erase) return;
    if(testFlag(TSF_LIFE))
    {
        if (!stop)
        {
            switch (direction)
            {
            case D_UP:
                pos_y -= speed * dt;
                break;
            case D_RIGHT:
                pos_x += speed * dt;
                break;
            case D_DOWN:
                pos_y += speed * dt;
                break;
            case D_LEFT:
                pos_x -= speed * dt;
                break;
            }
        }

        dest_rect.x = pos_x;
        dest_rect.y = pos_y;
        dest_rect.h = m_sprite->rect.h;
        dest_rect.w = m_sprite->rect.w;
        //cập nhật hình chữ nhật va chạm
        collision_rect.x = dest_rect.x + 2;
        collision_rect.y = dest_rect.y + 2;
        collision_rect.h = dest_rect.h - 4;
        collision_rect.w = dest_rect.w - 4;
    }
    //cập nhật khiên bảo vệ
    if(testFlag(TSF_SHIELD) && m_shield != nullptr)
    {
        m_shield_time += dt;
        m_shield->pos_x = pos_x;
        m_shield->pos_y = pos_y;
        m_shield->update(dt);
        if(m_shield_time > AppConfig::tank_shield_time) clearFlag(TSF_SHIELD);
    }
    if(m_sprite->frames_count > 1 && (testFlag(TSF_LIFE) ? speed > 0 : true))
    {
        m_frame_display_time += dt;
        if(m_frame_display_time > (testFlag(TSF_MENU)  ? m_sprite->frame_duration / 2 : m_sprite->frame_duration))
        {
            m_frame_display_time = 0;
            m_current_frame++;
            if(m_current_frame >= m_sprite->frames_count)
            {
                if(m_sprite->loop) m_current_frame = 0;
                else if(testFlag(TSF_CREATE))
                {
                    m_sprite = Engine::getEngine().getSpriteConfig()->getSpriteData(type);
                    clearFlag(TSF_CREATE);
                    setFlag(TSF_LIFE);
                    m_current_frame = 0;
                }
                else if(testFlag(TSF_DESTROYED))
                {
                    m_current_frame = m_sprite->frames_count;
                    if(lives_count > 0) respawn();
                    else if(bullets.size() == 0) to_erase = true;
                }
            }
        }
    }


    // Xử lí đạn
    for(auto bullet : bullets) bullet->update(dt);
    bullets.erase(std::remove_if(bullets.begin(), bullets.end(), [](Bullet*b){if(b->to_erase) {delete b; return true;} return false;}), bullets.end());
}

Bullet* Tank::fire()
{
    if(!testFlag(TSF_LIFE)) return nullptr;

    if(bullets.size() < m_bullet_max_size)
    {
        // Xác định xe tăng này có phải là người chơi không
        bool is_player_bullet = (type == ST_PLAYER_1 || type == ST_PLAYER_2);

        Bullet* bullet = new Bullet(pos_x, pos_y, is_player_bullet);
        bullets.push_back(bullet);

        Direction tmp_d = direction;

        switch(tmp_d)
        {
        case D_UP:
            bullet->pos_x += (dest_rect.w - bullet->dest_rect.w) / 2;
            bullet->pos_y -= bullet->dest_rect.h - 4;
            break;
        case D_RIGHT:
            bullet->pos_x += dest_rect.w - 4;
            bullet->pos_y += (dest_rect.h - bullet->dest_rect.h) / 2;
            break;
        case D_DOWN:
            bullet->pos_x += (dest_rect.w - bullet->dest_rect.w) / 2;
            bullet->pos_y += dest_rect.h - 4;
            break;
        case D_LEFT:
            bullet->pos_x -= bullet->dest_rect.w - 4;
            bullet->pos_y += (dest_rect.h - bullet->dest_rect.h) / 2;
            break;
        }

        bullet->direction = tmp_d;

        if(type == ST_TANK_C || type == ST_PLAYER_2) // giả sử player 2 mạnh hơn
            bullet->speed = AppConfig::bullet_default_speed * 1.3;
        else
            bullet->speed = AppConfig::bullet_default_speed;

        bullet->update(0); // cập nhật lại dest_rect dựa trên vị trí mới

        return bullet;
    }

    return nullptr;
}



SDL_Rect Tank::nextCollisionRect(Uint32 dt)
{
    if(speed == 0) return collision_rect;

    SDL_Rect r;
    int a = 1;
    switch (direction)
    {
    case D_UP:
        r.x = collision_rect.x;
        r.y = collision_rect.y - default_speed * dt - a;
        break;
    case D_RIGHT:
        r.x = collision_rect.x + default_speed * dt + a;
        r.y = collision_rect.y;
        break;
    case D_DOWN:
        r.x = collision_rect.x;
        r.y = collision_rect.y + default_speed * dt + a;
        break;
    case D_LEFT:
        r.x = collision_rect.x - default_speed * dt - a;
        r.y = collision_rect.y;
        break;
    }
    r.h = collision_rect.h;
    r.w = collision_rect.w;

    return r;
}

void Tank::setDirection(Direction d) //xử lí hướng thay đổi (cả th trượt trên băng)
{
    if(!(testFlag(TSF_LIFE) || testFlag(TSF_CREATE))) return;

    direction = d;

    if(!stop)
    {
        double epsilon = 5;
        int pos_x_tile, pos_y_tile;
        switch (direction)
        {
        case D_UP:
        case D_DOWN:
            pos_x_tile = ((int)(pos_x / AppConfig::tile_rect.w)) * AppConfig::tile_rect.w;
            if(pos_x - pos_x_tile < epsilon) pos_x = pos_x_tile;
            else if(pos_x_tile + AppConfig::tile_rect.w - pos_x < epsilon) pos_x = pos_x_tile + AppConfig::tile_rect.w;
            break;
        case D_RIGHT:
        case D_LEFT:
            pos_y_tile = ((int)(pos_y / AppConfig::tile_rect.h)) * AppConfig::tile_rect.h;
            if(pos_y - pos_y_tile < epsilon) pos_y = pos_y_tile;
            else if(pos_y_tile + AppConfig::tile_rect.h - pos_y < epsilon) pos_y = pos_y_tile + AppConfig::tile_rect.h;
            break;
        }
    }
}

void Tank::collide(SDL_Rect &intersect_rect) // dừng xe khi va chạm với vật cản
{
    if(intersect_rect.w > intersect_rect.h) {// Va chạm từ phía trên hoặc phía dưới
        if((direction == D_UP && intersect_rect.y <= collision_rect.y) ||
                (direction == D_DOWN && (intersect_rect.y + intersect_rect.h) >= (collision_rect.y + collision_rect.h)))
        {
            stop = true;
            m_slip_time = 0;
        }
    }
    else
    {
        if((direction == D_LEFT && intersect_rect.x <= collision_rect.x) ||
                (direction == D_RIGHT && (intersect_rect.x + intersect_rect.w) >= (collision_rect.x + collision_rect.w)))
        {
            stop = true;
            m_slip_time = 0;
        }
    }
}

void Tank::destroy() // kích hoạt hiệu ứng nổ và xử lí hồi sinh hoặc xóa xe tăng
{
    if(!testFlag(TSF_LIFE)) return;

    stop = true;
    m_flags = TSF_DESTROYED; // đánh dấu xe tăng bị hủy

    m_frame_display_time = 0;
    m_current_frame = 0;
    direction = D_UP;
    speed = 0;
    m_slip_time = 0;
    m_sprite = Engine::getEngine().getSpriteConfig()->getSpriteData(ST_DESTROY_TANK);
    //hiệu ứng nổ
    collision_rect.x = 0;
    collision_rect.y = 0;
    collision_rect.h = 0;
    collision_rect.w = 0;

    dest_rect.x = pos_x + (dest_rect.w - m_sprite->rect.w)/2;
    dest_rect.y = pos_y + (dest_rect.h - m_sprite->rect.h)/2;
    dest_rect.h = m_sprite->rect.h;
    dest_rect.w = m_sprite->rect.w;
}

void Tank::setFlag(TankStateFlag flag)
{
    if(flag == TSF_SHIELD)
    {
        if(m_shield == nullptr) m_shield = new Object(pos_x, pos_y, ST_SHIELD);
         m_shield_time = 0;
    }

    m_flags |= flag;
}

void Tank::clearFlag(TankStateFlag flag)
{
    if(flag == TSF_SHIELD)
    {
         if(m_shield != nullptr) delete m_shield;
         m_shield = nullptr;
         m_shield_time = 0;
    }

    m_flags &= ~flag;
}

bool Tank::testFlag(TankStateFlag flag)
{
    return (m_flags & flag) == flag;
}

void Tank::respawn() //hiệu ứng hồi sinh đặt lại trạng thái
{
    m_sprite = Engine::getEngine().getSpriteConfig()->getSpriteData(ST_CREATE);
    speed = 0.0;
    stop = false;
    m_slip_time = 0;

    clearFlag(TSF_SHIELD);
    m_flags = TSF_LIFE;
    update(0);
    m_flags = TSF_CREATE; // Đặt lại tất cả các cờ (flag) khác

    // Thiết lập hình chữ nhật va chạm sau khi gọi hàm update
    collision_rect.x = 0;
    collision_rect.y = 0;
    collision_rect.h = 0;
    collision_rect.w = 0;
}
