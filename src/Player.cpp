#include "Player.h"

void Player::move(int dx, int dy, const Map& map) {
    // Proposed new position
    int newX = x + dx;
    int newY = y + dy;

    // Only move if the tile is walkable
    if (map.isWalkable(newX, newY)) {
        x = newX;
        y = newY;
    }
}
