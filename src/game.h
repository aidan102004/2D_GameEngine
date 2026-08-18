#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>

class Game 
{
    public:
        Game();
        ~Game();
        void init(const char* title, int x_pos, int y_pos, int width, int height, bool fullscreen);
        void handle_events();
        void update();
        void render();
        void clean();

        inline bool running() {return is_running;};
        static SDL_Renderer* renderer;
    private:
        int cnt{0};
        bool is_running;
        SDL_Window *window;

};