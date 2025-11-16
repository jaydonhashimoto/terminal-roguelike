cmake_minimum_required(VERSION 3.20)

# Name of the project
project(Roguelike LANGUAGES CXX VERSION 0.1.0)

# Use modern C++ features
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Build an executable from these source files
add_executable(roguelike
    src/main.cpp
    src/Game.cpp
    src/Map.cpp
    src/Player.cpp
    src/Enemy.cpp
)

# So #include "Game.h" works
target_include_directories(roguelike PRIVATE src)
