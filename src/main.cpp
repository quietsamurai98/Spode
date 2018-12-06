#include <iostream>
#include <chrono>
#include "Board.h"
#include "Utils.h"
#include "Perft.h"
#include "Searcher.h"


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
    std::list<perft_divide_pair> out;
    if(depth < 2){
        throw std::out_of_range("perft_divide only works for n>=2");
    }
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

int main() {
    Board board;
    board.set_state_new();
    Perft tester(board);
    Searcher searcher(board);
    auto start = std::chrono::steady_clock::now();
    for (int i = 1; i <= 100; ++i) {
        //std::cout << i << '\t' << tester.perft(i) << std::endl;
        auto end = std::chrono::steady_clock::now();
        std::cout << i << '\t' << searcher.get_best_move(i, true).to_string() << '\t' << "Elapsed time in nanoseconds : " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << " ns" << std::endl;
    }
}