cmake_minimum_required(VERSION 3.20)
project(space_invaders C)

set(CMAKE_C_STANDARD 11)

add_executable(space_invaders
        src/main.c src/spaceship.c src/spaceship.h)
