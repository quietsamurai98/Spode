
#include <stdexcept>
#include <iostream>
#include "Board.h"

using BB = std::bitset<64>; ///BB = Bit board. BB[0] = a8, BB[1] = b8, BB[8] = a7
using CR = uint8_t; ///CR = Castle rights. CR&0b00001000 = white long castle, CR&0b00000001 = black short castle
using EP = uint8_t; ///EP = En passant target file. 0 = a, 7 = h
using SM = uint8_t; ///SM = Side to move. 0 = white, 1 = black.


Board::Board() {

}

Board::~Board() {

}

BB Board::wPawns() {
    return pieceBB[pawnBB] & pieceBB[whiteBB];
}

BB Board::wKnights() {
    return pieceBB[knightBB] & pieceBB[whiteBB];
}

BB Board::wBishops() {
    return pieceBB[bishopBB] & pieceBB[whiteBB];
}

BB Board::wRooks() {
    return pieceBB[rookBB] & pieceBB[whiteBB];
}

BB Board::wQueens() {
    return pieceBB[queenBB] & pieceBB[whiteBB];
}

BB Board::wKings() {
    return pieceBB[kingBB] & pieceBB[whiteBB];
}

BB Board::bPawns() {
    return pieceBB[pawnBB] & pieceBB[blackBB];
}

BB Board::bKnights() {
    return pieceBB[knightBB] & pieceBB[blackBB];
}

BB Board::bBishops() {
    return pieceBB[bishopBB] & pieceBB[blackBB];
}

BB Board::bRooks() {
    return pieceBB[rookBB] & pieceBB[blackBB];
}

BB Board::bQueens() {
    return pieceBB[queenBB] & pieceBB[blackBB];
}

BB Board::bKings() {
    return pieceBB[kingBB] & pieceBB[blackBB];
}

BB Board::passantTarget() {
    BB out;
    uint64_t offset;
    if(state.side == 1){
        //Black to move
        offset = 0x10ULL+state.passant_file;
    } else {
        //white to move
        offset = 0x28ULL+state.passant_file;
    }
    out|=(state.passant_exist?1ull:0ull)<<offset;
    return out;
}

void Board::set_state_new() {
    state = {0b1111, 0b0, 0b0, 0b0};
    pieceBB[whiteBB] = 0x000000000000ffff;
    pieceBB[blackBB] = 0xffff000000000000;
    pieceBB[pawnBB]  = 0x00ff00000000ff00;
    pieceBB[rookBB]  = 0x8100000000000081;
    pieceBB[knightBB]= 0x4200000000000042;
    pieceBB[bishopBB]= 0x2400000000000024;
    pieceBB[queenBB] = 0x0800000000000010;
    pieceBB[kingBB]  = 0x1000000000000008;
}

Board Board::make_move(Move move) {
    Board out = *this;
    boardID srcBB; //The bit board containing the source piece
    if(out.pieceBB[pawnBB][move.src]){
        srcBB = pawnBB;
    } else if(out.pieceBB[knightBB][move.src]){
        srcBB = knightBB;
    } else if(out.pieceBB[bishopBB][move.src]){
        srcBB = bishopBB;
    } else if(out.pieceBB[rookBB][move.src]){
        srcBB = rookBB;
    } else if(out.pieceBB[queenBB][move.src]){
        srcBB = queenBB;
    } else if(out.pieceBB[kingBB][move.src]){
        srcBB = kingBB;
    } else {
        throw std::logic_error("Tried to move non-existent piece!");
    }

    bool castle = (srcBB == kingBB) && (move.src%8 == 4) && (move.dest == 2 || move.dest == 6 || move.dest == 56 || move.dest == 62);
    bool passant = (srcBB == pawnBB) && out.passantTarget()[move.dest];

    if(castle){
        if(move.src == 4){//black
            out.pieceBB[kingBB][4] = false;
            out.pieceBB[blackBB][4] = false;
            if(move.dest == 2){ //long
                out.state.castle_rights&=0b1101;

                out.pieceBB[kingBB][2] = true;
                out.pieceBB[rookBB][0] = false;
                out.pieceBB[rookBB][3] = true;
                out.pieceBB[blackBB][2] = true;
                out.pieceBB[blackBB][0] = false;
                out.pieceBB[blackBB][3] = true;
            } else { //short
                out.state.castle_rights&=0b1110;
                out.pieceBB[kingBB][6] = true;
                out.pieceBB[rookBB][7] = false;
                out.pieceBB[rookBB][5] = true;
                out.pieceBB[blackBB][6] = false;
                out.pieceBB[blackBB][7] = false;
                out.pieceBB[blackBB][5] = true;
            }
        } else {//white
            out.pieceBB[kingBB][60] = false;
            out.pieceBB[whiteBB][60] = false;
            if(move.dest == 58){ //long
                out.state.castle_rights&=0b0111;

                out.pieceBB[kingBB][58] = true;
                out.pieceBB[rookBB][56] = false;
                out.pieceBB[rookBB][59] = true;
                out.pieceBB[whiteBB][58] = true;
                out.pieceBB[whiteBB][56] = false;
                out.pieceBB[whiteBB][59] = true;
            } else { //short
                out.state.castle_rights&=0b1011;

                out.pieceBB[kingBB][62] = true;
                out.pieceBB[rookBB][63] = false;
                out.pieceBB[rookBB][61] = true;
                out.pieceBB[whiteBB][62] = false;
                out.pieceBB[whiteBB][53] = false;
                out.pieceBB[whiteBB][61] = true;
            }
        }
    } else {
        bool capture = false;
        boardID destBB = srcBB; //Assume there wasn't a capture

        boardID sideBB = (out.state.side == 0)?(whiteBB):(blackBB);
        boardID opntBB = (out.state.side == 1)?(whiteBB):(blackBB); //Opponent bit board

        if(out.pieceBB[whiteBB][move.dest] || out.pieceBB[blackBB][move.dest]){
            //A piece was captured. Find it's bit board
            capture = true;
            if(out.pieceBB[pawnBB][move.src]){
                destBB = pawnBB;
            } else if(out.pieceBB[knightBB][move.src]){
                destBB = knightBB;
            } else if(out.pieceBB[bishopBB][move.src]){
                destBB = bishopBB;
            } else if(out.pieceBB[rookBB][move.src]){
                destBB = rookBB;
            } else if(out.pieceBB[queenBB][move.src]){
                destBB = queenBB;
            } else if(out.pieceBB[kingBB][move.src]){
                destBB = kingBB;
            }
        } else if(srcBB==pawnBB && ((move.src/8 == 1 && move.dest/8 == 3) || (move.src/8 == 6 && move.dest/8 == 4))) {
            out.state.passant_exist = 1;
            out.state.passant_file = move.src%((PF)8u);
        } else {
            out.state.passant_exist = 0;
        }
        //Move the piece
        out.pieceBB[sideBB][move.src] = false;
        out.pieceBB[sideBB][move.dest] = true;
        out.pieceBB[srcBB][move.src] = false;
        out.pieceBB[destBB][move.dest] = true;

        if(capture){
            out.pieceBB[opntBB][move.dest] = false;
            if(destBB == rookBB){
                //Update castle rights in case a rook was captured
                if(move.dest == 0){
                    out.state.castle_rights&= 0b1101;
                } else if(move.dest == 7){
                    out.state.castle_rights&= 0b1110;
                } else if(move.dest == 56){
                    out.state.castle_rights&= 0b0111;
                } else if(move.dest == 63){
                    out.state.castle_rights&= 0b1011;
                }
            }
        } else if(passant) {
            uint8_t cap = move.dest;
            if(out.state.side){
                cap+=8;
            } else {
                cap-=8;
            }
            out.pieceBB[opntBB][cap] = false;
            out.pieceBB[pawnBB][cap] = false;
        }
    }
    out.state.side++;
    return out;
}

std::string Board::to_string() {
    std::string out;
    for(int i = 0; i < 64; i++){
        std::string reps = pieceBB[whiteBB][i]?"PNBRQK":"pnbrqk";
        if(pieceBB[pawnBB][i]){
            out+=reps[0];
        } else if(pieceBB[knightBB][i]){
            out+=reps[1];
        } else if(pieceBB[bishopBB][i]){
            out+=reps[2];
        } else if(pieceBB[rookBB][i]){
            out+=reps[3];
        } else if(pieceBB[queenBB][i]){
            out+=reps[4];
        } else if(pieceBB[kingBB][i]){
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
