//
// Created by Kenneth on 11/28/2018.
//

#include <stdexcept>
#include "Move.h"

Move::Move(int source, int dest, Piece::Type promotion) :
    source(source),
    dest(dest),
    promotion(promotion),
    en_passant(false) {}

Move::Move(int source, int dest, bool en_passant, bool double_step) :
    source(source),
    dest(dest),
    promotion(Piece::Type::NIL),
    en_passant(en_passant),
    double_step(double_step) {
    if(source<0 || source>64){
        throw std::out_of_range("");
    }
    if(dest<0 || dest>64){
        throw std::out_of_range("");
    }
}

Move::Move(int source, int dest) :
    source(source),
    dest(dest),
    promotion(Piece::Type::NIL),
    en_passant(false) {}

int Move::getSource() const {
    return source;
}

int Move::getDest() const {
    return dest;
}

std::string Move::algebraic_notation() {
    std::string an_src, an_dest, an_move;
    an_src += "abcdefgh"[source%8];
    an_src += "87654321"[source/8];
    an_dest += "abcdefgh"[dest%8];
    an_dest += "87654321"[dest/8];
    an_move = an_src+an_dest;
    if(promotion==Piece::Type::NIL){
        return an_move;
    } else {
        std::string an_promo;
        switch(promotion){
            case Piece::Type::QUEEN:
                an_promo = "q";
                break;
            case Piece::Type::ROOK:
                an_promo = "r";
                break;
            case Piece::Type::BISHOP:
                an_promo = "b";
                break;
            case Piece::Type::KNIGHT:
                an_promo = "n";
                break;
            default:
                //This should never occur...
                an_promo = "";
        }
        return an_move+an_promo;
    }
}

Piece::Type Move::getPromotion() const {
    return promotion;
}

bool Move::isEn_passant() const {
    return en_passant;
}

bool Move::isDouble_step() const {
    return double_step;
}

void Move::setPromotion(Piece::Type promotion) {
    Move::promotion = promotion;
}
