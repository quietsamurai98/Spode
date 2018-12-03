
#ifndef SPODE_BOARD_H
#define SPODE_BOARD_H

#include <bitset>
#include "Move.h"

class Board {
public: //Type aliases and definitions
    using BB = std::bitset<64>; ///BB = Bit board. BB[0] = a8, BB[1] = b8, BB[8] = a7
    using CR = uint8_t; ///CR = Castle rights. CR&0b00001000 = white long castle, CR&0b00000001 = black short castle
    using EP = uint8_t; ///EP = En passant target exists. 1 = exists, 0 = not exists
    using PF = uint8_t; ///PF = En passant target file. 0 = a, 7 = h
    using SM = uint8_t; ///SM = Side to move. 0 = white, 1 = black.
    struct State{
        CR castle_rights : 4;
        PF passant_file  : 3;
        EP passant_exist : 1;
        SM side          : 1;
    };
    enum boardID{
        whiteBB = 0,
        blackBB = 1,
        pawnBB  = 2,
        knightBB= 3,
        bishopBB= 4,
        rookBB  = 5,
        queenBB = 6,
        kingBB  = 7
    };

public: //Member variables
    BB pieceBB[8];
    State state;

public: //Constructors, destructors
    Board();
    ~Board();

public: //State initializers
    void set_state_new(); //New game

public: //Operations
    Board make_move(Move move);
    std::string to_string();
    /**
     * Determines if the opponent side (the side opposing the current side to move) has a given square in check
     * @param square The number of the square to test, with 0 being a8, 7 being h8, and 63 being h1
     * @return Whether the square is in check or not.
     */
    bool in_check(uint8_t square);

public: //Bit board generators
    BB wPawns();
    BB wKnights();
    BB wBishops();
    BB wRooks();
    BB wQueens();
    BB wKings();
    BB bPawns();
    BB bKnights();
    BB bBishops();
    BB bRooks();
    BB bQueens();
    BB bKings();
    BB passantTarget();
    BB move_dests(uint8_t src);
    BB dest_pawn(uint8_t src, boardID side);
    BB dest_knight(uint8_t src, boardID side);
    BB dest_bishop(uint8_t src, boardID side);
    BB dest_rook(uint8_t src, boardID side);
    BB dest_queen(uint8_t src, boardID side);
    BB dest_king(uint8_t src, boardID side);
};

#endif //SPODE_BOARD_H
