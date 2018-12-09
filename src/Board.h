
#ifndef SPODE_BOARD_H
#define SPODE_BOARD_H

#include <bitset>
#include <list>
#include "AssertionFailure.h"
#include "Move.h"
#include "Util.h"
#include "Bitboard.h"

class Board {
public: //Type aliases and definitions
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

public: //Bitboard lookup
    ///TODO: Make these Bitboard member functions

    /**
     * Gets a Bitboard where each square is set iff it is in the specified rank/row.
     * NOTE: rank must be on interval [0..7]. 0 -> top row, 7 -> bottom row.
     */
    static Bitboard lookup_rank(int8_t rank){
        ASSERT(Util::on_range(rank, 0, 7), "RANK MUST BE ON INTERVAL [0..7]");
        return Bitboard(0xffULL << (rank << 3));
    }

    static Bitboard lookup_file(int8_t file){
        ASSERT(Util::on_range(file, 0, 7), "FILE MUST BE ON INTERVAL [0..7]");
        return Bitboard(0x0101010101010101ULL << file);
    }

public: //Member variables
    Bitboard pieceBB[8];
    State state;

public: //Constructors, destructors, instance counter
    static uintmax_t count;
    Board();
    explicit Board(std::string fen);
    Board(const Board &other);
    ~Board();

public: //Special boards
    static Board new_game();

public: //Operations
    Board make_move(Move move) const;
    std::string to_string() const;

    /**
     * Determines if the OTHER side could take the specified square
     * @param square
     * @param side
     * @return
     */
    bool square_under_attack(int64_t square, boardID side) /*const*/;

    std::list<Move> get_moves(bool tactical_only = false);
    bool in_checkmate() /*const*/;
    bool in_stalemate() /*const*/;

    bool sanity_check() const;

public: //Bit board generators
    Bitboard wPawns() /*const*/;
    Bitboard wKnights() /*const*/;
    Bitboard wBishops() /*const*/;
    Bitboard wRooks() /*const*/;
    Bitboard wQueens() /*const*/;
    Bitboard wKings() /*const*/;
    Bitboard bPawns() /*const*/;
    Bitboard bKnights() /*const*/;
    Bitboard bBishops() /*const*/;
    Bitboard bRooks() /*const*/;
    Bitboard bQueens() /*const*/;
    Bitboard bKings() /*const*/;
    Bitboard wbEmpty() /*const*/;
    Bitboard wbEnemy(boardID side) /*const*/;
    Bitboard passantTarget() /*const*/;

    Bitboard quiet_pawn(uint8_t src, boardID side) /*const*/;
    Bitboard quiet_knight(uint8_t src, boardID side) /*const*/;
    Bitboard quiet_bishop(uint8_t src, boardID side) /*const*/;
    Bitboard quiet_rook(uint8_t src, boardID side) /*const*/;
    Bitboard quiet_queen(uint8_t src, boardID side) /*const*/;
    Bitboard quiet_king(uint8_t src, boardID side) /*const*/;
    Bitboard castle_king(uint8_t src, boardID side) /*const*/;

    Bitboard tactical_pawn(int64_t src, boardID side) /*const*/;
    Bitboard tactical_knight(int64_t src, boardID side) /*const*/;
    Bitboard tactical_bishop(int64_t src, boardID side) /*const*/;
    Bitboard tactical_rook(int64_t src, boardID side) /*const*/;
    Bitboard tactical_queen(uint8_t src, boardID side) /*const*/;
    Bitboard tactical_king(int64_t src, boardID side) /*const*/;

    /**
     * Finds the pseudo legal move destinations for the piece belonging to the specified side at the specified source square.
     * If the piece at the source square does not belong to the specified side, it is treated like an empty square (no moves).
     * @param src
     * @param side
     * @return
     */
    Bitboard find_dests(uint8_t src, boardID side) /*const*/;
};

#endif //SPODE_BOARD_H
