
#include <stdexcept>
#include "Move.h"

Move::Move(uint8_t src, uint8_t dest) : src(src), dest(dest){

}

Move::Move(uint8_t src, uint8_t dest, uint8_t promotion) : src(src), dest(dest), promotion(promotion){

}

Move::Move(std::string an) {
    src = ((uint8_t) an[0]-'a')+((uint8_t) 64)-((an[1]-'0')*((uint8_t) 8));
    dest = ((uint8_t) an[2]-'a')+((uint8_t) 64)-((an[3]-'0')*((uint8_t) 8));
    if(an.length()==5){
        switch (an[5]){
            case 'q':
                promotion = 0;
                break;
            case 'n':
                promotion = 1;
                break;
            case 'r':
                promotion = 2;
                break;
            case 'b':
                promotion = 3;
                break;
            default:
                throw std::logic_error("Invalid promotion!");
        }
    }
}
