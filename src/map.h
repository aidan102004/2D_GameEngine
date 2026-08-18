#pragma once
#include "game.h"
#include <vector>
using std::vector;

class Map
{
    public:
        Map();
        ~Map();
    
        void LoadMap(vector<vector<int>>& arr);
        void DrawMap();
    private:
        SDL_Rect src, dest;
        SDL_Texture* dirt;
        SDL_Texture* grass;
        SDL_Texture* water;

        vector<vector<int>> map;
};