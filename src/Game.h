#pragma once
#include "Map.h"
#include "Player.h"
#include "Enemy.h"
#include <memory>     // Required for std::unique_ptr
#include <vector>     // Store multiple enemies

// The Game class controls the entire flow of the program.
// It owns:
//   - The map
//   - The player (as a pointer)
//   - All enemies (as a vector of pointers)
//
// Converting to pointers is a realistic architectural change.
// In larger games, entities are almost always heap-allocated.
//
class Game {
public:
    // Main game loop (runs until user quits)
    void run();

private:
    // Cross-platform function to read a single character without echo
    char getChar();

    Map map;   // Still stored by value since it's simple and static

    // The player is now dynamically allocated on the heap.
    // unique_ptr means:
    //  - exactly one owner (Game)
    //  - auto-cleanup when Game is destroyed
    std::unique_ptr<Player> player;

    // All enemies will be stored as pointers too.
    // This avoids copying enemy objects and prepares us
    // for polymorphism and complex behaviors.
    std::vector<std::unique_ptr<Enemy>> enemies;
};
