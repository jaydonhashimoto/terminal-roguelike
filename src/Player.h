#pragma once
#include "Map.h"

// Represents the player in the game world
class Player {
public:
    int x = 1; // starting x coordinate
    int y = 1; // starting y coordinate

    // Attempts to move the player by (dx, dy)
    void move(int dx, int dy, const Map& map);
};
