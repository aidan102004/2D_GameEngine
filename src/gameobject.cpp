#include "gameobject.h"
#include "texturemanager.h"

GameObject::GameObject(const char* texSheet, int x, int y)
{
    objTexture = TextureManager::LoadTexture(texSheet);
    xpos = x;
    ypos = y;
    srcRect.x = 0;
    srcRect.y = 0;
    SDL_QueryTexture(objTexture, NULL, NULL, &srcRect.w, &srcRect.h);
}

void GameObject::update()
{
    xpos++;
    ypos++;
    destRect.x = xpos;
    destRect.y = ypos;
    destRect.w = srcRect.w;
    destRect.h = srcRect.h;
}

void GameObject::render()
{
    SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}