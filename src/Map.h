#pragma once
#include <vector>
#include <string>
#include <memory>     // Required for std::unique_ptr

class Player;
class Enemy;

// The Map class knows how to draw the world and how to tell
// whether a tile is walkable. It does NOT own the entities.
//
// Enemy list is now a vector of unique_ptr<Enemy> —
// we use const references to avoid copying.
class Map {
public:
    Map();

    // Draw both the player and a list of enemies onto the map.
    // Player is passed by reference.
    // Enemies are pointers inside a vector — we don't copy them.
    void draw(const Player& player,
              const std::vector<std::unique_ptr<Enemy>>& enemies) const;

    bool isWalkable(int x, int y) const;

private:
    std::vector<std::string> tiles;
};
