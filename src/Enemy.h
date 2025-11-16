#pragma once
#include "Map.h"

// Represents a basic enemy in the world
class Enemy {
public:
    int x;
    int y;

    Enemy(int startX, int startY);

    // Simple AI: try to move toward player
    void update(int playerX, int playerY, const Map& map);
};
