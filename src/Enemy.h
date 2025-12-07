#pragma once
#include "Map.h"

// Forward declaration to avoid circular includes.
// This tells the compiler that Player is a class, but
// we don't need the full definition here in the header.
class Player;

// Represents a basic enemy in the world
class Enemy {
public:
    // Position coordinates on the map grid
    int x;
    int y;
    
    // Combat statistics
    int health = 10;      // Current health points (enemy dies at 0)
    int attackPower = 2;  // How much damage enemy deals per attack

    // Constructor: spawns enemy at given coordinates
    Enemy(int startX, int startY);

    // AI behavior: called each turn after player moves.
    // Enemy will try to move one step closer to player.
    // If already adjacent to player, will attack instead.
    void update(Player& player, const Map& map);
    
    // Deals damage to the player.
    // Called when enemy is adjacent to player.
    void attack(Player& player);
    
    // Reduces enemy health by the given damage amount.
    // Called when player attacks this enemy.
    // Health will not go below 0.
    void takeDamage(int damage);
    
    // Returns true if enemy still has health remaining.
    // Dead enemies will be removed from the game.
    bool isAlive() const { return health > 0; }
};
