
#ifndef SPODE_SEARCHER_H
#define SPODE_SEARCHER_H


#include <cstdint>
#include <vector>
#include "Move.h"
#include "Board.h"

class Searcher {
public:
    using score_t = int16_t ;
    static const score_t PLUS_INFINITY = INT16_MAX/2;
    static const score_t MINUS_INFINITY = INT16_MIN/2;

    struct Node{
        /**
         * DESIGN DECISION NOTE: By only holding a Move (2 bytes) instead of a Board and a Move (74 bytes) in each node,
         * the tree can store 37 times as many possible game states in memory.
         * However, extra CPU time is used every time the Board represented by a Node is needed, as the root to node
         * path must be traversed and a new Board must be generated each time.
         */

        static uintmax_t count;
        std::vector<Node> children; //24
        Node *parent;               // 8
        Move move = Move();         // 2
        score_t score = 0;          // 2
        bool populated = false;     // 1
        bool evaluated = false;     // 1

        Node(){
            count++;
            parent = nullptr;
            move = Move();
            children = std::vector<Node>(0);
        }
        Node(Node *p, const Move &m){
            count++;
            parent = p;
            move = Move(m);
            children = std::vector<Node>(0);
        }
        ~Node(){
            count--;
            children.clear();
            children.shrink_to_fit();
        }
    };

    Board initial_board;
    Node *root;

    explicit Searcher(const Board &board) : initial_board(board) {
        root = new Node(nullptr, Move());
    };
    ~Searcher(){
        delete root;
    }

    /**
     * Generates the Board represented by the node. The board is calculated using the Searcher's initial_board, and the
     * moves contained by every node on the path from the root node to the given node.
     * @param n The node to get the Board for
     * @return The Board represented by the node
     */
    Board get_board(Node *n);

    /**
     * Populates the child node pointers if not already populated
     * @param n The node to populate the children of, if needed
     */
    void populate_node(Node *n);

    /**
     * Evaluates the score of a node. The more positive the score, the better for white, and the more negative the
     * score, the better for black. +INFINITY indicates a checkmate where white wins, and -INFINITY indicates a
     * checkmate where black wins. This value is only calculated once per node.
     * @param n The node to evaluate
     * @return The score of the node
     */
    score_t evaluate_node(Node *n);

    /**
     * The actual heuristic used to evaluate non-terminal game states
     * @param board The board to evaluate.
     * @return The heuristic score.
     */
    score_t heuristic_eval(Board board);

    /**
     * Gets the best move based on all the possible game states after <depth> moves.
     * @param depth The depth of the search tree.
     * @param quiescence_mode If enabled, all captures will be explored regardless of depth.
     * @return The optimal move.
     */
    Move get_best_move(int depth, bool quiescence_mode = false);

    /**
     * A wrapper for the recursive negamax
     * @param n
     * @param depth
     * @param quiescence_mode If enabled, all captures will be explored regardless of depth.
     * @return
     */
    Move negamax_alpha_beta(int depth, bool quiescence_mode);

    /**
     * Negamax search with alpha beta pruning.
     * @param n     The node to start the search at
     * @param depth The remaining search depth
     * @param alpha The minimum score that is guaranteed to be attainable by the maxing side
     * @param beta  The maximum score that is guaranteed to be attainable by the minimizing side
     * @param quiescence_mode If enabled, all captures will be explored regardless of depth.
     * @return The new bound
     */
    score_t negamax_alpha_beta(Node *n, int depth, score_t alpha, score_t beta, bool quiescence_mode);

    score_t quiesce(Node *n, score_t alpha, score_t beta);
};


#endif //SPODE_SEARCHER_H
