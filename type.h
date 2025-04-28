#ifndef TYPE_H
#define TYPE_H

enum SpriteType // kiểu dữ liệu đặc biệt định nghĩa các giá trị hằng số có tên được đánh số thứ tự tăng dần trong 1 enum nếu không định nghĩa sẽ đầu từ 0
{
    // định nghĩa các đối tượng trong game
    ST_TANK_A,
    ST_TANK_B,
    ST_TANK_C,
    ST_TANK_D,

    ST_PLAYER_1,
    ST_PLAYER_2,

    ST_BRICK_WALL,
    ST_STONE_WALL,
    ST_WATER,
    ST_BUSH,
    ST_ICE,

    ST_SHIELD,
    ST_CREATE,
    ST_DESTROY_TANK,
    ST_DESTROY_BULLET,
    ST_BOAT_P1,
    ST_BOAT_P2,

    ST_EAGLE,
    ST_DESTROY_EAGLE,
    ST_FLAG,

    ST_BULLET,

    ST_LEFT_ENEMY,
    ST_STAGE_STATUS,

    ST_TANKS_LOGO,

    ST_NONE
};

enum TankStateFlag
{
    // định nghĩa các trạng thái của xe tăng
    TSF_SHIELD = 1 << 1,     // Khi nhận được mũ bảo hiểm (trạng thái bảo vệ)
    TSF_FROZEN = 1 << 2,      // Khi đối phương nhận được đồng hồ (bị đóng băng)
    TSF_DESTROYED = 1 << 3,   // Khi bị trúng bom từ đối phương hoặc bị bắn trúng
    TSF_BOAT = 1 << 4,        // Khi nhận được thuyền, cho phép đi qua nước
    TSF_ON_ICE = 1 << 6,      // Nếu xe tăng đang ở trên băng, nó sẽ trượt
    TSF_CREATE = 1 << 7,      // Trạng thái đang tạo xe tăng (hiệu ứng spawn)
    TSF_LIFE = 1 << 8,        // Trạng thái mạng sống (có thể dùng cho player)
    TSF_MENU = 1 << 9         // Tăng tốc độ animation gấp đôi (dùng trong menu)
};

enum Direction
{
    // định nghĩa 4 hướng di chuyển/ đạn bắn trong game
    D_UP = 0,
    D_RIGHT = 1,
    D_DOWN = 2,
    D_LEFT = 3
};

#endif // TYPE_H
