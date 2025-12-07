#include "Game.h"
#include <iostream>
#include <memory>      // For std::make_unique and std::unique_ptr
#include <algorithm>   // For std::remove_if (used to remove dead enemies)

// Platform-specific includes for terminal input
#ifdef _WIN32
    #include <conio.h>  // For _getch() on Windows
#else
    #include <termios.h>  // For terminal settings on Unix/Linux
    #include <unistd.h>   // For read() on Unix/Linux
#endif

// ========================================
//  CROSS-PLATFORM CHARACTER INPUT
// ========================================
// Reads a single character from stdin without waiting for Enter.
// Works on both Windows and Unix-like systems (Linux, macOS).
char Game::getChar() {
#ifdef _WIN32
    // Windows: use _getch() from conio.h
    return _getch();
#else
    // Unix/Linux: modify terminal settings temporarily
    char buf = 0;
    struct termios old = {0};
    
    // Get current terminal settings
    if (tcgetattr(0, &old) < 0) {
        perror("tcgetattr()");
    }
    
    // Disable canonical mode (line buffering) and echo
    old.c_lflag &= ~ICANON;  // Read character by character
    old.c_lflag &= ~ECHO;    // Don't echo characters to screen
    old.c_cc[VMIN] = 1;      // Minimum characters to read
    old.c_cc[VTIME] = 0;     // No timeout
    
    // Apply new settings
    if (tcsetattr(0, TCSANOW, &old) < 0) {
        perror("tcsetattr ICANON");
    }
    
    // Read one character
    if (read(0, &buf, 1) < 0) {
        perror("read()");
    }
    
    // Restore original terminal settings
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if (tcsetattr(0, TCSADRAIN, &old) < 0) {
        perror("tcsetattr ~ICANON");
    }
    
    return buf;
#endif
}

void Game::run() {
    bool running = true;

    // ========================================
    //  INITIALIZATION: Create player & enemies
    // ========================================
    // Allocate the player on the heap using make_unique.
    // make_unique removes the need for `new` and ensures
    // the returned pointer is safely owned by this unique_ptr.
    player = std::make_unique<Player>();

    // Spawn enemies on the heap and store them in the vector.
    // Using unique_ptr ensures:
    //   - No need to manually delete
    //   - Clear ownership (the Game owns the enemies)
    //   - Automatic cleanup when enemies are removed
    enemies.emplace_back(std::make_unique<Enemy>(10, 3));  // Enemy at (10, 3)
    enemies.emplace_back(std::make_unique<Enemy>(15, 5));  // Enemy at (15, 5)

    // ========================================
    //  MAIN GAME LOOP
    // ========================================
    while (running) {

        // ----------------------------------------
        //  RENDER: Draw the game state
        // ----------------------------------------
        // Draw the map with player and all enemies.
        // We pass *player because:
        //   - player is a unique_ptr (pointer)
        //   - draw() expects a reference to a Player object
        //   - *player dereferences the pointer to get the object
        map.draw(*player, enemies);

        // Display game UI
        std::cout << "Player Health: " << player->health << "/" << 20 << "\n";
        std::cout << "Enemies remaining: " << enemies.size() << "\n";
        std::cout << "Move with WASD, press q to quit\n";

        // ----------------------------------------
        //  CHECK GAME OVER CONDITIONS
        // ----------------------------------------
        // Check if player has died (health reached 0)
        if (!player->isAlive()) {
            std::cout << "\nYou died! Game Over.\n";
            break;  // Exit game loop
        }

        // Check if player has won (all enemies defeated)
        if (enemies.empty()) {
            std::cout << "\nAll enemies defeated! You win!\n";
            break;  // Exit game loop
        }

        // ----------------------------------------
        //  INPUT: Get player action
        // ----------------------------------------
        // Read a single key press without requiring Enter
        // Works on both Windows and Linux
        char input = getChar();

        // ----------------------------------------
        //  PROCESS INPUT: Determine movement direction
        // ----------------------------------------
        int dx = 0;  // Horizontal movement delta
        int dy = 0;  // Vertical movement delta
        
        switch (input) {
            case 'w': dy = -1; break;  // Move up (decrease y)
            case 's': dy = 1;  break;  // Move down (increase y)
            case 'a': dx = -1; break;  // Move left (decrease x)
            case 'd': dx = 1;  break;  // Move right (increase x)
            case 'q':                  // Quit game
                running = false;
                continue;  // Skip rest of loop and exit
        }

        // ----------------------------------------
        //  PLAYER TURN: Movement or Attack
        // ----------------------------------------
        // Calculate where player wants to move
        // player is a unique_ptr, so use -> to access members
        int newX = player->x + dx;
        int newY = player->y + dy;

        // Check if an enemy occupies the target position
        bool attackedEnemy = false;
        for (auto& enemy : enemies) {
            // enemy is also a unique_ptr, so use -> to access members
            if (enemy->x == newX && enemy->y == newY) {
                // Enemy found at target position - attack it!
                // Pass *enemy because attack() expects Enemy&, not unique_ptr<Enemy>&
                player->attack(*enemy);
                attackedEnemy = true;
                break;  // Only attack one enemy per turn
            }
        }

        // If we didn't attack an enemy and player pressed a movement key,
        // try to move to the new position (if it's walkable).
        if (!attackedEnemy && (dx != 0 || dy != 0)) {
            player->move(dx, dy, map);
        }

        // ----------------------------------------
        //  ENEMY TURN: Each enemy acts
        // ----------------------------------------
        // Loop through all enemies and let them take their turn.
        // Enemies will move toward player or attack if adjacent.
        // Enemy pointers use -> to access members.
        // update() moves each enemy one step toward the player or attacks.
        for (auto& enemy : enemies) {
            // Pass *player because update() expects Player&, not unique_ptr<Player>&
            enemy->update(*player, map);
        }

        // ----------------------------------------
        //  CLEANUP: Remove dead enemies
        // ----------------------------------------
        // Use erase-remove idiom to remove all dead enemies from vector.
        // std::remove_if shifts dead enemies to end and returns iterator to first dead one.
        // enemies.erase() then removes everything from that point to the end.
        // Note: We use -> because enemy is a unique_ptr
        enemies.erase(
            std::remove_if(enemies.begin(), enemies.end(),
                [](const std::unique_ptr<Enemy>& enemy) { 
                    return !enemy->isAlive();  // Return true for dead enemies (to be removed)
                }),
            enemies.end()
        );
    }  // End of game loop
}
