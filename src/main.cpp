#include <iostream>
#include <chrono>
#include "Board.h"
#include "Util.h"
#include "Perft.h"
#include "Searcher.h"
#include "AssertionFailure.h"
#include "Bitboard.h"



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
        std::cout << Board::lookup_rank(i).to_string() << std::endl;
    }
    for(auto i = 0; i < 8; i++){
        std::cout << Board::lookup_file(i).to_string() << std::endl;
    }
}

void ab_test(int trials, int depth, bool q_search){
    auto start = std::chrono::steady_clock::now();
    for (int i = 1; i <= trials; ++i) {
        Board board = Board::new_game();
        Searcher searcher(board);
        std::cout << searcher.get_best_move(depth, q_search).to_string() << '\t' << ((i*100)/trials) << '%' << std::endl;
    }
    auto end = std::chrono::steady_clock::now();
    std::cout << "Average time per search was " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()/trials << " milliseconds." << std::endl;
}

void bitboard_test(){
    Bitboard bb(0b01000010'01000010'00100010'00011110'00100010'01000010'01000010'00111110);
    std::cout << bb << std::endl << std::endl;
    bb.sym_rot_ccw();
    std::cout << bb << std::endl << std::endl;
    bb.sym_rot_ccw();
    std::cout << bb << std::endl << std::endl;
    bb.sym_rot_ccw();
    std::cout << bb << std::endl << std::endl;
    bb.sym_rot_ccw();
    std::cout << bb << std::endl << std::endl;
}

void holy_war(){
    std::vector<Move> history;
    Board board = Board::new_game();
    while(!board.in_stalemate() && !board.in_checkmate()){
        Searcher steve(board);
        Move mv = steve.get_best_move(4,false);
        history.push_back(mv);
        board = board.make_move(mv);
        std::cout << "\n\n\n\n\n\n\n\n\n\n";
        std::cout << board.to_string() << std::endl;
        for (size_t i = 0; i < history.size(); ++i) {
            std::cout << std::to_string((i/2)+1) << ((i%2)?'b':'w') << ": " << history[i].to_string() << std::endl;
        }
    }
}

void mate_in_one(){
    Board white_to_win("3k4/8/3p4/7B/3Q4/2R1R3/8/5K2 w - -"); //d4d6 wins
    Searcher wh(white_to_win);
    std::cout << wh.get_best_move(4, false).to_string() << std::endl;
    std::cout << wh.heuristic_eval(white_to_win.make_move(Move("d4d6"))) << std::endl;

    Board black_to_win("1r4kb/5q2/8/8/7p/1R1p1p1P/K2P1P2/4BRN1 b - -");
    Searcher bl(black_to_win);
    std::cout << (black_to_win.make_move(Move("f7b3")).in_checkmate()?"mate":"fuck") << bl.get_best_move(4, false).to_string() << std::endl;
}

int main() {
    mate_in_one();
}