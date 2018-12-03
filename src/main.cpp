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
    Move move1("a2a4");
    std::cout << ((int)move1.src) << ',' << ((int)move1.dest) << std::endl;
}