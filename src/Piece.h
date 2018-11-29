//
// Created by Kenneth on 11/28/2018.
//

#ifndef SPODE_PIECE_H
#define SPODE_PIECE_H


#include <cstdint>
#include <string>
#include "Common.h"

class Piece {
public:
    Piece();

    enum class Type {
        NIL,
        PAWN,
        KNIGHT,
        BISHOP,
        ROOK,
        QUEEN,
        KING
    };

    Piece(Type type, Color side, int square);

    Color getSide() const;

    /**
     * @return The type of the piece.
     */
    Type getType() const;

    /**
     * @return The ID of the square occupied by the piece. Note: 0 means a8, 7 means h8, 56 means a1, 63 means h1
     */
    int getSquare() const;

    bool getPassant() const;

private:
    Type type;
    Color side = Color::NIL;;     /// The color/side of the piece.
    int square; /// ID of the occupied square. 0 = upper left, 7 = upper right, 56 = lower left, 63 = lower right
    bool passant;
public:
    void setPassant(bool passant);
    /// If true, the piece is able to be captured via en passant.
    std::string stringify();
};


#endif //SPODE_PIECE_H
