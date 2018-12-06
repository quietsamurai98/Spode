cmake_minimum_required(VERSION 3.10)
project(Spode)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g -Og")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

add_executable(Spode src/main.cpp src/Board.cpp src/Board.h src/Board.cpp src/Board.h src/Move.cpp src/Move.h src/Utils.h src/Perft.h src/Perft.cpp)