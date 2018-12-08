
#include <stdexcept>
#include "AssertionFailure.h"
#include "Move.h"

uintmax_t Move::count = 0;

Move::~Move() {
    //count--;
}

Move::Move() {
    //count++;

    this->src = 0;
    this->dest = 0;
    this->promotion = 0;
    this->promo_enabled = 0;
    this->null_move = 1;
}

Move::Move(uint8_t src, uint8_t dest){
    //count++;

    this->src = src;
    this->dest = dest;
    this->promotion = 0;
    this->promo_enabled = 0;
    this->null_move = 0;
}

Move::Move(uint8_t src, uint8_t dest, uint8_t promotion){
    //count++;

    this->src = src;
    this->dest = dest;
    this->promotion = promotion;
    this->promo_enabled = 1;
    this->null_move = 0;
}

Move::Move(const Move &other) {
    //count++;

    src = other.src;
    dest = other.dest;
    promotion = other.promotion;
    promo_enabled = other.promo_enabled;
    null_move = other.null_move;
}

Move::Move(std::string an) {
    //count++;

    if(an == "0000"){
        this->src = 0;
        this->dest = 0;
        this->promotion = 0;
        this->promo_enabled = 0;
        this->null_move = 1;
    } else {
        src = ((uint8_t) an[0] - 'a') + ((uint8_t) 64) - ((an[1] - '0') * ((uint8_t) 8));
        dest = ((uint8_t) an[2] - 'a') + ((uint8_t) 64) - ((an[3] - '0') * ((uint8_t) 8));
        promo_enabled = 0;
        if (an.length() == 5) {
            promo_enabled = 1;
            switch (an[5]) {
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
                    char msg[] = "The promotion character in move \"12345\" is invalid.\nValid promotion characters are be q, n, r, or b.";
                    msg[33] = an[0];
                    msg[34] = an[1];
                    msg[35] = an[2];
                    msg[36] = an[3];
                    msg[37] = an[4];
                    ASSERT_FAIL(msg);
            }
        }
    }
}

std::string Move::to_string() const {
    if(null_move == 1){
        return "0000";
    }
    std::string out;
    out+="abcdefgh"[src%8];
    out+="87654321"[src/8];
    out+="abcdefgh"[dest%8];
    out+="87654321"[dest/8];
    if(promo_enabled==1){
        out+="qnrb"[promotion];
    }
    return out;
}

