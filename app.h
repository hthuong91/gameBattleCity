#ifndef APP_H
#define APP_H
#include

class App
{
    public:
        App();
        ~App();
        void run();
        void eventProces();
    private:
        bool is_running;
        AppState* m_app_state;
        SDL_Window* m_window;
};

#endif // APP_H
