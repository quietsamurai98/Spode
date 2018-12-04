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

std::vector<Move> perft(int depth){
    std::vector<Board> parents;
    std::vector<Board> children;
    std::vector<Move> out;
    parents.push_back(*new Board);
    parents[0].set_state_new();

    for(int i = 0; i < depth; i++){
        out.clear();
        for(Board b : parents){
            auto ms = b.get_moves();
            out.insert(out.end(), ms.begin(), ms.end());
            for(auto m : ms){
                children.push_back(b.make_move(m));
            }
        }
        parents.clear();
        parents = children;
        children.clear();
    }

    return out;
}

int main() {
    Board board;
    board.set_state_new();
    std::cout << board.to_string() << std::endl;
    std::cout << perft(3).size() << std::endl;
    auto moves = perft(3);
}