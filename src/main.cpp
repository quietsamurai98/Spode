#include <iostream>
#include <chrono>
#include "Board.h"
#include "Util.h"
#include "Perft.h"
#include "Searcher.h"
#include "AssertionFailure.h"

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

Board apply_moves(Board in, std::list<Move> moves){
    Board out(in);
    for(auto m:moves){
        out = out.make_move(m);
    }
    return out;
}

uintmax_t perft(Board board, int depth){
    std::list<std::list<Move>> parents;
    std::list<std::list<Move>> children;
    uintmax_t out = 0;

    for(auto m:board.get_moves()){
        std::list<Move> tmp;
        tmp.push_back(m);
        parents.push_back(tmp);
        out++;
    }

    for(int i = 1; i < depth; i++){
        out=0;

        while(!parents.empty()){
            std::list<Move> mv(parents.back());
            auto b = apply_moves(board,mv);
            parents.pop_back();
            auto ms = b.get_moves();
            out+=ms.size();
            for(auto m : ms){
                std::list<Move> tmp(mv);
                tmp.push_back(m);
                children.push_back(tmp);
            }
        }
        parents.clear();
        parents = children;
        children.clear();
    }

    return out;
}

struct perft_divide_pair {
    Move parent;
    uintmax_t children;
};

std::list<perft_divide_pair> perft_divide(Board board, int depth){
    ASSERT(depth < 2, "Invalid argument: perft_divide requires a depth of two or more.");

    std::list<perft_divide_pair> out;

    for(auto m : board.get_moves()){
        perft_divide_pair p;
        p.parent = m;
        p.children = perft(board.make_move(m),depth-1);
        out.push_back(p);
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
    int i = 0;
    for(auto p : pd){
        std::cout << (++i) << '\t' << p.parent.to_string() << '\t' << p.children << std::endl;
        sum+=p.children;
    }
    std::cout << "Total: " << sum << std::endl;
}

void p_test(const Board &board, int depth){
    std::cout << "Depth " << depth << '\t' << perft(board, depth) << std::endl;
}

void sanity(){
    for(auto i = 0; i < 8; i++){
        std::cout << bb_to_string(Board::lookup_rank(i)) << std::endl;
    }
    for(auto i = 0; i < 8; i++){
        std::cout << bb_to_string(Board::lookup_file(i)) << std::endl;
    }
}

void byte_swap(){
    Board board("1krnbn2/1q4b1/1p4r1/1p3p2/1BPPP3/1N3R2/1Q4B1/1K4R1 w - -");
    std::cout << board.to_string() << std::endl << std::endl;
    for(auto i = 0; i < 8; i++){
        board.pieceBB[i] = __builtin_bswap64(board.pieceBB[i].to_ullong());
    }
    std::cout << board.to_string() << std::endl;
}

void ab_test(int trials){
    auto start = std::chrono::steady_clock::now();
    for (int i = 1; i <= trials; ++i) {
        Board board;
        board.set_state_new();
        Searcher searcher(board);
        searcher.get_best_move(5, false);
        std::cout << ((i*100)/trials) << '%' << std::endl;
    }
    auto end = std::chrono::steady_clock::now();
    std::cout << "Average time per search was " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()/trials << " milliseconds." << std::endl;
}

int main() {
    ab_test(10);
}