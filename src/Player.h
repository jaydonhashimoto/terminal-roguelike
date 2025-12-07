#pragma once
#include "Map.h"

// Forward declaration to avoid circular includes.
// This tells the compiler that Enemy is a class, but
// we don't need the full definition here in the header.
class Enemy;

// Represents the player in the game world
class Player {
public:
    // Position coordinates on the map grid
    int x = 1; // starting x coordinate
    int y = 1; // starting y coordinate
    
    // Combat statistics
    int health = 20;      // Current health points (player dies at 0)
    int attackPower = 3;  // How much damage player deals per attack

    // Attempts to move the player by (dx, dy).
    // Only moves if the target tile is walkable (not a wall).
    void move(int dx, int dy, const Map& map);
    
    // Deals damage to an enemy.
    // Called when player walks into an enemy's position.
    void attack(Enemy& enemy);
    
    // Reduces player health by the given damage amount.
    // Called when an enemy attacks the player.
    // Health will not go below 0.
    void takeDamage(int damage);
    
    // Returns true if player still has health remaining.
    // Used to check game over condition.
    bool isAlive() const { return health > 0; }
};
