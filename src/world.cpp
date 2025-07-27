#include "world.h"

World::World(int width, int height) : width(width), height(height) {
    // Initialize world
}   

void World::Update() {
    // Update world state
}

void World::Draw() {
    
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            switch (tileMap[i][j])
            {
            case EMPTY:
                DrawRectangle(j * TILE_SIZE, i * TILE_SIZE, TILE_SIZE, TILE_SIZE, WHITE);
                break;
            case SOLID:
                DrawRectangle(j * TILE_SIZE, i * TILE_SIZE, TILE_SIZE, TILE_SIZE, BLACK);
                break;
            case PLATFORM:
                DrawRectangle(j * TILE_SIZE, i * TILE_SIZE, TILE_SIZE, TILE_SIZE, BLUE);
                break;
            }
        }
    }
    
}