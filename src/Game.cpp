#include "Game.h"
#include <iostream>
#include <conio.h>   // For _getch() input (Windows only)
#include <memory>    // For std::make_unique

void Game::run() {
    bool running = true;

    // ------------------------------------------------------------
    //  Allocate the player on the heap.
    //  make_unique removes the need for `new` and ensures
    //  the returned pointer is safely owned by this unique_ptr.
    // ------------------------------------------------------------
    player = std::make_unique<Player>();


    // ------------------------------------------------------------
    //  Spawn one enemy on the heap and store it in the vector.
    //  Using unique_ptr here ensures:
    //    - No need to delete manually
    //    - Clear ownership (the Game owns the enemies)
    // ------------------------------------------------------------
    enemies.emplace_back(std::make_unique<Enemy>(10, 3));


    // ------------------------------------------------------------
    //  MAIN GAME LOOP
    // ------------------------------------------------------------
    while (running) {

        // --------------------------------------------------------
        // Draw the map with:
        //   - player (dereferenced because draw expects a Player&)
        //   - enemies (vector of unique_ptr<Enemy>)
        //
        // Notice we pass *player because:
        //   - player is a pointer (unique_ptr)
        //   - draw() expects a reference to a Player object
        // --------------------------------------------------------
        map.draw(*player, enemies);

        std::cout << "Move with WASD, press q to quit\n";

        // Read a single key press without requiring Enter
        char input = _getch();


        // --------------------------------------------------------
        //                   PLAYER TURN
        //
        // player is a unique_ptr, so use -> to call methods.
        // --------------------------------------------------------
        switch (input) {
            case 'w': player->move(0, -1, map); break;
            case 's': player->move(0, 1, map); break;
            case 'a': player->move(-1, 0, map); break;
            case 'd': player->move(1, 0, map); break;
            case 'q': running = false; break;
        }


        // --------------------------------------------------------
        //                   ENEMY TURN
        //
        // Enemy pointers also use -> to access members.
        // update() moves each enemy one step toward the player.
        //
        // We pass:
        //   player->x  (because player is a pointer)
        // --------------------------------------------------------
        for (auto& enemy : enemies) {
            enemy->update(player->x, player->y, map);
        }
    }
}
