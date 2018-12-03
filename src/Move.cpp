
#include "Move.h"

Move::Move(uint8_t src, uint8_t dest) : src(src), dest(dest){

}

Move::Move(uint8_t src, uint8_t dest, uint8_t promotion) : src(src), dest(dest), promotion(promotion){

}