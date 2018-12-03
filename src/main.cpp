#include <iostream>
#include "Board.h"

using BB = std::bitset<64>; ///BB = Bit board. BB[0] = a8, BB[1] = b8, BB[8] = a7

std::string bb_to_string(BB in){
    std::string out;
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++) {
            out+=in[i*8+j]?"X":".";
        }
        out+="\n";
    }
    return out;
}

int main() {
    Board board;
    board.set_state_new();
    Move move1(11,27);
    Move move2(49,33);
    Move move3(10,26);
    Move move4(33,25);
    Move move5(8,24);
    Board board2 = board.make_move(move1).make_move(move2).make_move(move3).make_move(move4).make_move(move5);
    //std::cout << board2.to_string() << std::endl;
    std::cout << bb_to_string(board2.passantTarget()) << std::endl;
    Move move6(25,16);
    std::cout << board2.make_move(move6).to_string() << std::endl;
}