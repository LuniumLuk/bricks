cmake_minimum_required(VERSION 3.20)

project(Bricks)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Bricks
    platform/win32.cpp
    src/game.cpp
    src/gui.cpp
    src/image.cpp
    src/main.cpp
)