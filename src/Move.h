#ifndef SPODE_MOVE_H
#define SPODE_MOVE_H


#include <cstdint>
#include <string>
#include <iostream>

class Move {
public:
    static uintmax_t count;

    Move();
    Move(uint8_t src, uint8_t dest);
    Move(uint8_t src, uint8_t dest, uint8_t promotion);
    explicit Move(std::string an);
    Move(const Move &other);
    ~Move();


    uint8_t src  : 6;
    uint8_t promotion : 2; //0 = queen, 1 = knight, 2 = rook, 3 = bishop
    uint8_t dest : 6;
    uint8_t promo_enabled : 1;
    uint8_t null_move : 1;
    std::string to_string() const;
};


#endif //SPODE_MOVE_H
