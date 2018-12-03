#ifndef SPODE_MOVE_H
#define SPODE_MOVE_H


#include <cstdint>

class Move {
public:
    Move(uint8_t src, uint8_t dest);
    Move(uint8_t src, uint8_t dest, uint8_t promotion);
    uint8_t src  : 6;
    uint8_t promotion : 2; //0 = queen, 1 = knight, 2 = rook, 3 = bishop
    uint8_t dest : 6;
};


#endif //SPODE_MOVE_H
