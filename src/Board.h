
#ifndef SPODE_BOARD_H
#define SPODE_BOARD_H

#include <bitset>
#include <list>
#include "AssertionFailure.h"
#include "Move.h"
#include "Util.h"

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

public: //BB lookup
    /**
     * Gets a BB where each square is set iff it is in the specified rank/row.
     * NOTE: rank must be on interval [0..7]. 0 -> top row, 7 -> bottom row.
     */
    static BB lookup_rank(int8_t rank){
        ASSERT(Util::on_range(rank, 0, 7), "RANK MUST BE ON INTERVAL [0..7]");
        return BB(0xffULL << (rank << 3));
    }

    static BB lookup_file(int8_t file){
        ASSERT(Util::on_range(file, 0, 7), "FILE MUST BE ON INTERVAL [0..7]");
        return BB(0x0101010101010101ULL << file);
    }

public: //Member variables
    BB pieceBB[8];
    State state;

public: //Constructors, destructors, instance counter
    static uintmax_t count;
    Board();
    explicit Board(std::string fen);
    Board(const Board &other);
    ~Board();

public: //State initializers
    void set_state_new(); //New game

public: //Operations
    Board make_move(Move move) const;
    std::string to_string() const;

    /**
     * Determines if the OTHER side could take the specified square
     * @param square
     * @param side
     * @return
     */
    bool square_under_attack(uint8_t square, boardID side) /*const*/;

    std::list<Move> get_moves(bool tactical_only = false);
    bool in_checkmate() /*const*/;
    bool in_stalemate() /*const*/;

    bool sanity_check() const;

public: //Bit board generators
    BB wPawns() /*const*/;
    BB wKnights() /*const*/;
    BB wBishops() /*const*/;
    BB wRooks() /*const*/;
    BB wQueens() /*const*/;
    BB wKings() /*const*/;
    BB bPawns() /*const*/;
    BB bKnights() /*const*/;
    BB bBishops() /*const*/;
    BB bRooks() /*const*/;
    BB bQueens() /*const*/;
    BB bKings() /*const*/;
    BB wbEmpty() /*const*/;
    BB wbEnemy(boardID side) /*const*/;
    BB passantTarget() /*const*/;

    BB quiet_pawn(uint8_t src, boardID side) /*const*/;
    BB quiet_knight(uint8_t src, boardID side) /*const*/;
    BB quiet_bishop(uint8_t src, boardID side) /*const*/;
    BB quiet_rook(uint8_t src, boardID side) /*const*/;
    BB quiet_queen(uint8_t src, boardID side) /*const*/;
    BB quiet_king(uint8_t src, boardID side) /*const*/;
    BB castle_king(uint8_t src, boardID side) /*const*/;

    BB tactical_pawn(uint8_t src, boardID side) /*const*/;
    BB tactical_knight(uint8_t src, boardID side) /*const*/;
    BB tactical_bishop(uint8_t src, boardID side) /*const*/;
    BB tactical_rook(uint8_t src, boardID side) /*const*/;
    BB tactical_queen(uint8_t src, boardID side) /*const*/;
    BB tactical_king(uint8_t src, boardID side) /*const*/;

    /**
     * Finds the pseudo legal move destinations for the piece belonging to the specified side at the specified source square.
     * If the piece at the source square does not belong to the specified side, it is treated like an empty square (no moves).
     * @param src
     * @param side
     * @return
     */
    BB find_dests(uint8_t src, boardID side) /*const*/;
};

#endif //SPODE_BOARD_H
