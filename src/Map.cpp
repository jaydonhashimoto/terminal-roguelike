#include "Map.h"
#include "Player.h"
#include "Enemy.h"
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

void Map::draw(const Player& player, const std::vector<Enemy>& enemies) const {
    // Clear the terminal. Windows only — I can give portable versions.
    system("cls");

    // Loop through each row (y)
    for (int y = 0; y < tiles.size(); ++y) {
        // Loop through each column (x)
        for (int x = 0; x < tiles[y].size(); ++x) {

            bool printed = false;

            // Draw player if they are here
            if (player.x == x && player.y == y) {
                std::cout << '@';
                printed = true;
            }

            // Draw enemies if present on this tile
            for (const auto& enemy : enemies) {
                if (enemy.x == x && enemy.y == y) {
                    std::cout << 'E';
                    printed = true;
                    break;
                }
            }

            // If nothing else printed, draw the map tile
            if (!printed) {
                std::cout << tiles[y][x];
            }
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
