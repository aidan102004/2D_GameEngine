#pragma once

#include "../game.h"
#include "ecs.h"
#include "components.h"

class InputController : public Component 
{
    public:
        TransformComponent *transform;
        const Uint8* keystates = SDL_GetKeyboardState(NULL); 

        void init() override
        {
            transform = &entity->GetComponent<TransformComponent>();
        }

        void update() override {
            transform->velocity.x = 0;
            transform->velocity.y = 0;

            if (keystates[SDL_SCANCODE_UP] || keystates[SDL_SCANCODE_W]) transform->velocity.y = -1;
            
            if (keystates[SDL_SCANCODE_LEFT] || keystates[SDL_SCANCODE_A]) transform->velocity.x = -1;
            
            if ((keystates[SDL_SCANCODE_DOWN] || keystates[SDL_SCANCODE_S])) transform->velocity.y = 1;
        
            if (keystates[SDL_SCANCODE_RIGHT] || keystates[SDL_SCANCODE_D]) transform->velocity.x = 1;
        }
};
