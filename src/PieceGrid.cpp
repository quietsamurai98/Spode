//
// Created by Kenneth on 11/28/2018.
//

#include <stdexcept>
#include "PieceGrid.h"

PieceGrid::PieceGrid(std::vector<Piece> pieces) {
    squares = new Piece**[8]{};
    for(int i = 0; i < 8; i++){
        squares[i] = new Piece*[8];
        for(int j = 0; j < 8; j++){
            squares[i][j] = nullptr;
        }
    }
    for(Piece &p : pieces){
        squares[p.getSquare()/8][p.getSquare()%8] = &p;
    }
}

Piece* PieceGrid::get(int id) const {
    if(id > 63){
        throw std::out_of_range("Parameter id was out of bounds. Must be in range [0,63], actual value was "+ std::to_string(id)+".");
    }
    return squares[id/8][id%8];
}

Piece* PieceGrid::get(int row, int col) const {
    if(row > 7){
        throw std::out_of_range("Parameter row was out of bounds. Must be in range [0,7], actual value was "+ std::to_string(row)+".");
    }
    if(col > 7){
        throw std::out_of_range("Parameter col was out of bounds. Must be in range [0,7], actual value was "+ std::to_string(col)+".");
    }

    return squares[row][col];
}

void PieceGrid::set(int id, Piece *piece) {
    if(id > 63){
        throw std::out_of_range("Parameter id was out of bounds. Must be in range [0,63], actual value was "+ std::to_string(id)+".");
    }
    squares[id/8][id%8] = piece;
}

void PieceGrid::set(int row, int col, Piece *piece) {
    if(row > 7){
        throw std::out_of_range("Parameter row was out of bounds. Must be in range [0,7], actual value was "+ std::to_string(row)+".");
    }
    if(col > 7){
        throw std::out_of_range("Parameter col was out of bounds. Must be in range [0,7], actual value was "+ std::to_string(col)+".");
    }

    squares[row][col] = piece;
}

PieceGrid::PieceGrid() {
}
