#include "Enemy.h"

Enemy::Enemy(int startX, int startY)
    : x(startX), y(startY) {}

// Move one step closer to the player
void Enemy::update(int playerX, int playerY, const Map& map) {
    int dx = 0;
    int dy = 0;

    // Horizontal direction
    if (playerX > x) dx = 1;
    else if (playerX < x) dx = -1;

    // Vertical direction
    if (playerY > y) dy = 1;
    else if (playerY < y) dy = -1;

    int newX = x + dx;
    int newY = y + dy;

    // Only move if the tile is walkable
    if (map.isWalkable(newX, newY)) {
        x = newX;
        y = newY;
    }
}
