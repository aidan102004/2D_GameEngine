#include "game.h"
#include <iostream>
#include "texturemanager.h"
#include "map.h"
#include "ecs/components.h"
#include "ecs/spritecomponent.h"
#include "vector2d.h"


Map* map;
SDL_Renderer* Game::renderer = nullptr;

EntityManager manager;
auto &player(manager.addEntity());

Game::Game() {

}
Game::~Game() {

}

void Game::init(const char* title, int x_pos, int y_pos, int width, int height, bool fullscreen) 
{
    Uint32 flags = 0;
    if (fullscreen)
        flags = SDL_WINDOW_FULLSCREEN;
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) 
    {
        std::cout << "Sub-systems Initialised" << std::endl;

        window = SDL_CreateWindow(title, x_pos, y_pos, width, height, flags);
        if (window) 
            std::cout << "Window created" << std::endl;

        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer)
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            std::cout << "Renderer created" << std::endl;
        }
            
        is_running = true;
    } else {
        is_running = false;
    }
    map = new Map();

    //ecs implementation
    player.addComponent<TransformComponent>();
    player.addComponent<SpriteComponent>("assets/player.png");
}

void Game::handle_events() 
{
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type) {
        case SDL_QUIT:
            is_running = false;
            break;
        default:
            break;
    }
}

void Game::update() 
{
    manager.refresh();
    manager.update();
    player.GetComponent<TransformComponent>().position.Add(Vector2D(5, 0));
    if (player.GetComponent<TransformComponent>().position.x > 100) 
    {
        player.GetComponent<SpriteComponent>().setTexture("assets/player1.png");
    }
    
}

void Game::render()
{
    SDL_RenderClear(renderer);
    map->DrawMap();
    manager.draw();
    SDL_RenderPresent(renderer);
}

void Game::clean() 
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Game Cleaned" << std::endl;
}