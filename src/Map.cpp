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

void Map::draw(const Player& player,
               const std::vector<std::unique_ptr<Enemy>>& enemies) const 
{
    // Clear console (cross-platform)
#ifdef _WIN32
    system("cls");    // Windows
#else
    system("clear");  // Linux/macOS
#endif

    // Loop through every tile in the grid
    for (int y = 0; y < tiles.size(); ++y) {
        for (int x = 0; x < tiles[y].size(); ++x) {

            bool printedSomething = false;

            // ----------------------------------------------
            //  Draw the player if it's located at this tile
            // ----------------------------------------------
            if (player.x == x && player.y == y) {
                std::cout << '@';
                printedSomething = true;
            }

            // ----------------------------------------------
            //  Draw enemies if any are located at this tile.
            //
            //  Each enemy is a pointer, so we use enemy->x.
            //
            //  We break after drawing one because you can't
            //  see two enemies on the same tile anyway.
            // ----------------------------------------------
            for (const auto& enemy : enemies) {
                if (enemy->x == x && enemy->y == y) {
                    std::cout << 'E';
                    printedSomething = true;
                    break;
                }
            }

            // ----------------------------------------------
            //  If nothing is drawn yet (player/enemy isn't here),
            //  print the underlying map tile.
            // ----------------------------------------------
            if (!printedSomething) {
                std::cout << tiles[y][x];
            }
        }
        std::cout << '\n'; // End of row
    }
}

bool Map::isWalkable(int x, int y) const {
    // Check boundaries first to avoid out-of-range access
    if (y < 0 || y >= tiles.size()) return false;
    if (x < 0 || x >= tiles[y].size()) return false;

    // Only '.' counts as walkable
    return tiles[y][x] == '.';
}
