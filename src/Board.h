//
// Created by Kenneth on 11/28/2018.
//

#ifndef SPODE_BOARD_H
#define SPODE_BOARD_H

#include <cstddef>
#include <bitset>
#include <vector>
#include "Common.h"
#include "Piece.h"
#include "PieceGrid.h"
#include "Move.h"

class Board {
public:
    Board();

    Color getSide_to_move() const;

    const std::bitset<4> &getCastle_rights() const;

    const std::vector<Piece> &getPieces() const;

    const PieceGrid &getGrid() const;

    std::vector<Move> generate_legal_moves();

    Board apply_move(Move move);

    std::string stringify();

    void setup_new_game_board();

private:


    Color side_to_move;

    /**
     * castle_rights[0] = White queen side castle rights
     * castle_rights[1] = White king side castle rights
     * castle_rights[2] = Black queen side castle rights
     * castle_rights[3] = Black king side castle rights
     */
    std::bitset<4> castle_rights;

    std::vector<Piece> pieces;

    PieceGrid grid;

    /**
     * Checks if the square with the given ID is under attack. Used for seeing if the king is in check.
     * @param square The square ID to test
     * @return If the square is being attacked
     */
    bool in_check();

    std::vector<Move> generate_piece_moves(Piece piece);

    void delete_piece_from_list(int id, std::vector<Piece> &vect);
    bool square_occupied(int id);
    int row_col_to_id(int row, int col);
};


#endif //SPODE_BOARD_H
