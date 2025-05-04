#ifndef APP_H
#define APP_H
#include "appstate.h"
#include<SDL_mixer.h>
class App
{
    public:
        App(); // constructor, tạo đối tượng
        ~App(); // destrctor, hủy đối tượng
        void run(); // hàm chạy app
        void eventProces(); // hàm xử lí sự kiện
        Mix_Music* bgm = nullptr;


    private:
        bool is_running; // biến kiểm tra ứng dụng có đang chạy hay không
        AppState* m_app_state; // trạng thái hiện tại của ứng dụng (vd menu, game,...)
        SDL_Window* m_window; // cửa sổ SDL
};

#endif  //APP_H
