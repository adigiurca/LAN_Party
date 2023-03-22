cmake_minimum_required(VERSION 3.24)
project(LAN_Party C)

set(CMAKE_C_STANDARD 11)

add_executable(LAN_Party
        main.c functions.h functions.c)
