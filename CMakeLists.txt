cmake_minimum_required(VERSION 3.10)
project(Spode)

set(CMAKE_CXX_STANDARD 17)

add_executable(Spode src/main.cpp src/Board.cpp src/Board.h src/Piece.cpp src/Piece.h src/Common.h src/PieceGrid.cpp src/PieceGrid.h src/Move.cpp src/Move.h)