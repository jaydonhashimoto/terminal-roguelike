# Terminal Roguelike

A simple terminal-based roguelike game written in C++ to learn fundamental programming concepts.

## Current Features

- **Grid-based map** with walls and walkable floors
- **Player movement** using WASD keys
- **Enemy AI** that chases the player
- **Turn-based combat system**
  - Player health: 20 HP
  - Enemy health: 10 HP
  - Attack by moving into enemies
  - Enemies attack when adjacent
- **Win/lose conditions**
  - Game over when player health reaches 0
  - Victory when all enemies are defeated
- **Real-time UI** showing health and enemy count

## Building and Running

Running on Windows:

```bash
mkdir build
cd build
cmake -G "MinGW Makefiles" ..
cmake --build .
./roguelike
```

## Controls

- `W` - Move up
- `A` - Move left
- `S` - Move down
- `D` - Move right
- `Q` - Quit game