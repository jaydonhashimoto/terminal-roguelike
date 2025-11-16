cmake_minimum_required(VERSION 3.20)
project(Roguelike LANGUAGES CXX VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(roguelike
    src/main.cpp
    src/Game.cpp
    src/Map.cpp
    src/Player.cpp
)

target_include_directories(roguelike PRIVATE src)
