
#include <stdexcept>
#include <iostream>
#include <cmath>
#include <sstream>
#include "Board.h"

using CR = uint8_t; ///CR = Castle rights. CR&0b00001000 = white long castle, CR&0b00000001 = black short castle
using EP = uint8_t; ///EP = En passant target file. 0 = a, 7 = h
using SM = uint8_t; ///SM = Side to move. 0 = white, 1 = black.

uintmax_t Board::count = 0;

Board::Board() = default;

Board::Board(const Board &other) {
    state = other.state;
    for (int i = 0; i < 8; ++i) {
        pieceBB[i] = other.pieceBB[i];
    }
}

Board::Board(std::string const fen){
    unsigned long i = 0, j = 0;
    for (; i < fen.length() && fen[i]!=' '; ++i) {
        switch(fen[i]){
            case 'p':
                pieceBB[blackBB].set(j);
                pieceBB[pawnBB].set(j);
                ++j;
                break;
            case 'P':
                pieceBB[whiteBB].set(j);
                pieceBB[pawnBB].set(j);
                ++j;
                break;
            case 'n':
                pieceBB[blackBB].set(j);
                pieceBB[knightBB].set(j);
                ++j;
                break;
            case 'N':
                pieceBB[whiteBB].set(j);
                pieceBB[knightBB].set(j);
                ++j;
                break;
            case 'b':
                pieceBB[blackBB].set(j);
                pieceBB[bishopBB].set(j);
                ++j;
                break;
            case 'B':
                pieceBB[whiteBB].set(j);
                pieceBB[bishopBB].set(j);
                ++j;
                break;
            case 'r':
                pieceBB[blackBB].set(j);
                pieceBB[rookBB].set(j);
                ++j;
                break;
            case 'R':
                pieceBB[whiteBB].set(j);
                pieceBB[rookBB].set(j);
                ++j;
                break;
            case 'q':
                pieceBB[blackBB].set(j);
                pieceBB[queenBB].set(j);
                ++j;
                break;
            case 'Q':
                pieceBB[whiteBB].set(j);
                pieceBB[queenBB].set(j);
                ++j;
                break;
            case 'k':
                pieceBB[blackBB].set(j);
                pieceBB[kingBB].set(j);
                ++j;
                break;
            case 'K':
                pieceBB[whiteBB].set(j);
                pieceBB[kingBB].set(j);
                ++j;
                break;
            case '1':
                j+=1;
                break;
            case '2':
                j+=2;
                break;
            case '3':
                j+=3;
                break;
            case '4':
                j+=4;
                break;
            case '5':
                j+=5;
                break;
            case '6':
                j+=6;
                break;
            case '7':
                j+=7;
                break;
            case '8':
                j+=8;
                break;
            case '/':
                break;
            default:
                ASSERT_FAIL("FEN board contains an invalid character!");
        }
    }
    state.side = (fen[++i]=='w'?(SM)0:(SM)1);
    i+=2;
    state.castle_rights = 0b0000;
    while(fen[i]!=' '){
        switch(fen[i]){
            case 'Q':
                state.castle_rights |= 0b1000;
                break;
            case 'K':
                state.castle_rights |= 0b0100;
                break;
            case 'q':
                state.castle_rights |= 0b0010;
                break;
            case 'k':
                state.castle_rights |= 0b0001;
                break;
            case '-':
                break;
            default:
                ASSERT_FAIL("FEN castle rights contains invalid character!");
        }
        i++;
    }
    i++;
    if(fen[i]!='-'){
        state.passant_exist = 1;
        state.passant_file = (uint8_t)(fen[i]-'a');
        i++;
    } else {
        state.passant_exist = 0;
    }
    i++;
    ///TODO Move counters
}

Board::~Board() = default;

Bitboard Board::wPawns() /*const*/ {
    return pieceBB[pawnBB] & pieceBB[whiteBB];
}

Bitboard Board::wKnights() /*const*/ {
    return pieceBB[knightBB] & pieceBB[whiteBB];
}

Bitboard Board::wBishops() /*const*/ {
    return pieceBB[bishopBB] & pieceBB[whiteBB];
}

Bitboard Board::wRooks() /*const*/ {
    return pieceBB[rookBB] & pieceBB[whiteBB];
}

Bitboard Board::wQueens() /*const*/ {
    return pieceBB[queenBB] & pieceBB[whiteBB];
}

Bitboard Board::wKings() /*const*/ {
    return pieceBB[kingBB] & pieceBB[whiteBB];
}

Bitboard Board::bPawns() /*const*/ {
    return pieceBB[pawnBB] & pieceBB[blackBB];
}

Bitboard Board::bKnights() /*const*/ {
    return pieceBB[knightBB] & pieceBB[blackBB];
}

Bitboard Board::bBishops() /*const*/ {
    return pieceBB[bishopBB] & pieceBB[blackBB];
}

Bitboard Board::bRooks() /*const*/ {
    return pieceBB[rookBB] & pieceBB[blackBB];
}

Bitboard Board::bQueens() /*const*/ {
    return pieceBB[queenBB] & pieceBB[blackBB];
}

Bitboard Board::bKings() /*const*/ {
    return pieceBB[kingBB] & pieceBB[blackBB];
}

Bitboard Board::wbEmpty() /*const*/ {
    return ~pieceBB[whiteBB] & ~pieceBB[blackBB];
}

Bitboard Board::wbEnemy(boardID side) /*const*/ {
    if(side == whiteBB){
        return pieceBB[blackBB];
    } else {
        return pieceBB[whiteBB];
    }
}

Bitboard Board::passantTarget() /*const*/ {
    Bitboard out;
    if(state.passant_exist) {
        if (state.side == 1) {
            //Black to move
            out.set(40 + state.passant_file);
        } else {
            //white to move
            out.set(16 + state.passant_file);
        }
    }
    return out;
}

void Board::set_state_new() {
    state = {0b1111, 0b0, 0b0, 0b0};
    pieceBB[whiteBB] = 0xffff000000000000;
    pieceBB[blackBB] = 0x000000000000ffff;
    pieceBB[pawnBB]  = 0x00ff00000000ff00;
    pieceBB[rookBB]  = 0x8100000000000081;
    pieceBB[knightBB]= 0x4200000000000042;
    pieceBB[bishopBB]= 0x2400000000000024;
    pieceBB[queenBB] = 0x0800000000000008;
    pieceBB[kingBB]  = 0x1000000000000010;
}

Board Board::make_move(Move move) const{
    Board out(*this);
    if(move.null_move == 0) {
        boardID srcBB; //The bit board containing the source piece
        if (out.pieceBB[pawnBB].test(move.src)) {
            srcBB = pawnBB;
        } else if (out.pieceBB[knightBB].test(move.src)) {
            srcBB = knightBB;
        } else if (out.pieceBB[bishopBB].test(move.src)) {
            srcBB = bishopBB;
        } else if (out.pieceBB[rookBB].test(move.src)) {
            srcBB = rookBB;
        } else if (out.pieceBB[queenBB].test(move.src)) {
            srcBB = queenBB;
        } else if (out.pieceBB[kingBB].test(move.src)) {
            srcBB = kingBB;
        } else {
            std::stringstream msg;
            msg << "TRIED TO MOVE NON EXISTENT PIECE!\n";
            msg << "Initial state:\n" << to_string() << "\n";
            msg << "Move: " << move.to_string();
            ASSERT_FAIL(msg.str().c_str());
        }

        bool castle = (srcBB == kingBB) && (move.src % 8 == 4) && (move.dest % 8 == 2 || move.dest % 8 == 6);
        bool passant = (srcBB == pawnBB) && (move.dest % 8 != move.src % 8) && out.wbEmpty().test(move.dest);
        bool capture = false;

        if (castle) {
            if (move.src == 4) {//black
                out.state.castle_rights &= 0b1100;
                if (move.dest == 2) { //long
                    out.pieceBB[kingBB].set(4, false);
                    out.pieceBB[blackBB].set(4, false);
                    out.pieceBB[kingBB].set(2, true);
                    out.pieceBB[blackBB].set(2, true);

                    out.pieceBB[rookBB].set(0, false);
                    out.pieceBB[blackBB].set(0, false);
                    out.pieceBB[rookBB].set(3, true);
                    out.pieceBB[blackBB].set(3, true);
                } else { //short
                    out.pieceBB[kingBB].set(4, false);
                    out.pieceBB[blackBB].set(4, false);
                    out.pieceBB[kingBB].set(6, true);
                    out.pieceBB[blackBB].set(6, true);

                    out.pieceBB[rookBB].set(7, false);
                    out.pieceBB[blackBB].set(7, false);
                    out.pieceBB[rookBB].set(5, true);
                    out.pieceBB[blackBB].set(5, true);
                }
            } else {//white
                out.state.castle_rights &= 0b0011;
                if (move.dest == 58) { //long
                    out.pieceBB[kingBB].set(60, false);
                    out.pieceBB[whiteBB].set(60, false);
                    out.pieceBB[kingBB].set(58, true);
                    out.pieceBB[whiteBB].set(58, true);

                    out.pieceBB[rookBB].set(56, false);
                    out.pieceBB[whiteBB].set(56, false);
                    out.pieceBB[rookBB].set(59, true);
                    out.pieceBB[whiteBB].set(59, true);
                } else { //short
                    out.pieceBB[kingBB].set(60, false);
                    out.pieceBB[whiteBB].set(60, false);
                    out.pieceBB[kingBB].set(62, true);
                    out.pieceBB[whiteBB].set(62, true);

                    out.pieceBB[rookBB].set(63, false);
                    out.pieceBB[whiteBB].set(63, false);
                    out.pieceBB[rookBB].set(61, true);
                    out.pieceBB[whiteBB].set(61, true);
                }
            }
        } else {
            boardID capBB = srcBB; //Assume there wasn't a capture

            boardID sideBB = (out.state.side == 0) ? (whiteBB) : (blackBB);
            boardID opntBB = (out.state.side == 1) ? (whiteBB) : (blackBB); //Opponent bit board

            if (out.pieceBB[opntBB].test(move.dest)) {
                //A piece was captured. Find it's bit board
                capture = true;
                if (out.pieceBB[pawnBB].test(move.dest)) {
                    capBB = pawnBB;
                } else if (out.pieceBB[knightBB].test(move.dest)) {
                    capBB = knightBB;
                } else if (out.pieceBB[bishopBB].test(move.dest)) {
                    capBB = bishopBB;
                } else if (out.pieceBB[rookBB].test(move.dest)) {
                    capBB = rookBB;
                } else if (out.pieceBB[queenBB].test(move.dest)) {
                    capBB = queenBB;
                } else if (out.pieceBB[kingBB].test(move.dest)) {
                    capBB = kingBB;
                }
            }
            if (srcBB == pawnBB && std::abs(move.src / 8 - move.dest / 8) == 2){
                out.state.passant_exist = 1;
                out.state.passant_file = (PF)(move.src % 8);
            } else {
                out.state.passant_exist = 0;
            }
            //Move the piece
            //Pick up the piece
            out.pieceBB[sideBB].reset(move.src);
            out.pieceBB[srcBB].reset(move.src);

            //Clear the destination square
            out.pieceBB[capBB].reset(move.dest);
            out.pieceBB[opntBB].reset(move.dest);

            //Put down the piece
            out.pieceBB[sideBB].set(move.dest);
            out.pieceBB[srcBB].set(move.dest);

            if (srcBB == rookBB) {
                //Update castle rights in case a rook was moved
                if (move.src == 0) {
                    out.state.castle_rights &= 0b1101;
                } else if (move.src == 7) {
                    out.state.castle_rights &= 0b1110;
                } else if (move.src == 56) {
                    out.state.castle_rights &= 0b0111;
                } else if (move.src == 63) {
                    out.state.castle_rights &= 0b1011;
                }
            }

            if (srcBB == kingBB) {
                //Update castle rights in case a king was moved
                if (move.src == 4) {
                    out.state.castle_rights &= 0b1101;
                    out.state.castle_rights &= 0b1110;
                } else if (move.src == 60) {
                    out.state.castle_rights &= 0b0111;
                    out.state.castle_rights &= 0b1011;
                }
            }

            if (capture) {
                if (capBB == rookBB) {
                    //Update castle rights in case a rook was captured
                    if (move.dest == 0) {
                        out.state.castle_rights &= 0b1101;
                    } else if (move.dest == 7) {
                        out.state.castle_rights &= 0b1110;
                    } else if (move.dest == 56) {
                        out.state.castle_rights &= 0b0111;
                    } else if (move.dest == 63) {
                        out.state.castle_rights &= 0b1011;
                    }
                }
            } else if (passant) {
                int cap = move.dest%8 + 8*(move.src/8);
                out.pieceBB[opntBB].reset(cap);
                out.pieceBB[pawnBB].reset(cap);
            }

        }

        if(!out.sanity_check()){
            std::stringstream msg;
            msg << "SANITY CHECK FAILED: ";
            msg << "capture=" << (capture?"true":"false") << ", ";
            msg << "castle=" << (castle?"true":"false") << ", ";
            msg << "passant=" << (passant?"true":"false") << "\n";
            msg << "Initial state:\n" << to_string() << "\n";
            msg << "Move: " << move.to_string();
            ASSERT_FAIL(msg.str().c_str());
        }
    }
    out.state.side++;

    return out;
}

std::string Board::to_string() const{
    std::string out;
    for(int i = 0; i < 64; i++){
        std::string reps = pieceBB[whiteBB].test(i)?"PNBRQK":"pnbrqk";
        if(pieceBB[pawnBB].test(i)){
            out+=reps[0];
        } else if(pieceBB[knightBB].test(i)){
            out+=reps[1];
        } else if(pieceBB[bishopBB].test(i)){
            out+=reps[2];
        } else if(pieceBB[rookBB].test(i)){
            out+=reps[3];
        } else if(pieceBB[queenBB].test(i)){
            out+=reps[4];
        } else if(pieceBB[kingBB].test(i)){
            out+=reps[5];
        } else {
            out+=".";
        }
        if(i%8==7 && i!=63){
            out+="\n";
        }
    }
    return out;
}

std::list<Move> Board::get_moves(bool tactical_only) /*const*/ {
    boardID side = (state.side == 0)?(whiteBB):(blackBB);
    Bitboard sideBB = pieceBB[side];
    Bitboard enemBB = wbEnemy(side);
    std::list<Move> moves;
    if((pieceBB[kingBB]&pieceBB[whiteBB]).count()!=1 || (pieceBB[kingBB]&pieceBB[blackBB]).count()!=1) {
        std::stringstream msg;
        msg << "BOARD IS MISSING ONE OR MORE KINGS!\n";
        msg << "Board layout:\n" << to_string() << "\n";
        ASSERT_FAIL(msg.str().c_str());
    }

    for (uint8_t i = 0; i < 64; i++) {
        if (sideBB.test(i)) {
            Bitboard moveBB = find_dests(i, side);
            for (uint8_t j = 0; j < 64; j++) {
                if (moveBB.test(j)) {
                    if ((j / 8) % 7 == 0 && pieceBB[pawnBB].test(i)) {
                        moves.emplace_back(i, j, 0);
                        moves.emplace_back(i, j, 1);
                        moves.emplace_back(i, j, 2);
                        moves.emplace_back(i, j, 3);
                    } else if(!tactical_only || enemBB.test(j)) {
                        moves.emplace_back(i, j);
                    }
                }
            }
        }
    }

    std::list<Move> out;
    for(Move m : moves){
        Board b = make_move(m);
        b.state.side = state.side;
        Bitboard king = (b.pieceBB[(state.side == 0)?(whiteBB):(blackBB)]&b.pieceBB[kingBB]);
        auto king_pos = king.positions();
        ASSERT(king_pos.size()==1, "Current side does not have exactly one king!");
        if(!b.square_under_attack(king_pos.front(), side)){
            out.push_back(m);
        }
    }
    return out;
}


bool Board::in_checkmate() /*const*/ {
    //If there are no legal moves, and the king is in check, that's a checkmate.
    Bitboard king = (pieceBB[(state.side == 0)?(whiteBB):(blackBB)]&pieceBB[kingBB]);
    auto king_pos = king.positions();
    ASSERT(king_pos.size()==1, "Current side does not have exactly one king!");
    return square_under_attack(king_pos.front(), (state.side == 0)?(whiteBB):(blackBB)) && get_moves().empty();
}
bool Board::in_stalemate() /*const*/ {
    //If there are no legal moves, and the king is not in check, that's a stalemate.
    Bitboard king = (pieceBB[(state.side == 0)?(whiteBB):(blackBB)]&pieceBB[kingBB]);
    auto king_pos = king.positions();
    ASSERT(king_pos.size()==1, "Current side does not have exactly one king!");
    return !square_under_attack(king_pos.front(), (state.side == 0)?(whiteBB):(blackBB)) && get_moves().empty();
}

Bitboard Board::quiet_pawn(uint8_t src, boardID side) /*const*/ {
    auto move_offset = (int8_t)((side == whiteBB) ? -8 : 8);
    auto home_rank = (uint8_t)((side==whiteBB)?6:1);
    Bitboard valid = wbEmpty();
    Bitboard out;
    out.set(src+move_offset, valid.test(src+move_offset));
    if(src/8==home_rank){
        out.set(src+2*move_offset, valid.test(src+move_offset) && valid.test(src+2*move_offset));
    }
    return out;
}
Bitboard Board::quiet_knight(uint8_t src, boardID) /*const*/ {
    Bitboard valid = wbEmpty();
    Bitboard out;
    // .A.B.
    // C...D
    // ..K..
    // E...F
    // .G.H.
    if(src > 15 && src%8 < 7){//nne
        out.set(src-16+1);
    }
    if(src > 15 && src%8 > 0){//nnw
        out.set(src-16-1);
    }
    if(src < 48 && src%8 < 7){//sse
        out.set(src+16+1);
    }
    if(src < 48 && src%8 > 0){//ssw
        out.set(src+16-1);
    }
    if(src > 7  && src%8 < 6){//nee
        out.set(src-8+2);
    }
    if(src < 56 && src%8 < 6){//see
        out.set(src+8+2);
    }
    if(src > 7  && src%8 > 1){//nww
        out.set(src-8-2);
    }
    if(src < 56 && src%8 > 1){//sww
        out.set(src+8-2);
    }
    out &= valid;
    return out;
}
Bitboard Board::quiet_bishop(uint8_t src, boardID) /*const*/ {
    Bitboard out;
    Bitboard valid = wbEmpty();
    int src_r = src/8;
    int src_c = src%8;

    for(int r = src_r+1, c = src_c+1; r < 8 && c < 8 && valid.test(r*8+c); r++, c++){
        out.set(r*8+c);
    }
    for(int r = src_r+1, c = src_c-1; r < 8 && c > -1 && valid.test(r*8+c); r++, c--){
        out.set(r*8+c);
    }
    for(int r = src_r-1, c = src_c+1; r > -1 && c < 8 && valid.test(r*8+c); r--, c++){
        out.set(r*8+c);
    }
    for(int r = src_r-1, c = src_c-1; r > -1 && c > -1 && valid.test(r*8+c); r--, c--){
        out.set(r*8+c);
    }

    return out;
}
Bitboard Board::quiet_rook(uint8_t src, boardID) /*const*/ {
    Bitboard out;
    Bitboard valid = wbEmpty();
    int src_r = src/8;
    int src_c = src%8;

    for(int r = src_r+1, c = src_c; r < 8 && valid.test(r*8+c); r++){
        out.set(r*8+c);
    }
    for(int r = src_r-1, c = src_c; r > -1 && valid.test(r*8+c); r--){
        out.set(r*8+c);
    }
    for(int r = src_r, c = src_c+1; c < 8 && valid.test(r*8+c); c++){
        out.set(r*8+c);
    }
    for(int r = src_r, c = src_c-1; c > -1 && valid.test(r*8+c); c--){
        out.set(r*8+c);
    }

    return out;
}
Bitboard Board::quiet_queen(uint8_t src, boardID side) /*const*/ {
    return quiet_bishop(src, side) | quiet_rook(src, side);
}

Bitboard Board::quiet_king(uint8_t src, boardID side) /*const*/ {
    bool north = src > 7;
    bool south = src < 56;
    bool east = src%8 < 7;
    bool west = src%8 > 0;
    Bitboard valid = wbEmpty();
    Bitboard out;
    if(north){
        out.set(src-8);
    }
    if(south){
        out.set(src+8);
    }
    if(east){
        out.set(src+1);
    }
    if(west){
        out.set(src-1);
    }
    if(north&&east){
        out.set(src-8+1);
    }
    if(south&&east){
        out.set(src+8+1);
    }
    if(north&&west){
        out.set(src-8-1);
    }
    if(south&&west){
        out.set(src+8-1);
    }
    out &= valid;
    out |= castle_king(src, side);
    return out;
}

Bitboard Board::castle_king(uint8_t src, boardID side) /*const*/ {
    Bitboard out;
    Bitboard empty = wbEmpty();
    if(side == whiteBB && src == 60){
        if(state.castle_rights & 0b1000u){
            //Long white castle
            out.set(58, empty.test(57) & empty.test(58) & empty.test(59) & !square_under_attack(58, side) & !square_under_attack(59, side) & !square_under_attack(60, side));;
        }
        if(state.castle_rights & 0b0100u){
            //Short white castle
            out.set(62, empty.test(61) & empty.test(62) & !square_under_attack(60, side) & !square_under_attack(61, side) & !square_under_attack(62, side));;
        }
    } else if(side == blackBB && src == 4){
        if(state.castle_rights & 0b0010u){
            //Long black castle
            out.set(2, empty.test(1) & empty.test(2) & empty.test(3) & !square_under_attack(2, side) & !square_under_attack(3, side) & !square_under_attack(4, side));;
        }
        if(state.castle_rights & 0b0001u){
            //Short black castle
            out.set(6, empty.test(5) & empty.test(6) & !square_under_attack(4, side) & !square_under_attack(5, side) & !square_under_attack(6, side));;
        }
    }
    return out;
}
Bitboard Board::tactical_pawn(int64_t src, boardID side) /*const*/ {
    auto move_offset = (int8_t)((side == whiteBB) ? -8 : 8);
    Bitboard out;
    Bitboard valid = wbEnemy(side);
    if((side == whiteBB && state.side == 0) || (side == blackBB && state.side == 1)){
        valid |= passantTarget();
    }
    if(src%8!=0){ //left
        out.set(src+move_offset-1, valid.test(src+move_offset-1));
    }
    if(src%8!=7){ //right
        out.set(src+move_offset+1, valid.test(src+move_offset+1));
    }
    return out;
}
Bitboard Board::tactical_knight(int64_t src, boardID side) /*const*/ {
    Bitboard valid = wbEnemy(side);
    Bitboard out;
    // .A.B.
    // C...D
    // ..K..
    // E...F
    // .G.H.
    if(src > 15 && src%8 < 7){//nne
        out.set(src-16+1);
    }
    if(src > 15 && src%8 > 0){//nnw
        out.set(src-16-1);
    }
    if(src < 48 && src%8 < 7){//sse
        out.set(src+16+1);
    }
    if(src < 48 && src%8 > 0){//ssw
        out.set(src+16-1);
    }
    if(src > 7  && src%8 < 6){//nee
        out.set(src-8+2);
    }
    if(src < 56 && src%8 < 6){//see
        out.set(src+8+2);
    }
    if(src > 7  && src%8 > 1){//nww
        out.set(src-8-2);
    }
    if(src < 56 && src%8 > 1){//sww
        out.set(src+8-2);
    }
    out &= valid;
    return out;
}
Bitboard Board::tactical_bishop(int64_t src, boardID side) /*const*/ {
    Bitboard out;
    Bitboard valid = wbEnemy(side);
    Bitboard empty = wbEmpty();
    int src_r = src/8;
    int src_c = src%8;
    {
        int r = src_r+1, c = src_c+1;
        for (; r < 8 && c < 8 && empty.test(r * 8 + c); r++, c++) {}
        if(r < 8 && c < 8){
            out.set(r*8+c, valid.test(r*8+c));
        }
    }
    {
        int r = src_r+1, c = src_c-1;
        for (; r < 8 && c > -1 && empty.test(r * 8 + c); r++, c--) {}
        if(r < 8 && c > -1){
            out.set(r*8+c, valid.test(r*8+c));
        }
    }
    {
        int r = src_r-1, c = src_c+1;
        for (; r > -1 && c < 8 && empty.test(r * 8 + c); r--, c++) {}
        if(r > -1 && c < 8){
            out.set(r*8+c, valid.test(r*8+c));
        }
    }
    {
        int r = src_r-1, c = src_c-1;
        for (; r > -1 && c > -1 && empty.test(r * 8 + c); r--, c--) {}
        if(r > -1 && c > -1){
            out.set(r*8+c, valid.test(r*8+c));
        }
    }

    return out;
}
Bitboard Board::tactical_rook(int64_t src, boardID side) /*const*/ {
    Bitboard out;
    Bitboard valid = wbEnemy(side);
    Bitboard empty = wbEmpty();
    int src_r = src/8;
    int src_c = src%8;
    {
        int r = src_r+1, c = src_c;
        for (; r < 8 && empty.test(r * 8 + c); r++) {}
        if(r < 8){
            out.set(r*8+c, valid.test(r*8+c));
        }
    }
    {
        int r = src_r-1, c = src_c;
        for (; r > -1 && empty.test(r * 8 + c); r--) {}
        if(r > -1){
            out.set(r*8+c, valid.test(r*8+c));
        }
    }
    {
        int r = src_r, c = src_c+1;
        for (; c < 8 && empty.test(r * 8 + c); c++) {}
        if(c < 8){
            out.set(r*8+c, valid.test(r*8+c));
        }
    }
    {
        int r = src_r, c = src_c-1;
        for (; c > -1 && empty.test(r * 8 + c); c--) {}
        if(c > -1){
            out.set(r*8+c, valid.test(r*8+c));
        }
    }

    return out;
}
Bitboard Board::tactical_queen(uint8_t src, boardID side) /*const*/ {
    return tactical_rook(src, side) | tactical_bishop(src, side);
}

Bitboard Board::tactical_king(int64_t src, boardID side) /*const*/ {
    bool north = src > 7;
    bool south = src < 56;
    bool east = src%8 < 7;
    bool west = src%8 > 0;
    Bitboard valid = wbEnemy(side);
    Bitboard out;
    if(north){
        out.set(src-8);
    }
    if(south){
        out.set(src+8);
    }
    if(east){
        out.set(src+1);
    }
    if(west){
        out.set(src-1);
    }
    if(north&&east){
        out.set(src-8+1);
    }
    if(south&&east){
        out.set(src+8+1);
    }
    if(north&&west){
        out.set(src-8-1);
    }
    if(south&&west){
        out.set(src+8-1);
    }
    out &= valid;
    return out;
}

bool Board::square_under_attack(int64_t square, boardID side) /*const*/ {
    Bitboard attacks;
    attacks|=tactical_pawn(square, side)&pieceBB[pawnBB];
    attacks|=tactical_bishop(square, side)&(pieceBB[bishopBB] | pieceBB[queenBB]);
    attacks|=tactical_rook(square, side)&(pieceBB[rookBB] | pieceBB[queenBB]);
    //Queen taken care of by B and R
    attacks|=tactical_knight(square, side)&pieceBB[knightBB];
    attacks|=tactical_king(square, side)&pieceBB[kingBB];
    return attacks.any();
}

Bitboard Board::find_dests(uint8_t src, boardID side) /*const*/ {
    if(pieceBB[side].test(src)){ ///src square occupied by specified side
        if(pieceBB[pawnBB].test(src)){
            return tactical_pawn(src, side) | quiet_pawn(src, side);
        } else if(pieceBB[knightBB].test(src)){
            return tactical_knight(src, side) | quiet_knight(src, side);
        } else if(pieceBB[rookBB].test(src)){
            return tactical_rook(src, side) | quiet_rook(src, side);
        } else if(pieceBB[bishopBB].test(src)){
            return tactical_bishop(src, side) | quiet_bishop(src, side);
        } else if(pieceBB[queenBB].test(src)){
            return tactical_queen(src, side) | quiet_queen(src, side);
        } else if(pieceBB[kingBB].test(src)){
            return tactical_king(src, side) | quiet_king(src, side);
        } else {
            ASSERT_FAIL("Empty square is owned by side!");
        }
    } else {
        return Bitboard();
    }
}

bool Board::sanity_check() const {
    return true;
    boardID pieceIDs[6] = {pawnBB, knightBB, rookBB, bishopBB, queenBB, kingBB};

    Bitboard multiple_occupants;
    for(auto a : pieceIDs){
        for(auto b : pieceIDs){
            if(a!=b){
                multiple_occupants |= pieceBB[a] & pieceBB[b];
            }
        }
    }
    if(multiple_occupants.any()){
        std::cout << "SANITY CHECK FAILURE: MULTIPLE PIECES ON SQUARE" << std::endl;
        return false;
    }

    Bitboard all_pieces;
    for(auto a : pieceIDs){
        all_pieces |= pieceBB[a];
    }
    if((all_pieces ^ (pieceBB[whiteBB] | pieceBB[blackBB])).any()){
        std::cout << "SANITY CHECK FAILURE: COLORLESS PIECE / PIECELESS COLOR" << std::endl;
        return false;
    }
    return true;
}


