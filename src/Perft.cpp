
#include "Perft.h"

uintmax_t Perft::Node::count = 0;

void Perft::populate_node(Perft::Node *n) {
    if(n == nullptr){
        throw std::invalid_argument("Cannot populate null node!");
    }
    if(!(n -> children.empty())){
        throw std::invalid_argument("Node is already populated!");
    }

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
    if(node -> children.empty()){
        populate_node(node);
    }
    if(depth == target){
        return node -> children.size();
    } else if(depth < target) {
        uintmax_t sum = 0;
        for(auto c : node -> children){
            sum += perft(c, depth+1, target);
        }
        return sum;
    } else {
        throw std::logic_error("DEPTH EXCEEDS TARGET!");
    }
}
