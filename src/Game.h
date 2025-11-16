#pragma once
#include "Map.h"
#include "Player.h"
#include "Enemy.h"

// The Game class controls the main loop:
// - Draw map
// - Handle input
// - Update player
// - Repeat
class Game {
public:
    // Runs the main game loop
    void run();

private:
    Map map;       // The game world grid
    Player player; // The player's position & movement
    std::vector<Enemy> enemies; // NEW: store enemies
};
