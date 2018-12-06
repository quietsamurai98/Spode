#include <stack>
#include "Searcher.h"

uintmax_t Searcher::Node::count = 0;

Searcher::score_t Searcher::evaluate_node(Searcher::Node *n) {
    /**
     * Scores range from MINUS_INFINITY (Black mates white) to PLUS_INFINITY (White mates black). A score of 0
     *  represents a draw.
     */

    if(n == nullptr){
        throw std::invalid_argument("Cannot evaluate the null node!");
    }

    if(n -> evaluated){
        //Node has already been evaluated. Return the cached score value.
        return n->score;
    }

    Board board = get_board(n);
    score_t score = 0;

    if(board.in_checkmate()){
        //If the white player is in checkmate, MINUS_INFINITY. If the black player is in checkmate, PLUS_INFINITY
        score = (board.state.side == 0)?MINUS_INFINITY:PLUS_INFINITY;
    } else if (board.in_stalemate()){
        //Stalemate = draw.
        score = 0;
    } else {
        //Game state must be evaluated based on a heuristic.
        score = heuristic_eval(board);
    }
    n -> score = score;
    n -> evaluated = true;
    return score;
}

Searcher::score_t Searcher::heuristic_eval(Board board){
    /**
     * This method is the soul of Spode. It evaluates how "good" a non-terminal game state is.
     * More negative scores indicate better game states for black, while more positive scores indicate better
     * game states for white.
     */

    /**
     * VERSION 1.0: (White centipawn score) - (Black centipawn score)
     */
     score_t score = 0;

     score += board.wPawns().count()   * 100;
     score += board.wKnights().count() * 350;
     score += board.wBishops().count() * 350;
     score += board.wRooks().count()   * 525;
     score += board.wQueens().count()  * 1000;

     score -= board.bPawns().count()   * 100;
     score -= board.bKnights().count() * 350;
     score -= board.bBishops().count() * 350;
     score -= board.bRooks().count()   * 525;
     score -= board.bQueens().count()  * 1000;

     return score;
}

Board Searcher::get_board(Searcher::Node *n){
    if(n == nullptr){
        throw std::invalid_argument("Cannot get the null node's board!");
    }

    std::stack<Move> moves;
    Node *cur = n;
    while(cur != root){
        moves.push(Move(cur->move));
        cur = cur->parent;
    }

    Board board(initial_board);
    while(!moves.empty()){
        board = board.make_move(moves.top());
        moves.pop();
    }
    return board;
}

void Searcher::populate_node(Searcher::Node *n) {
    if(n == nullptr){
        throw std::invalid_argument("Cannot populate null node!");
    }
    if(n->populated){
        return;
    }

    n -> children.clear();
    for(const auto &m:get_board(n).get_moves()){
        n -> children.emplace_back(n, Move(m));
    }
    n -> children.shrink_to_fit();

    n -> populated = true;
}

Move Searcher::get_best_move(int depth, bool quiescence_mode) {
    return negamax_alpha_beta(depth, quiescence_mode);
}

Move Searcher::negamax_alpha_beta(int depth, bool quiescence_mode) {
    Node *n = root;
    score_t alpha = MINUS_INFINITY;
    score_t beta  = PLUS_INFINITY;
    Board board = get_board(n);
    if(depth == 0 || board.in_checkmate() || board.in_stalemate()){
        throw std::logic_error("No moves can be made!");
    }
    populate_node(n);
    score_t max_score = MINUS_INFINITY;
    Move    max_move;
    for(Node m : n->children){
        score_t tmp = -negamax_alpha_beta(&m, depth-1, -beta, -alpha, quiescence_mode);
        if(tmp > max_score){
            max_score = tmp;
            max_move = Move(m.move);
        }
        alpha = (alpha>max_score)?alpha:max_score;
        if(alpha>=beta){
            break; //Cutoff
        }
    }
    return max_move;
}

Searcher::score_t Searcher::negamax_alpha_beta(Searcher::Node *n, int depth, Searcher::score_t alpha, Searcher::score_t beta, bool quiescence_mode) {
    Board board = get_board(n);
    int8_t color_factor = (board.state.side==0)?(int8_t)1:(int8_t)-1;
    auto tactical_moves = board.get_moves(true);
    if(depth == 0 || board.in_checkmate() || board.in_stalemate()){
        if(quiescence_mode && !tactical_moves.empty()){
            return  quiesce(n, alpha, beta);
        } else {
            return evaluate_node(n) * color_factor;
        }
    }
    populate_node(n);

    score_t max_score = MINUS_INFINITY;
    for(Node m : n->children){
        score_t tmp = -negamax_alpha_beta(&m, depth-1, -beta, -alpha, quiescence_mode);
        if(tmp > max_score){
            max_score = tmp;
        }
        alpha = (alpha>max_score)?alpha:max_score;
        if(alpha>=beta){
            break; //Cutoff
        }
    }
    return max_score;
}

Searcher::score_t Searcher::quiesce(Searcher::Node *n, Searcher::score_t alpha, Searcher::score_t beta) {
    score_t stand_pat = evaluate_node(n);
    if(stand_pat >= beta){
        return beta;
    }
    if(alpha < stand_pat){
        alpha = stand_pat;
    }

    n -> children.clear();
    n -> populated = false;
    for(const auto &m:get_board(n).get_moves(true)){
        n -> children.emplace_back(n, Move(m));
    }
    n -> children.shrink_to_fit();

    for(auto c:n->children){
        score_t score = -quiesce(&c, -beta, -alpha);
        if(score >= beta){
            return score;
        }
        if(score > alpha){
            alpha = score;
        }
    }

    return alpha;
}
