//
// Created by Kenneth on 11/28/2018.
//

#include <iostream>
#include <algorithm>
#include "Board.h"

Board::Board() {
/**
    castle_rights.reset();
    pieces.push_back(*(new Piece(Piece::Type::KNIGHT,  Color::WHITE,8)));
**/
    grid = *(new PieceGrid(pieces));
}

void Board::setup_new_game_board(){
    side_to_move = Color::WHITE;

    castle_rights.reset();
    //Pawns
    for(int i = 0; i < 8; i++){
        Piece wp(Piece::Type::PAWN, Color::WHITE, (int)(48 + i));
        Piece bp(Piece::Type::PAWN, Color::BLACK, (int)(8 + i));
        pieces.push_back(wp);
        pieces.push_back(bp);
    }
    pieces.push_back(*(new Piece(Piece::Type::ROOK,  Color::WHITE,56)));
    pieces.push_back(*(new Piece(Piece::Type::ROOK,  Color::WHITE,63)));
    pieces.push_back(*(new Piece(Piece::Type::KNIGHT,Color::WHITE,57)));
    pieces.push_back(*(new Piece(Piece::Type::KNIGHT,Color::WHITE,62)));
    pieces.push_back(*(new Piece(Piece::Type::BISHOP,Color::WHITE,58)));
    pieces.push_back(*(new Piece(Piece::Type::BISHOP,Color::WHITE,61)));
    pieces.push_back(*(new Piece(Piece::Type::QUEEN, Color::WHITE,59)));
    pieces.push_back(*(new Piece(Piece::Type::KING,  Color::WHITE,60)));

    pieces.push_back(*(new Piece(Piece::Type::ROOK,  Color::BLACK,0)));
    pieces.push_back(*(new Piece(Piece::Type::ROOK,  Color::BLACK,7)));
    pieces.push_back(*(new Piece(Piece::Type::KNIGHT,Color::BLACK,1)));
    pieces.push_back(*(new Piece(Piece::Type::KNIGHT,Color::BLACK,6)));
    pieces.push_back(*(new Piece(Piece::Type::BISHOP,Color::BLACK,2)));
    pieces.push_back(*(new Piece(Piece::Type::BISHOP,Color::BLACK,5)));
    pieces.push_back(*(new Piece(Piece::Type::QUEEN, Color::BLACK,3)));
    pieces.push_back(*(new Piece(Piece::Type::KING,  Color::BLACK,4)));

    grid = *(new PieceGrid(pieces));
}

Color Board::getSide_to_move() const {
    return side_to_move;
}

const std::bitset<4> &Board::getCastle_rights() const {
    return castle_rights;
}

const std::vector<Piece> &Board::getPieces() const {
    return pieces;
}

const PieceGrid &Board::getGrid() const {
    return grid;
}

std::vector<Move> Board::generate_piece_moves(Piece piece) {


    grid = *(new PieceGrid(pieces));
    int row = piece.getSquare()/8;
    int col = piece.getSquare()%8;
    Piece::Type type = piece.getType();
    Color side = piece.getSide();
    Color capture_side = (side==Color::WHITE)?(Color::BLACK):(Color::WHITE);

    std::vector<Move> moves;

    if(side != this->side_to_move){   //If the piece belongs to the opponent...
        return moves;           //...it can't move. It's not their turn.
    }

    if(type==Piece::Type::PAWN && true){
        Piece::Type promotions[4] = {Piece::Type::QUEEN,Piece::Type::KNIGHT,Piece::Type::ROOK,Piece::Type::BISHOP};
        if(row == 0 || row == 7){
            std::cerr << "[WARN]\tPawn on rank 0 or 8. That shouldn't be possible." << piece.getSquare() << std::endl;
        } else if(this->side_to_move == Color::WHITE){
            //Move forward
            if(grid.get(row-1,col) == nullptr){
                Move mv(piece.getSquare(), row_col_to_id(row - 1, col));
                if(row==1){
                    for(Piece::Type promotion : promotions){
                        mv.setPromotion(promotion);
                        moves.push_back(mv);
                    }
                } else {
                    moves.push_back(mv);
                }
                if(row==6 && grid.get(4,col) == nullptr){//Double step
                    Move mv2(piece.getSquare(), row_col_to_id(4, col), false, true);
                    moves.push_back(mv2);
                }
            }

            //Capture diagonally
            if(col!=0){
                Piece *target = grid.get(row-1,col-1);
                if(target != nullptr && target -> getSide() == Color::BLACK){
                    Move mv(piece.getSquare(), row_col_to_id((row - 1), (int)(col - 1)));
                    if(row==1){
                        for(Piece::Type promotion : promotions){
                            mv.setPromotion(promotion);
                            moves.push_back(mv);
                        }
                    } else {
                        moves.push_back(mv);
                    }
                }
            }
            if(col!=7){
                Piece *target = grid.get(row-1,col+1);
                if(target != nullptr && target -> getSide() == Color::BLACK){
                    Move mv(piece.getSquare(), row_col_to_id((int)(row - 1), (int)(col + 1)));
                    if(row==1){
                        for(Piece::Type promotion : promotions){
                            mv.setPromotion(promotion);
                            moves.push_back(mv);
                        }
                    } else {
                        moves.push_back(mv);
                    }
                }
            }

            if(row == 3){ //En passant
                if(col!=0){
                    Piece *target = grid.get(row-1,col-1);
                    Piece *capture = grid.get(row,col-1);
                    if(capture == nullptr && target != nullptr && target -> getSide() == Color::BLACK && target->getPassant()){
                        Move mv(piece.getSquare(), target->getSquare(),true,false);
                        moves.push_back(mv);
                    }
                }

                if(col!=7){
                    Piece *target = grid.get(row-1,col+1);
                    Piece *capture = grid.get(row,col+1);
                    if(capture == nullptr && target != nullptr && target -> getSide() == Color::BLACK && target->getPassant()){
                        Move mv(piece.getSquare(), target->getSquare(),true,false);
                        moves.push_back(mv);
                    }
                }
            }
        } else { //side_to_move is BLACK

            //Move forward
            if(grid.get(row+1,col) == nullptr){
                Move mv(piece.getSquare(), row_col_to_id((int)(row + 1), col));
                if(row==6){
                    for(Piece::Type promotion : promotions){
                        mv.setPromotion(promotion);
                        moves.push_back(mv);
                    }
                } else {
                    moves.push_back(mv);
                }
                if(row==1 && grid.get(row + 2,col) == nullptr){//Double step
                    Move mv2(piece.getSquare(), row_col_to_id((int)(row + 2), col), false, true);
                    moves.push_back(mv2);
                }
            }

            //Capture diagonally
            if(col!=0){
                Piece *target = grid.get(row+1,col-1);
                if(target != nullptr && target -> getSide() == Color::WHITE){
                    Move mv(piece.getSquare(), row*8+col+7);
                    if(row==6){
                        for(Piece::Type promotion : promotions){
                            mv.setPromotion(promotion);
                            moves.push_back(mv);
                        }
                    } else {
                        moves.push_back(mv);
                    }
                }
            }
            if(col!=7){
                Piece *target = grid.get(row+1,col+1);
                if(target != nullptr&& target -> getSide() == Color::WHITE){
                    Move mv(piece.getSquare(), row*8+col+9);
                    if(row==6){
                        for(Piece::Type promotion : promotions){
                            mv.setPromotion(promotion);
                            moves.push_back(mv);
                        }
                    } else {
                        moves.push_back(mv);
                    }
                }
            }

            if(row == 4){ //En passant
                if(col!=0){
                    Piece *target = grid.get(row+1,col-1);
                    Piece *capture = grid.get(row,col-1);
                    if(capture == nullptr && target != nullptr && target -> getSide() == Color::WHITE && target->getPassant()){
                        Move mv(piece.getSquare(), row_col_to_id((int)(row + 1), (int)(col - 1)),true,false);
                        moves.push_back(mv);
                    }
                }

                if(col!=7){
                    Piece *target = grid.get(row+1,col+1);
                    Piece *capture = grid.get(row,col+1);
                    if(capture == nullptr && target != nullptr && target -> getSide() == Color::WHITE && target->getPassant()){
                        Move mv(piece.getSquare(), row_col_to_id((int)(row + 1), (int)(col + 1)),true,false);
                        moves.push_back(mv);
                    }
                }
            }
        }
    }
    else if(type==Piece::Type::KNIGHT && true){
        /**
         *   0 1
         *  2   3
         *    X
         *  4   5
         *   6 7
         */

        int delta_r[8] = {-2,-2,-1,-1,1,1,2,2};
        int delta_c[8] = {-1,1,-2,2,2,-2,1,-1};
        for(int i = 0; i < 8; i++){
            int target_r = row+delta_r[i];
            int target_c = col+delta_c[i];
            if(-1 < target_c && -1 < target_r && 8>target_c && 8>target_r){
                Piece *target = grid.get(target_r,target_c);
                if(target == nullptr || target -> getSide() == capture_side){
                    Move mv(piece.getSquare(), row_col_to_id(target_r, target_c));
                    moves.push_back(mv);
                }
            }
        }
    }
    else if(type==Piece::Type::KING && true) {
        /**
         *  012
         *  3X4
         *  567
         */

        int delta_r[8] = {-1, -1, -1,  0, 0,  1, 1, 1};
        int delta_c[8] = {-1,  0,  1, -1, 1, -1, 0, 1};
        for(int i = 0; i < 8; i++){
            int target_r = row+delta_r[i];
            int target_c = col+delta_c[i];
            if(-1 < target_c && -1 < target_r && 8>target_c && 8>target_r){
                Piece *target = grid.get(target_r,target_c);
                if(target == nullptr || target -> getSide() == capture_side){
                    Move mv(piece.getSquare(), target_r*8+target_c);
                    moves.push_back(mv);
                }
            }
        }
        //Castling
        if (side == Color::WHITE) {
            if (castle_rights[0] && !grid.get(57) && !grid.get(58) && !grid.get(59)) {
                Move mv(60, 56);
                moves.push_back(mv);
            }
            if (castle_rights[1] && !grid.get(61) && !grid.get(62)) {
                Move mv(60, 63);
                moves.push_back(mv);
            }
        } else {
            if (castle_rights[2] && !grid.get(1) && !grid.get(2) && !grid.get(3)) {
                Move mv(4, 0);
                moves.push_back(mv);
            }
            if (castle_rights[3] && !grid.get(5) && !grid.get(6)) {
                Move mv(4, 7);
                moves.push_back(mv);
            }
        }
    }
    else if(type==Piece::Type::ROOK && true){
        bool ray_blocked;

        ray_blocked = false;
        for(int r = row, c = col; r > -1 && r < 8 && c > -1 && c < 8 && !ray_blocked; r--){
            if(r!=row || c!=col){
                Piece *target = grid.get(r, c);
                ray_blocked = target != nullptr;
                if (target == nullptr || target->getSide() == capture_side) {
                    Move mv(piece.getSquare(), r*8+c);
                    moves.push_back(mv);
                }   
            }
        }

        ray_blocked = false;
        for(int r = row, c = col; r > -1 && r < 8 && c > -1 && c < 8 && !ray_blocked; r++){
            if(r!=row || c!=col){
                Piece *target = grid.get(r, c);
                ray_blocked = target != nullptr;
                if (target == nullptr || target->getSide() == capture_side) {
                    Move mv(piece.getSquare(), r*8+c);
                    moves.push_back(mv);
                }   
            }
        }

        ray_blocked = false;
        for(int r = row, c = col; r > -1 && r < 8 && c > -1 && c < 8 && !ray_blocked; c--){
            if(r!=row || c!=col){
                Piece *target = grid.get(r, c);
                ray_blocked = target != nullptr;
                if (target == nullptr || target->getSide() == capture_side) {
                    Move mv(piece.getSquare(), r*8+c);
                    moves.push_back(mv);
                }   
            }
        }

        ray_blocked = false;
        for(int r = row, c = col; r > -1 && r < 8 && c > -1 && c < 8 && !ray_blocked; c++){
            if(r!=row || c!=col){
                Piece *target = grid.get(r, c);
                ray_blocked = target != nullptr;
                if (target == nullptr || target->getSide() == capture_side) {
                    Move mv(piece.getSquare(), r*8+c);
                    moves.push_back(mv);
                }   
            }
        }
    }
    else if(type==Piece::Type::BISHOP && true){
        bool ray_blocked;

        ray_blocked = false;
        for(int r = row, c = col; r > -1 && r < 8 && c > -1 && c < 8 && !ray_blocked; r--, c--){
            if(r!=row || c!=col){
                Piece *target = grid.get(r, c);
                ray_blocked = target != nullptr;
                if (target == nullptr || target->getSide() == capture_side) {
                    Move mv(piece.getSquare(), r*8+c);
                    moves.push_back(mv);
                }
            }
        }

        ray_blocked = false;
        for(int r = row, c = col; r > -1 && r < 8 && c > -1 && c < 8 && !ray_blocked; r++, c--){
            if(r!=row || c!=col){
                Piece *target = grid.get(r, c);
                ray_blocked = target != nullptr;
                if (target == nullptr || target->getSide() == capture_side) {
                    Move mv(piece.getSquare(), r*8+c);
                    moves.push_back(mv);
                }   
            }
        }

        ray_blocked = false;
        for(int r = row, c = col; r > -1 && r < 8 && c > -1 && c < 8 && !ray_blocked; r--, c++){
            if(r!=row || c!=col){
                Piece *target = grid.get(r, c);
                ray_blocked = target != nullptr;
                if (target == nullptr || target->getSide() == capture_side) {
                    Move mv(piece.getSquare(), r*8+c);
                    moves.push_back(mv);
                }   
            }
        }

        ray_blocked = false;
        for(int r = row, c = col; r > -1 && r < 8 && c > -1 && c < 8 && !ray_blocked; r++, c++){
            if(r!=row || c!=col){
                Piece *target = grid.get(r, c);
                ray_blocked = target != nullptr;
                if (target == nullptr || target->getSide() == capture_side) {
                    Move mv(piece.getSquare(), r*8+c);
                    moves.push_back(mv);
                }   
            }
        }
    }
    else if(type==Piece::Type::QUEEN && true){
        bool ray_blocked = false;

        ray_blocked = false;
        for(int r = row, c = col; r > -1 && r < 8 && c > -1 && c < 8 && !ray_blocked; r--){
            if(r!=row || c!=col){
                Piece *target = grid.get(r, c);
                ray_blocked = target != nullptr;
                if (target == nullptr || target->getSide() == capture_side) {
                    Move mv(piece.getSquare(), r*8+c);
                    moves.push_back(mv);
                }
            }
        }

        ray_blocked = false;
        for(int r = row, c = col; r > -1 && r < 8 && c > -1 && c < 8 && !ray_blocked; r++){
            if(r!=row || c!=col){
                Piece *target = grid.get(r, c);
                ray_blocked = target != nullptr;
                if (target == nullptr || target->getSide() == capture_side) {
                    Move mv(piece.getSquare(), r*8+c);
                    moves.push_back(mv);
                }
            }
        }

        ray_blocked = false;
        for(int r = row, c = col; r > -1 && r < 8 && c > -1 && c < 8 && !ray_blocked; c--){
            if(r!=row || c!=col){
                Piece *target = grid.get(r, c);
                ray_blocked = target != nullptr;
                if (target == nullptr || target->getSide() == capture_side) {
                    Move mv(piece.getSquare(), r*8+c);
                    moves.push_back(mv);
                }
            }
        }

        ray_blocked = false;
        for(int r = row, c = col; r > -1 && r < 8 && c > -1 && c < 8 && !ray_blocked; c++){
            if(r!=row || c!=col){
                Piece *target = grid.get(r, c);
                ray_blocked = target != nullptr;
                if (target == nullptr || target->getSide() == capture_side) {
                    Move mv(piece.getSquare(), r*8+c);
                    moves.push_back(mv);
                }
            }
        }

        ray_blocked = false;
        for(int r = row, c = col; r > -1 && r < 8 && c > -1 && c < 8 && !ray_blocked; r--, c--){
            if(r!=row || c!=col){
                Piece *target = grid.get(r, c);
                ray_blocked = target != nullptr;
                if (target == nullptr || target->getSide() == capture_side) {
                    Move mv(piece.getSquare(), r*8+c);
                    moves.push_back(mv);
                }
            }
        }

        ray_blocked = false;
        for(int r = row, c = col; r > -1 && r < 8 && c > -1 && c < 8 && !ray_blocked; r++, c--){
            if(r!=row || c!=col){
                Piece *target = grid.get(r, c);
                ray_blocked = target != nullptr;
                if (target == nullptr || target->getSide() == capture_side) {
                    Move mv(piece.getSquare(), r*8+c);
                    moves.push_back(mv);
                }
            }
        }

        ray_blocked = false;
        for(int r = row, c = col; r > -1 && r < 8 && c > -1 && c < 8 && !ray_blocked; r--, c++){
            if(r!=row || c!=col){
                Piece *target = grid.get(r, c);
                ray_blocked = target != nullptr;
                if (target == nullptr || target->getSide() == capture_side) {
                    Move mv(piece.getSquare(), r*8+c);
                    moves.push_back(mv);
                }
            }
        }

        ray_blocked = false;
        for(int r = row, c = col; r > -1 && r < 8 && c > -1 && c < 8 && !ray_blocked; r++, c++){
            if(r!=row || c!=col){
                Piece *target = grid.get(r, c);
                ray_blocked = target != nullptr;
                if (target == nullptr || target->getSide() == capture_side) {
                    Move mv(piece.getSquare(), r*8+c);
                    moves.push_back(mv);
                }
            }
        }
    }

    moves.erase(
            std::remove_if(
                    moves.begin(), moves.end(),
                    [this](Move mv){ return !square_occupied(mv.getSource());}),
            moves.end());

    return moves;
}

bool Board::in_check() {
    return false;
}

std::vector<Move> Board::generate_legal_moves() {
    std::vector<Move> moves;
    for(Piece p : pieces){
        std::vector<Move> p_moves = generate_piece_moves(p);
        if(!p_moves.empty()){
            moves.insert(moves.end(), p_moves.begin(), p_moves.end());
        }
    }
    return moves;
}

int Board::row_col_to_id(int row, int col) {
    return (row*8)+col;
}

std::string Board::stringify(){
    std::string out;
    for(int i = 0; i < 64; i++){
        Piece *p = grid.get(i);
        if(p == nullptr){
            out+='_';
        } else {
            switch(p->getSide()) {
                case Color::WHITE:
                    switch (p->getType()) {
                        case Piece::Type::NIL:
                            out += "?";
                            break;
                        case Piece::Type::PAWN:
                            out += "P";
                            break;
                        case Piece::Type::ROOK:
                            out += "R";
                            break;
                        case Piece::Type::BISHOP:
                            out += "B";
                            break;
                        case Piece::Type::KNIGHT:
                            out += "N";
                            break;
                        case Piece::Type::KING:
                            out += "K";
                            break;
                        case Piece::Type::QUEEN:
                            out += "Q";
                            break;
                    }
                    break;
                case Color::BLACK:
                    switch (p->getType()) {
                        case Piece::Type::NIL:
                            out += "!";
                            break;
                        case Piece::Type::PAWN:
                            out += "p";
                            break;
                        case Piece::Type::ROOK:
                            out += "r";
                            break;
                        case Piece::Type::BISHOP:
                            out += "b";
                            break;
                        case Piece::Type::KNIGHT:
                            out += "n";
                            break;
                        case Piece::Type::KING:
                            out += "k";
                            break;
                        case Piece::Type::QUEEN:
                            out += "q";
                            break;
                    }
                    break;
            }
        }
    }
    return out;
}

Board Board::apply_move(Move move) {
    std::cout << move.algebraic_notation() << std::endl;
    std::cout << stringify() << std::endl;


    Board res;
    res.pieces = this->pieces;
    res.side_to_move = (this->side_to_move==Color::WHITE)?(Color::BLACK):(Color::WHITE);

    res.castle_rights[0]=this->castle_rights[0];
    res.castle_rights[1]=this->castle_rights[1];
    res.castle_rights[2]=this->castle_rights[2];
    res.castle_rights[3]=this->castle_rights[3];

    res.grid = *(new PieceGrid(res.pieces));
    Piece *src = res.grid.get(move.getSource());
    Piece *dest = res.grid.get(move.getDest());
    if(src == nullptr){
        throw std::out_of_range("SOURCE PIECE IS NULL");
    }
    for(Piece p : res.pieces){
        if(p.getSide()==this->side_to_move){
            p.setPassant(false);
        }
    }
    if(dest == nullptr){
        if(move.isEn_passant()){
            ///oh fuck off
        } else {
            Piece::Type newType = src->getType();
            if(src->getType()==Piece::Type::PAWN && (move.getDest()/8)%7==0){
                newType = move.getPromotion();
            }
            Piece newPiece(newType, src->getSide(), move.getDest());
            newPiece.setPassant(move.isDouble_step());
            delete_piece_from_list(move.getSource(), res.pieces);
            res.pieces.push_back(newPiece);
        }
    } else {
        if(src->getType()==Piece::Type::KING && dest->getType()==Piece::Type::ROOK && dest->getSide()==src->getSide()){
            //Castle
            Piece newKing = *(new Piece(Piece::Type::KING,(move.getSource()<32)?(Color::BLACK):(Color::WHITE),move.getDest()));
            Piece newRook = *(new Piece(Piece::Type::ROOK,(move.getSource()<32)?(Color::BLACK):(Color::WHITE),move.getSource()));
            if(dest->getSquare() == 54){
                //White queen side
                res.castle_rights[0] = false;
                res.castle_rights[1] = false;
            }
            if(dest->getSquare() == 63){
                //White king side
                res.castle_rights[0] = false;
                res.castle_rights[1] = false;
            }
            if(dest->getSquare() == 0){
                //Black queen side
                res.castle_rights[2] = false;
                res.castle_rights[3] = false;
            }
            if(dest->getSquare() == 7){
                //Black king side
                res.castle_rights[2] = false;
                res.castle_rights[3] = false;
            }
            delete_piece_from_list(move.getSource(), res.pieces);
            delete_piece_from_list(move.getDest(), res.pieces);
            res.pieces.push_back(newKing);
            res.pieces.push_back(newRook);
        } else {
            //Capture
            delete_piece_from_list(move.getDest(),res.pieces);
            Piece::Type newType = src->getType();
            if(src->getType()==Piece::Type::PAWN && (move.getDest()/8)%7==0){
                newType = move.getPromotion();
            }
            Piece newPiece(newType, src->getSide(), move.getDest());
            delete_piece_from_list(move.getSource(), res.pieces);
            res.pieces.push_back(newPiece);
        }
    }

    res.grid = *(new PieceGrid(res.pieces));
    return res;
}

void Board::delete_piece_from_list(int id, std::vector<Piece> &vect) {
    for(int i = 0; i < vect.size(); i++){
        if(vect[i].getSquare()==id){
            vect.erase(vect.begin()+i);
            break;
        }
    }
}

bool Board::square_occupied(int id) {
    for (auto &piece : pieces) {
        if(piece.getSquare()==id){
            return true;
        }
    }
    return false;
}
