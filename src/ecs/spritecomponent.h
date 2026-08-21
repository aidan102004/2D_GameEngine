#pragma once

#include "components.h"
#include "../texturemanager.h"
#include "SDL.h"
#include <iostream>

class SpriteComponent : public Component
{
    private:
        TransformComponent *transform;
        SDL_Texture *texture;
        SDL_Rect srcRect, destRect;
    public:
        SpriteComponent() = default;
        SpriteComponent(const char* path)
        {
            texture = TextureManager::LoadTexture(path);
        }

        void setTexture(const char* path) {
            texture = TextureManager::LoadTexture(path);
            setTextureParams();
        }
        void setTextureParams()
        {
            srcRect.x = 0;
            srcRect.y = 0;
            SDL_QueryTexture(texture, NULL, NULL, &srcRect.w, &srcRect.h); //updates srcRect w and h with texture res
            destRect.w = srcRect.w/4; //note im dividing values by 4
            destRect.h = srcRect.h/4;
        }
        void init() override
        {
            transform = &entity->GetComponent<TransformComponent>();
            setTextureParams();
        }
        void update() override
        {
            destRect.x = static_cast<int>(transform->position.x);
            destRect.y = static_cast<int>(transform->position.y);
        }

        void draw() override
        {
            TextureManager::Draw(texture, srcRect, destRect);
        }
};