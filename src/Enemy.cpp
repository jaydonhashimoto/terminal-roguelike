#include "Enemy.h"
#include "Player.h"  // Now we need the full definition since we access Player members

// Constructor: initialize enemy position
Enemy::Enemy(int startX, int startY)
    : x(startX), y(startY) {}

// AI logic: move toward player or attack if adjacent
void Enemy::update(Player& player, const Map& map) {
    // Calculate movement direction toward player
    int dx = 0;
    int dy = 0;

    // Determine horizontal movement direction
    if (player.x > x) {
        dx = 1;   // Player is to the right, move right
    } else if (player.x < x) {
        dx = -1;  // Player is to the left, move left
    }

    // Determine vertical movement direction
    if (player.y > y) {
        dy = 1;   // Player is below, move down
    } else if (player.y < y) {
        dy = -1;  // Player is above, move up
    }

    // Calculate target position (one step toward player)
    int newX = x + dx;
    int newY = y + dy;

    // Check if player occupies the target position
    if (newX == player.x && newY == player.y) {
        // Player is adjacent! Attack instead of moving.
        attack(player);
    }
    // If no player at target position, try to move there
    else if (map.isWalkable(newX, newY)) {
        // Target tile is empty and walkable, move there
        x = newX;
        y = newY;
    }
    // Otherwise, enemy can't move (blocked by wall or another enemy)
}

void Enemy::attack(Player& player) {
    // Deal damage to the player equal to our attack power.
    // The player's takeDamage method handles reducing their health.
    player.takeDamage(attackPower);
}

void Enemy::takeDamage(int damage) {
    // Reduce health by the damage amount
    health -= damage;
    
    // Ensure health doesn't go negative (cap at 0)
    if (health < 0) health = 0;
}
