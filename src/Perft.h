
#ifndef SPODE_PERFT_H
#define SPODE_PERFT_H

#include <cstdint>
#include <vector>
#include <stack>
#include "Board.h"

class Perft{
public:
    struct Node{
        static uintmax_t count;
        Node *parent;
        Move *move;
        std::vector<Node*> children;
        Node(Node *p, Move *m){
            count++;
            parent = p;
            move = m;
            children = std::vector<Node *>();
        }
        ~Node(){
            count--;
            delete move;
            for(auto n : children)
                delete(n);
            children.clear();
        }
    };
public:
    explicit Perft(const Board &board) : initial_board(board) {
        root = new Node(nullptr, nullptr);
    };
    ~Perft(){
        delete root;
    }
public:
    Board initial_board;
    Node *root;
private:
    void populate_node(Node *n);
    uintmax_t perft(Node *node, uint depth, uint target);
public:
    uintmax_t perft(uint depth);
};

#endif //SPODE_PERFT_H