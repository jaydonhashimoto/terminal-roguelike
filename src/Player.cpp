#include "Player.h"
#include "Enemy.h"  // Now we need the full definition since we call Enemy methods

void Player::move(int dx, int dy, const Map& map) {
    // Calculate where the player wants to move
    int newX = x + dx;
    int newY = y + dy;

    // Only update position if the destination tile is walkable.
    // This prevents walking through walls.
    if (map.isWalkable(newX, newY)) {
        x = newX;
        y = newY;
    }
}

void Player::attack(Enemy& enemy) {
    // Deal damage to the enemy equal to our attack power.
    // The enemy's takeDamage method handles reducing its health.
    enemy.takeDamage(attackPower);
}

void Player::takeDamage(int damage) {
    // Reduce health by the damage amount
    health -= damage;
    
    // Ensure health doesn't go negative (cap at 0)
    if (health < 0) health = 0;
}
