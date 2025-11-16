#pragma once
#include <vector>
#include <string>

class Player;

// Represents the static level layout
class Map {
public:
    Map(); // Constructor builds the map

    // Draws the map and overlays the player on top
    void draw(const Player& player) const;

    // Returns true if the tile at (x, y) can be walked on
    bool isWalkable(int x, int y) const;

private:
    std::vector<std::string> tiles; // Each string is one row of the map
};
