#include "Map.h"
#include "Player.h"
#include <iostream>

Map::Map() {
    // Each string is a row of the dungeon.
    // '#' = wall
    // '.' = floor
    tiles = {
        "####################",
        "#..................#",
        "#.............##...#",
        "#..................#",
        "#....##............#",
        "#..................#",
        "####################"
    };
}

void Map::draw(const Player& player) const {
    // Clear the terminal. Windows only — I can give portable versions.
    system("cls");

    // Loop through each row (y)
    for (int y = 0; y < tiles.size(); ++y) {
        // Loop through each column (x)
        for (int x = 0; x < tiles[y].size(); ++x) {

            // If this position matches the player's coordinates,
            // print the @ symbol instead of the floor.
            if (player.x == x && player.y == y)
                std::cout << '@';
            else
                std::cout << tiles[y][x];
        }
        std::cout << '\n';
    }
}

bool Map::isWalkable(int x, int y) const {
    // Check boundaries first to avoid out-of-range access
    if (y < 0 || y >= tiles.size()) return false;
    if (x < 0 || x >= tiles[y].size()) return false;

    // Only '.' counts as walkable
    return tiles[y][x] == '.';
}
