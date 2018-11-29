#include <iostream>

#include "Board.h"

int main() {
    Board board;
    board.setup_new_game_board();
    std::vector<Move> opening_moves = board.generate_legal_moves();
    std::cout << opening_moves.size() << std::endl;
    for(Move mv : opening_moves){
        //std::cout << mv.algebraic_notation() << " (" << std::to_string(mv.getSource()) << " -> " << std::to_string(mv.getDest()) << ")" << std::endl;
    }
    std::vector<Move> reply_moves;
    while(opening_moves.size()>0){
        for(int i = 0; i<opening_moves.size(); i++){
            Move mv = opening_moves[i];
            //std::cout << i << std::endl;
            std::vector<Move> genMoves = board.apply_move(mv).generate_legal_moves();
            reply_moves.insert(reply_moves.end(), genMoves.begin(), genMoves.end());
        }
        std::cout << reply_moves.size() << std::endl;
        opening_moves = std::vector<Move>(reply_moves);
        reply_moves = std::vector<Move>();
    }
    return 0;
}