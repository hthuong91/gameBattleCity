#include "bullet.h"
#include "appconfig.h"

Mix_Chunk* Bullet::sfx_shoot = nullptr;

Bullet::Bullet(double x, double y, bool from_player)
    : Object(x, y, ST_BULLET), is_player_bullet(from_player)
{
    speed = 0.0;
    direction = D_UP;
    increased_damage = false;
    collide = false;

    // Chỉ phát âm thanh nếu là đạn người chơi
    if (is_player_bullet && sfx_shoot) {
        Mix_PlayChannel(-1, sfx_shoot, 0);
    }
}

void Bullet::update(Uint32 dt) {
    if (!collide) {
        switch (direction) {
            case D_UP:    pos_y -= speed * dt; break;
            case D_RIGHT: pos_x += speed * dt; break;
            case D_DOWN:  pos_y += speed * dt; break;
            case D_LEFT:  pos_x -= speed * dt; break;
        }
        src_rect = moveRect(m_sprite->rect, direction, 0);
        Object::update(dt);
    } else if (m_sprite->frames_count > 1) {
        m_frame_display_time += dt;
        if (m_frame_display_time > m_sprite->frame_duration) {
            m_frame_display_time = 0;
            m_current_frame++;
            if (m_current_frame >= m_sprite->frames_count)
                to_erase = true;

            src_rect = moveRect(m_sprite->rect, 0, m_current_frame);
        }
    }
}

void Bullet::destroy() {
    if (collide) return;

    collide = true;
    speed = 0;
    m_current_frame = 0;
    m_frame_display_time = 0;
    m_sprite = Engine::getEngine().getSpriteConfig()->getSpriteData(ST_DESTROY_BULLET);

    switch (direction) {
        case D_UP:
            dest_rect.x = pos_x + (dest_rect.w - m_sprite->rect.w) / 2;
            dest_rect.y = pos_y - m_sprite->rect.h / 2;
            break;
        case D_RIGHT:
            dest_rect.x = pos_x + dest_rect.w - m_sprite->rect.w / 2;
            dest_rect.y = pos_y + (dest_rect.h - m_sprite->rect.h) / 2;
            break;
        case D_DOWN:
            dest_rect.x = pos_x + (dest_rect.w - m_sprite->rect.w) / 2;
            dest_rect.y = pos_y + dest_rect.h - m_sprite->rect.h / 2;
            break;
        case D_LEFT:
            dest_rect.x = pos_x - m_sprite->rect.w / 2;
            dest_rect.y = pos_y + (dest_rect.h - m_sprite->rect.h) / 2;
            break;
    }

    dest_rect.w = m_sprite->rect.w;
    dest_rect.h = m_sprite->rect.h;

    src_rect = m_sprite->rect;
}

bool Bullet::loadAssets() {
    sfx_shoot = Mix_LoadWAV("audio/shoot.wav");
    if (!sfx_shoot) {
        std::cerr << "Failed to load shoot sound: " << Mix_GetError() << std::endl;
        return false;
    }
    return true;
}

void Bullet::cleanupAssets() {
    if (sfx_shoot) {
        Mix_FreeChunk(sfx_shoot);
        sfx_shoot = nullptr;
    }
}
