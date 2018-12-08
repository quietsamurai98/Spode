
#include "Perft.h"
#include "AssertionFailure.h"

uintmax_t Perft::Node::count = 0;

void Perft::populate_node(Perft::Node *n) {
    ASSERT(n != nullptr, "A null node cannot be populated!");

    ASSERT(n -> children.empty(),"Node is already populated!");

    std::stack<Move> moves;
    Node *cur = n;
    while(cur != root){
        moves.push(*cur->move);
        cur = cur->parent;
    }

    Board board(initial_board);
    while(!moves.empty()){
        board = board.make_move(moves.top());
        moves.pop();
    }

    for(const auto &m:board.get_moves()){
        n -> children.push_back(new Node(n, new Move(m)));
    }
}

uintmax_t Perft::perft(uint depth) {
    return perft(root, 1, depth);
}

uintmax_t Perft::perft(Node *node, uint depth, uint target) {
    ASSERT(depth <= target, "DEPTH EXCEEDED TARGET!");
    if(node -> children.empty()){
        populate_node(node);
    }
    if(depth == target){
        return node -> children.size();
    } else { //depth < target
        uintmax_t sum = 0;
        for(auto c : node -> children){
            sum += perft(c, depth+1, target);
        }
        return sum;
    }
}
