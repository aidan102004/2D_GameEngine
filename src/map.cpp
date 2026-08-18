#include "map.h"
#include "texturemanager.h"

vector<vector<int>> lvl1(20, vector<int>(25, 0));

Map::Map()
{
    dirt = TextureManager::LoadTexture("assets/dirt.png");
    grass = TextureManager::LoadTexture("assets/grass.png");
    water = TextureManager::LoadTexture("assets/water.png");

    LoadMap(lvl1);

    src.x = 0;
    src.y = 0;
    src.w = dest.w = 32;
    src.h = dest.h = 32;

    dest.x = dest.y = 0;
}
void Map::LoadMap(vector<vector<int>>& vec)
{
    map = vec;
}

void Map::DrawMap()
{
    int type = 0;
    for (size_t row = 0; row < map.size(); row++) {
        for (size_t col = 0; col < map[row].size(); col++) {
            type = map[row][col];
            dest.x = col * 32;
            dest.y = row * 32;
            switch (type) {
                case 0:
                    TextureManager::Draw(water, src, dest);
                    break;
                case 1:
                    TextureManager::Draw(grass, src, dest);
                    break;
                case 2:
                    TextureManager::Draw(dirt, src, dest);
                    break; // still missing this from before
            }
        }
    }
}