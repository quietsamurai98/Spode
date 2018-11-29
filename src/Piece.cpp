//
// Created by Kenneth on 11/28/2018.
//

#include "Piece.h"

Piece::Type Piece::getType() const {
    return type;
}

int Piece::getSquare() const {
    return square;
}

Color Piece::getSide() const {
    return side;
}

bool Piece::getPassant() const {
    return passant;
}

Piece::Piece(Piece::Type type, Color side, int square) : type(type), side(side), square(square) {}

Piece::Piece() {

}

void Piece::setPassant(bool passant) {
    Piece::passant = passant;
}

std::string Piece::stringify() {
    std::string out;
    switch(side){
        case Color::WHITE:
            out+="WHITE";
            break;
        case Color::BLACK:
            out+="BLACK";
            break;
        case Color::NIL:
            out+="NIL";
    }
    switch(type){
        case Type::NIL:
            out+="NIL";
            break;
        case Type::PAWN:
            out+="PAWN";
            break;
        case Type::ROOK:
            out+="ROOK";
            break;
        case Type::BISHOP:
            out+="BISHOP";
            break;
        case Type::KNIGHT:
            out+="KNIGHT";
            break;
        case Type::KING:
            out+="KING";
            break;
        case Type::QUEEN:
            out+="QUEEN";
            break;
    }
    out+=std::to_string(square);
    return out;
}

