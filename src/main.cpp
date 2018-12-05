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

std::vector<Move> perft(Board board, int depth){
    std::vector<Board> parents;
    std::vector<Board> children;
    std::vector<Move> out;
    parents.push_back(Board(board));

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

Board apply_moves(Board in, std::vector<Move> moves){
    Board out(in);
    for (uint64_t i = 0; i < moves.size(); ++i) {
        out = out.make_move(moves[i]);
    }
    return out;
}

struct perft_divide_pair {
    Move parent;
    std::vector<Board> children;
};

std::vector<perft_divide_pair> perft_divide(Board board, int depth){
    std::vector<perft_divide_pair> out;
    for(auto m : board.get_moves()){
        perft_divide_pair p;
        p.parent = m;
        for(auto mm : board.make_move(m).get_moves()){
            p.children.push_back(board.make_move(m).make_move(mm));
        }
        out.push_back(p);
    }
    if(depth < 2){
        throw std::out_of_range("perft_divide only works for n>=2");
    }
    for (int i = 2; i < depth; ++i) {
        for(uint64_t j = 0; j < out.size(); ++j){
            std::vector<Board> parents(out[j].children);
            out[j].children.clear();
            for(auto b:parents){
                for(auto m:b.get_moves()){
                    out[j].children.push_back(b.make_move(m));
                }
            }
        }
    }

    return out;
}

BB str_to_bb(std::string str){
    BB out;
    for (unsigned long int i = 0; i < str.length(); ++i) {
        out[i] = str[i]=='1';
    }
    return out;
}

void pd_test(Board board, int depth){
    auto pd = perft_divide(board, depth);
    size_t sum = 0;
    for(unsigned long i = 0; i < pd.size(); ++i){
        auto p = pd[i];
        std::cout << (i+1) << '\t' << p.parent.to_string() << '\t' << p.children.size() << std::endl;
        sum+=p.children.size();
    }
    std::cout << "Total: " << sum << std::endl;
}

int main() {
    Board board("r3k2r/8/8/p6p/P6P/8/8/R3K2R w KQkq -");
    pd_test(board,3);
    //std::cout << bb_to_string(board.quiet_king(4,Board::blackBB)) << std::endl;
    //std::cout << board.wbEmpty()[5] << (bool)board.wbEmpty()[6] << (bool)!board.square_under_attack(4, Board::blackBB) << (bool)!board.square_under_attack(5, Board::blackBB) << (bool)!board.square_under_attack(6, Board::blackBB) << std::endl;
}