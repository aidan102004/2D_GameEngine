#pragma once
#include "game.h"

class GameObject 
{
    public:
        GameObject(const char* texSheet, SDL_Renderer* ren, int x, int y);
        ~GameObject();

        void update();
        void render();
    private:
        int xpos;
        int ypos;

        SDL_Texture* objTexture;
        SDL_Rect srcRect, destRect;
        SDL_Renderer* renderer;
};