//
// Created by Kenneth on 11/28/2018.
//

#ifndef SPODE_PIECEGRID_H
#define SPODE_PIECEGRID_H


#include <vector>
#include "Piece.h"

class PieceGrid {
public:
    /**
     * Creates a PieceGrid from a vector of Pieces
     * @param pieces
     */
    explicit PieceGrid(std::vector<Piece> pieces);

    PieceGrid();

    Piece *get(int id) const;
    Piece *get(int row, int col) const;
    void set(int id, Piece *piece);
    void set(int row, int col, Piece *piece);
private:
    Piece ***squares;
};


#endif //SPODE_PIECEGRID_H
