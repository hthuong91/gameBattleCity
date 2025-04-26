#include "app.h"
#include "appconfig.h"
#include "engine.h"
#include "game.h"
#include "menu.h"

#include <ctime>
#include <iostream>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

App::App()
{
    m_window = nullptr; // khởi tại m_window là con trỏ không troe đến đâu cả
}

App::~App()
{
    if (m_app_state != nullptr)
        delete m_app_state; // giải phóng bộ nhớ của m_app_state nếu nó không phải nullptr
}
void App::run()
{
    is_running = true;

    // Khởi tạo SDL và các thư viện
    if(SDL_Init(SDL_INIT_VIDEO) == 0)
    {
        m_window = SDL_CreateWindow("TANKS", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                  AppConfig::windows_rect.w, AppConfig::windows_rect.h,
                                  SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
        if(m_window == nullptr) return;
        if(!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) return;
        if(TTF_Init() == -1) return;

        srand(time(NULL));

        // Khởi tạo engine
        Engine& engine = Engine::getEngine();
        engine.initModules();
        engine.getRenderer()->loadTexture(m_window);
        engine.getRenderer()->loadFont();

        // Khởi tạo trạng thái ban đầu
        m_app_state = new Menu;

        // Biến quản lý FPS
        const int TARGET_FPS = 60;
        const int FRAME_DELAY = 1000 / TARGET_FPS;
        Uint32 frameStart, frameTime;
        Uint32 lastFPSCheck = SDL_GetTicks();
        int frameCount = 0;
        float fps = 0;

        // Vòng lặp chính
        while(is_running)
        {
            frameStart = SDL_GetTicks();

            // Xử lý thay đổi trạng thái
            if (m_app_state->finished())
            {
                AppState* new_state = m_app_state->nextState();
                delete m_app_state;
                m_app_state = new_state;
                if(m_app_state == nullptr) break;
            }

            // Xử lý sự kiện
            eventProces();

            // Cập nhật và render
            m_app_state->update(FRAME_DELAY);
            m_app_state->draw();

            // Giới hạn FPS
            frameTime = SDL_GetTicks() - frameStart;
            if(frameTime < FRAME_DELAY) {
                SDL_Delay(FRAME_DELAY - frameTime);
            }

            // Tính toán FPS (cho mục đích debug)
            frameCount++;
            if(SDL_GetTicks() - lastFPSCheck >= 1000) {
                fps = frameCount / ((SDL_GetTicks() - lastFPSCheck) / 1000.0f);
                std::cout << "FPS: " << fps << std::endl;
                frameCount = 0;
                lastFPSCheck = SDL_GetTicks();
            }
        }

        // Dọn dẹp
        engine.destroyModules();
    }

    // Giải phóng tài nguyên
    SDL_DestroyWindow(m_window);
    m_window = nullptr;
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}


void App::eventProces()
{
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        if(event.type == SDL_QUIT)
        {
            is_running = false; // Đóng ứng dụng khi nhận được sự kiện thoát
        }
        else if(event.type == SDL_WINDOWEVENT)
        {
            // Cập nhật lại kích thước cửa sổ khi người dùng thay đổi kích thước
            if(event.window.event == SDL_WINDOWEVENT_RESIZED ||
               event.window.event == SDL_WINDOWEVENT_MAXIMIZED ||
               event.window.event == SDL_WINDOWEVENT_RESTORED ||
               event.window.event == SDL_WINDOWEVENT_SHOWN)
            {
                AppConfig::windows_rect.w = event.window.data1;
                AppConfig::windows_rect.h = event.window.data2;
                Engine::getEngine().getRenderer()->setScale((float)AppConfig::windows_rect.w / (AppConfig::map_rect.w + AppConfig::status_rect.w),
                                                            (float)AppConfig::windows_rect.h / AppConfig::map_rect.h);
            }
        }

        m_app_state->eventProcess(&event); // Truyền sự kiện cho trạng thái hiện tại xử lý
    }
}
