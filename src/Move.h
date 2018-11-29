//
// Created by Kenneth on 11/28/2018.
//

#ifndef SPODE_MOVE_H
#define SPODE_MOVE_H


#include <cstdint>
#include <string>
#include "Piece.h"

class Move {
public:
    /**
     * Creates a move from the source square to the destination square.
     * @param source The source square ID.
     * @param dest The destination square ID.
     */
    Move(int source, int dest);

    /**
     * Creates a move from the source square to the destination square, where the moving piece is promoted.
     * @param source The source square ID.
     * @param dest The destination square ID.
     * @param promotion The type of piece being promoted to.
     */
    Move(int source, int dest, Piece::Type promotion);


    Move(int source, int dest, bool en_passant, bool double_step);

    /**
     * Gets the UCI-compatible algebraic notation representation of the move
     * @return
     */
    std::string algebraic_notation();
public:
    int getSource() const;

    int getDest() const;

    Piece::Type getPromotion() const;

private:
    int source, dest; ///The source and destination square IDs
    /**
     * If the move involves promoting a pawn, this is the type of piece the pawn was promoted to.
     * Otherwise, it is Piece::Type::NIL.
     */
    Piece::Type promotion;
public:
    void setPromotion(Piece::Type promotion);

private:

    /**
     * Whether or not the move involved a capture by en passant
     */
    bool en_passant;

    bool double_step;
public:
    bool isDouble_step() const;

public:
    bool isEn_passant() const;
};


#endif //SPODE_MOVE_H
