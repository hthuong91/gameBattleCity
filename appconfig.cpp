#include "appconfig.h"

string AppConfig::texture_path = "texture.png";
string AppConfig::levels_path = "bin/Debug/levels/";
string AppConfig::font_name = "prstartk.ttf";
string AppConfig::game_over_text = "GAME OVER";
SDL_Rect AppConfig::map_rect = {0, 0, 26*16, 26*16};
SDL_Rect AppConfig::status_rect = {26*16, 0, 3*16, AppConfig::map_rect.h};
SDL_Rect AppConfig::windows_rect = {0, 0, AppConfig::map_rect.w + AppConfig::status_rect.w, AppConfig::map_rect.h};
SDL_Rect AppConfig::tile_rect = {0, 0, 16, 16 };
const SDL_Scancode AppConfig::P1_FIRE_KEY = SDL_SCANCODE_SPACE;
const SDL_Scancode AppConfig::P2_FIRE_KEY = SDL_SCANCODE_Q;


vector<SDL_Point> AppConfig::player_starting_point = // tọa độ người chơi xuất hiện
[]{
    vector<SDL_Point> v;
    v.push_back({128, 384});
    v.push_back({256, 384});
    return v;
}();
vector<SDL_Point> AppConfig::enemy_starting_point = // tọa độ địch xuất hiện
[]{
    vector<SDL_Point> v;
    v.push_back({1, 1});
    v.push_back({192, 1});
    v.push_back({384, 1});
    return v;
}();
vector<Player::PlayerKeys> AppConfig::player_keys = // các phím điều khiển người chơi
[]{
    vector<Player::PlayerKeys> v;
    v.push_back({SDL_SCANCODE_UP, SDL_SCANCODE_DOWN, SDL_SCANCODE_LEFT, SDL_SCANCODE_RIGHT, AppConfig::P1_FIRE_KEY});
    v.push_back({SDL_SCANCODE_W, SDL_SCANCODE_S, SDL_SCANCODE_A, SDL_SCANCODE_D, AppConfig::P2_FIRE_KEY});

    return v;
}();
unsigned AppConfig::level_start_time = 2000;        // Thời gian bắt đầu màn chơi (miligiây)
unsigned AppConfig::slip_time = 380;                // Thời gian trượt/lướt (miligiây)
unsigned AppConfig::enemy_start_count = 4;          // Số lượng kẻ địch xuất hiện ban đầu
unsigned AppConfig::enemy_redy_time = 500;          // Thời gian chờ kẻ địch sẵn sàng (miligiây)
unsigned AppConfig::player_bullet_max_size = 2;     // Số lượng đạn tối đa người chơi có thể bắn ra cùng lúc
unsigned AppConfig::score_show_time = 3000;         // Thời gian hiển thị điểm số (miligiây)
unsigned AppConfig::tank_shield_time = 10000;       // Thời gian xe tăng được bảo vệ (miligiây)
unsigned AppConfig::tank_frozen_time = 8000;        // Thời gian xe tăng bị đóng băng (miligiây)
unsigned AppConfig::level_end_time = 1000;          // Thời gian kết thúc màn chơi (miligiây)
unsigned AppConfig::protect_eagle_time = 15000;     // Thời gian bảo vệ đại bàng (miligiây)
unsigned AppConfig::player_reload_time = 120;       // Thời gian nạp đạn của người chơi (miligiây)

int AppConfig::enemy_max_count_on_map = 4;          // số lượng kẻ địch cần tiêu diệt để chiến thắng

double AppConfig::game_over_entry_speed = 0.13;     // Tốc độ chuyển cảnh khi kết thúc trò chơi
double AppConfig::tank_default_speed = 0.08;        // Tốc độ mặc định của xe tăng
double AppConfig::bullet_default_speed = 0.23;      // Tốc độ mặc định của đạn

bool AppConfig::show_enemy_target = false;          // Có hiển thị mục tiêu của kẻ địch hay không
