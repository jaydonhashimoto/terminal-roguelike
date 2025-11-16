#include "Game.h"
#include <iostream>
#include <conio.h> // For _getch() on Windows (I can give Linux/macOS version)

void Game::run() {
    bool running = true;

    // Spawn an enemy at (10, 3)
    enemies.emplace_back(10, 3);

    while (running) {
        // Draw the map and the player's and enemies' position on it
        map.draw(player, enemies);

        std::cout << "Move with WASD, press q to quit\n";

        // Get a single key without needing Enter
        char input = _getch();

        // Handle movement input
        switch (input) {
            case 'w': player.move(0, -1, map); break; // up
            case 's': player.move(0, 1, map); break;  // down
            case 'a': player.move(-1, 0, map); break; // left
            case 'd': player.move(1, 0, map); break;  // right
            case 'q': running = false; break;         // quit game
        }

        // ---- ENEMY TURN ----
        for (auto& enemy : enemies) {
            enemy.update(player.x, player.y, map);
        }
    }
}
