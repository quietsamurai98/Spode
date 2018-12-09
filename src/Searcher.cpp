#include <stack>
#include "Searcher.h"
#include "AssertionFailure.h"
#include "Util.h"

uintmax_t Searcher::Node::count = 0;

Searcher::score_t Searcher::evaluate_node(Searcher::Node * const n) {
    /**
     * Scores range from MINUS_INFINITY (Black mates white) to PLUS_INFINITY (White mates black). A score of 0
     *  represents a draw.
     */
    ASSERT(n != nullptr, "A null node cannot be evaluated!");

    if(n -> evaluated){
        //Node has already been evaluated. Return the cached score value.
        return n->score;
    }

    Board board = get_board(n);
    score_t score = 0;

    score = heuristic_eval(board);

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

    if(board.in_checkmate()){
        return board.state.side==0 ? MINUS_INFINITY : PLUS_INFINITY;
    }

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

Board Searcher::get_board(Searcher::Node * const n){
    ASSERT(n != nullptr, "Cannot get board belonging to the null node!");

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

void Searcher::populate_node(Searcher::Node * const n) {
    ASSERT(n != nullptr, "A null node cannot be populated!");

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

Move Searcher::get_best_move(int const depth, bool const quiescence_mode) {
    ASSERT(depth > 0, "How am I supposed to search for a move if I can't look at my options‽");
    ASSERT(!initial_board.in_checkmate(), "You already won, no need to rub it in...");
    ASSERT(!initial_board.in_stalemate(), "The only winning move is not to play... How about a nice game of-- oh.");
    return negamax_alpha_beta(depth, quiescence_mode);
}

Move Searcher::negamax_alpha_beta(int const depth, bool const quiescence_mode) {
    Node *n = root;
    score_t alpha = MINUS_INFINITY;
    score_t beta  = PLUS_INFINITY;
    populate_node(n);
    Move best_move;
    score_t best_score = MINUS_INFINITY*2;

    for(Node c : n->children) {
        auto c_score = -negamax_alpha_beta(n, depth, alpha, beta, quiescence_mode);
        if(c_score > best_score){
            best_score = c_score;
            best_move = c.move;
        }
    }

    return best_move;
}

Searcher::score_t Searcher::negamax_alpha_beta(Searcher::Node * const n, int const depth, Searcher::score_t alpha, Searcher::score_t beta, bool const quiescence_mode) {
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
    score_t max_score = MINUS_INFINITY*2;
    for(Node m : n->children){
        score_t tmp = -negamax_alpha_beta(&m, depth-1, -beta, -alpha, quiescence_mode);
        if(tmp > max_score){
            max_score = tmp;
        }
        if (max_score > alpha) {
            alpha = max_score;
        }
        if(max_score >= beta){
            break; //Cutoff
        }
    }
    return max_score;
}

Searcher::score_t Searcher::quiesce(Searcher::Node * const n, Searcher::score_t alpha, Searcher::score_t beta) {
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
