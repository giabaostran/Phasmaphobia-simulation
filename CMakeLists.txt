cmake_minimum_required(VERSION 4.0)
project(final_project C)

set(CMAKE_C_STANDARD 11)

add_executable(final_project helpers.c main.c hunter.c ghost.c room.c log.c)

