#ifndef SPODE_MOVE_H
#define SPODE_MOVE_H


#include <cstdint>
#include <string>

class Move {
public:
    Move(uint8_t src, uint8_t dest);
    Move(uint8_t src, uint8_t dest, uint8_t promotion);
    Move(std::string an);
    uint8_t src  : 6;
    uint8_t promotion : 2; //0 = queen, 1 = knight, 2 = rook, 3 = bishop
    uint8_t dest : 6;
    uint8_t promo_enabled : 1;
    std::string to_string();
};


#endif //SPODE_MOVE_H
