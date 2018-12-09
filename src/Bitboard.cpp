
#include "Bitboard.h"
#include "AssertionFailure.h"

bool Bitboard::literal_test(int64_t index) const {
    switch (index){
        case  0: return (data & 0b0000000000000000000000000000000000000000000000000000000000000001) != 0;
        case  1: return (data & 0b0000000000000000000000000000000000000000000000000000000000000010) != 0;
        case  2: return (data & 0b0000000000000000000000000000000000000000000000000000000000000100) != 0;
        case  3: return (data & 0b0000000000000000000000000000000000000000000000000000000000001000) != 0;
        case  4: return (data & 0b0000000000000000000000000000000000000000000000000000000000010000) != 0;
        case  5: return (data & 0b0000000000000000000000000000000000000000000000000000000000100000) != 0;
        case  6: return (data & 0b0000000000000000000000000000000000000000000000000000000001000000) != 0;
        case  7: return (data & 0b0000000000000000000000000000000000000000000000000000000010000000) != 0;
        case  8: return (data & 0b0000000000000000000000000000000000000000000000000000000100000000) != 0;
        case  9: return (data & 0b0000000000000000000000000000000000000000000000000000001000000000) != 0;
        case 10: return (data & 0b0000000000000000000000000000000000000000000000000000010000000000) != 0;
        case 11: return (data & 0b0000000000000000000000000000000000000000000000000000100000000000) != 0;
        case 12: return (data & 0b0000000000000000000000000000000000000000000000000001000000000000) != 0;
        case 13: return (data & 0b0000000000000000000000000000000000000000000000000010000000000000) != 0;
        case 14: return (data & 0b0000000000000000000000000000000000000000000000000100000000000000) != 0;
        case 15: return (data & 0b0000000000000000000000000000000000000000000000001000000000000000) != 0;
        case 16: return (data & 0b0000000000000000000000000000000000000000000000010000000000000000) != 0;
        case 17: return (data & 0b0000000000000000000000000000000000000000000000100000000000000000) != 0;
        case 18: return (data & 0b0000000000000000000000000000000000000000000001000000000000000000) != 0;
        case 19: return (data & 0b0000000000000000000000000000000000000000000010000000000000000000) != 0;
        case 20: return (data & 0b0000000000000000000000000000000000000000000100000000000000000000) != 0;
        case 21: return (data & 0b0000000000000000000000000000000000000000001000000000000000000000) != 0;
        case 22: return (data & 0b0000000000000000000000000000000000000000010000000000000000000000) != 0;
        case 23: return (data & 0b0000000000000000000000000000000000000000100000000000000000000000) != 0;
        case 24: return (data & 0b0000000000000000000000000000000000000001000000000000000000000000) != 0;
        case 25: return (data & 0b0000000000000000000000000000000000000010000000000000000000000000) != 0;
        case 26: return (data & 0b0000000000000000000000000000000000000100000000000000000000000000) != 0;
        case 27: return (data & 0b0000000000000000000000000000000000001000000000000000000000000000) != 0;
        case 28: return (data & 0b0000000000000000000000000000000000010000000000000000000000000000) != 0;
        case 29: return (data & 0b0000000000000000000000000000000000100000000000000000000000000000) != 0;
        case 30: return (data & 0b0000000000000000000000000000000001000000000000000000000000000000) != 0;
        case 31: return (data & 0b0000000000000000000000000000000010000000000000000000000000000000) != 0;
        case 32: return (data & 0b0000000000000000000000000000000100000000000000000000000000000000) != 0;
        case 33: return (data & 0b0000000000000000000000000000001000000000000000000000000000000000) != 0;
        case 34: return (data & 0b0000000000000000000000000000010000000000000000000000000000000000) != 0;
        case 35: return (data & 0b0000000000000000000000000000100000000000000000000000000000000000) != 0;
        case 36: return (data & 0b0000000000000000000000000001000000000000000000000000000000000000) != 0;
        case 37: return (data & 0b0000000000000000000000000010000000000000000000000000000000000000) != 0;
        case 38: return (data & 0b0000000000000000000000000100000000000000000000000000000000000000) != 0;
        case 39: return (data & 0b0000000000000000000000001000000000000000000000000000000000000000) != 0;
        case 40: return (data & 0b0000000000000000000000010000000000000000000000000000000000000000) != 0;
        case 41: return (data & 0b0000000000000000000000100000000000000000000000000000000000000000) != 0;
        case 42: return (data & 0b0000000000000000000001000000000000000000000000000000000000000000) != 0;
        case 43: return (data & 0b0000000000000000000010000000000000000000000000000000000000000000) != 0;
        case 44: return (data & 0b0000000000000000000100000000000000000000000000000000000000000000) != 0;
        case 45: return (data & 0b0000000000000000001000000000000000000000000000000000000000000000) != 0;
        case 46: return (data & 0b0000000000000000010000000000000000000000000000000000000000000000) != 0;
        case 47: return (data & 0b0000000000000000100000000000000000000000000000000000000000000000) != 0;
        case 48: return (data & 0b0000000000000001000000000000000000000000000000000000000000000000) != 0;
        case 49: return (data & 0b0000000000000010000000000000000000000000000000000000000000000000) != 0;
        case 50: return (data & 0b0000000000000100000000000000000000000000000000000000000000000000) != 0;
        case 51: return (data & 0b0000000000001000000000000000000000000000000000000000000000000000) != 0;
        case 52: return (data & 0b0000000000010000000000000000000000000000000000000000000000000000) != 0;
        case 53: return (data & 0b0000000000100000000000000000000000000000000000000000000000000000) != 0;
        case 54: return (data & 0b0000000001000000000000000000000000000000000000000000000000000000) != 0;
        case 55: return (data & 0b0000000010000000000000000000000000000000000000000000000000000000) != 0;
        case 56: return (data & 0b0000000100000000000000000000000000000000000000000000000000000000) != 0;
        case 57: return (data & 0b0000001000000000000000000000000000000000000000000000000000000000) != 0;
        case 58: return (data & 0b0000010000000000000000000000000000000000000000000000000000000000) != 0;
        case 59: return (data & 0b0000100000000000000000000000000000000000000000000000000000000000) != 0;
        case 60: return (data & 0b0001000000000000000000000000000000000000000000000000000000000000) != 0;
        case 61: return (data & 0b0010000000000000000000000000000000000000000000000000000000000000) != 0;
        case 62: return (data & 0b0100000000000000000000000000000000000000000000000000000000000000) != 0;
        case 63: return (data & 0b1000000000000000000000000000000000000000000000000000000000000000) != 0;
        default: ASSERT_FAIL("Index may not be outside of the interval [0..63]!");
    }
}

void Bitboard::literal_set(int64_t index, bool value) {
    if(value) {
        switch (index) {
            case  0: data |= 0b0000000000000000000000000000000000000000000000000000000000000001; return;
            case  1: data |= 0b0000000000000000000000000000000000000000000000000000000000000010; return;
            case  2: data |= 0b0000000000000000000000000000000000000000000000000000000000000100; return;
            case  3: data |= 0b0000000000000000000000000000000000000000000000000000000000001000; return;
            case  4: data |= 0b0000000000000000000000000000000000000000000000000000000000010000; return;
            case  5: data |= 0b0000000000000000000000000000000000000000000000000000000000100000; return;
            case  6: data |= 0b0000000000000000000000000000000000000000000000000000000001000000; return;
            case  7: data |= 0b0000000000000000000000000000000000000000000000000000000010000000; return;
            case  8: data |= 0b0000000000000000000000000000000000000000000000000000000100000000; return;
            case  9: data |= 0b0000000000000000000000000000000000000000000000000000001000000000; return;
            case 10: data |= 0b0000000000000000000000000000000000000000000000000000010000000000; return;
            case 11: data |= 0b0000000000000000000000000000000000000000000000000000100000000000; return;
            case 12: data |= 0b0000000000000000000000000000000000000000000000000001000000000000; return;
            case 13: data |= 0b0000000000000000000000000000000000000000000000000010000000000000; return;
            case 14: data |= 0b0000000000000000000000000000000000000000000000000100000000000000; return;
            case 15: data |= 0b0000000000000000000000000000000000000000000000001000000000000000; return;
            case 16: data |= 0b0000000000000000000000000000000000000000000000010000000000000000; return;
            case 17: data |= 0b0000000000000000000000000000000000000000000000100000000000000000; return;
            case 18: data |= 0b0000000000000000000000000000000000000000000001000000000000000000; return;
            case 19: data |= 0b0000000000000000000000000000000000000000000010000000000000000000; return;
            case 20: data |= 0b0000000000000000000000000000000000000000000100000000000000000000; return;
            case 21: data |= 0b0000000000000000000000000000000000000000001000000000000000000000; return;
            case 22: data |= 0b0000000000000000000000000000000000000000010000000000000000000000; return;
            case 23: data |= 0b0000000000000000000000000000000000000000100000000000000000000000; return;
            case 24: data |= 0b0000000000000000000000000000000000000001000000000000000000000000; return;
            case 25: data |= 0b0000000000000000000000000000000000000010000000000000000000000000; return;
            case 26: data |= 0b0000000000000000000000000000000000000100000000000000000000000000; return;
            case 27: data |= 0b0000000000000000000000000000000000001000000000000000000000000000; return;
            case 28: data |= 0b0000000000000000000000000000000000010000000000000000000000000000; return;
            case 29: data |= 0b0000000000000000000000000000000000100000000000000000000000000000; return;
            case 30: data |= 0b0000000000000000000000000000000001000000000000000000000000000000; return;
            case 31: data |= 0b0000000000000000000000000000000010000000000000000000000000000000; return;
            case 32: data |= 0b0000000000000000000000000000000100000000000000000000000000000000; return;
            case 33: data |= 0b0000000000000000000000000000001000000000000000000000000000000000; return;
            case 34: data |= 0b0000000000000000000000000000010000000000000000000000000000000000; return;
            case 35: data |= 0b0000000000000000000000000000100000000000000000000000000000000000; return;
            case 36: data |= 0b0000000000000000000000000001000000000000000000000000000000000000; return;
            case 37: data |= 0b0000000000000000000000000010000000000000000000000000000000000000; return;
            case 38: data |= 0b0000000000000000000000000100000000000000000000000000000000000000; return;
            case 39: data |= 0b0000000000000000000000001000000000000000000000000000000000000000; return;
            case 40: data |= 0b0000000000000000000000010000000000000000000000000000000000000000; return;
            case 41: data |= 0b0000000000000000000000100000000000000000000000000000000000000000; return;
            case 42: data |= 0b0000000000000000000001000000000000000000000000000000000000000000; return;
            case 43: data |= 0b0000000000000000000010000000000000000000000000000000000000000000; return;
            case 44: data |= 0b0000000000000000000100000000000000000000000000000000000000000000; return;
            case 45: data |= 0b0000000000000000001000000000000000000000000000000000000000000000; return;
            case 46: data |= 0b0000000000000000010000000000000000000000000000000000000000000000; return;
            case 47: data |= 0b0000000000000000100000000000000000000000000000000000000000000000; return;
            case 48: data |= 0b0000000000000001000000000000000000000000000000000000000000000000; return;
            case 49: data |= 0b0000000000000010000000000000000000000000000000000000000000000000; return;
            case 50: data |= 0b0000000000000100000000000000000000000000000000000000000000000000; return;
            case 51: data |= 0b0000000000001000000000000000000000000000000000000000000000000000; return;
            case 52: data |= 0b0000000000010000000000000000000000000000000000000000000000000000; return;
            case 53: data |= 0b0000000000100000000000000000000000000000000000000000000000000000; return;
            case 54: data |= 0b0000000001000000000000000000000000000000000000000000000000000000; return;
            case 55: data |= 0b0000000010000000000000000000000000000000000000000000000000000000; return;
            case 56: data |= 0b0000000100000000000000000000000000000000000000000000000000000000; return;
            case 57: data |= 0b0000001000000000000000000000000000000000000000000000000000000000; return;
            case 58: data |= 0b0000010000000000000000000000000000000000000000000000000000000000; return;
            case 59: data |= 0b0000100000000000000000000000000000000000000000000000000000000000; return;
            case 60: data |= 0b0001000000000000000000000000000000000000000000000000000000000000; return;
            case 61: data |= 0b0010000000000000000000000000000000000000000000000000000000000000; return;
            case 62: data |= 0b0100000000000000000000000000000000000000000000000000000000000000; return;
            case 63: data |= 0b1000000000000000000000000000000000000000000000000000000000000000; return;
            default: ASSERT_FAIL("Index may not be outside of the interval [0..63]!");
        }
    } else {
        switch (index) {
            case  0: data &= 0b1111111111111111111111111111111111111111111111111111111111111110; return;
            case  1: data &= 0b1111111111111111111111111111111111111111111111111111111111111101; return;
            case  2: data &= 0b1111111111111111111111111111111111111111111111111111111111111011; return;
            case  3: data &= 0b1111111111111111111111111111111111111111111111111111111111110111; return;
            case  4: data &= 0b1111111111111111111111111111111111111111111111111111111111101111; return;
            case  5: data &= 0b1111111111111111111111111111111111111111111111111111111111011111; return;
            case  6: data &= 0b1111111111111111111111111111111111111111111111111111111110111111; return;
            case  7: data &= 0b1111111111111111111111111111111111111111111111111111111101111111; return;
            case  8: data &= 0b1111111111111111111111111111111111111111111111111111111011111111; return;
            case  9: data &= 0b1111111111111111111111111111111111111111111111111111110111111111; return;
            case 10: data &= 0b1111111111111111111111111111111111111111111111111111101111111111; return;
            case 11: data &= 0b1111111111111111111111111111111111111111111111111111011111111111; return;
            case 12: data &= 0b1111111111111111111111111111111111111111111111111110111111111111; return;
            case 13: data &= 0b1111111111111111111111111111111111111111111111111101111111111111; return;
            case 14: data &= 0b1111111111111111111111111111111111111111111111111011111111111111; return;
            case 15: data &= 0b1111111111111111111111111111111111111111111111110111111111111111; return;
            case 16: data &= 0b1111111111111111111111111111111111111111111111101111111111111111; return;
            case 17: data &= 0b1111111111111111111111111111111111111111111111011111111111111111; return;
            case 18: data &= 0b1111111111111111111111111111111111111111111110111111111111111111; return;
            case 19: data &= 0b1111111111111111111111111111111111111111111101111111111111111111; return;
            case 20: data &= 0b1111111111111111111111111111111111111111111011111111111111111111; return;
            case 21: data &= 0b1111111111111111111111111111111111111111110111111111111111111111; return;
            case 22: data &= 0b1111111111111111111111111111111111111111101111111111111111111111; return;
            case 23: data &= 0b1111111111111111111111111111111111111111011111111111111111111111; return;
            case 24: data &= 0b1111111111111111111111111111111111111110111111111111111111111111; return;
            case 25: data &= 0b1111111111111111111111111111111111111101111111111111111111111111; return;
            case 26: data &= 0b1111111111111111111111111111111111111011111111111111111111111111; return;
            case 27: data &= 0b1111111111111111111111111111111111110111111111111111111111111111; return;
            case 28: data &= 0b1111111111111111111111111111111111101111111111111111111111111111; return;
            case 29: data &= 0b1111111111111111111111111111111111011111111111111111111111111111; return;
            case 30: data &= 0b1111111111111111111111111111111110111111111111111111111111111111; return;
            case 31: data &= 0b1111111111111111111111111111111101111111111111111111111111111111; return;
            case 32: data &= 0b1111111111111111111111111111111011111111111111111111111111111111; return;
            case 33: data &= 0b1111111111111111111111111111110111111111111111111111111111111111; return;
            case 34: data &= 0b1111111111111111111111111111101111111111111111111111111111111111; return;
            case 35: data &= 0b1111111111111111111111111111011111111111111111111111111111111111; return;
            case 36: data &= 0b1111111111111111111111111110111111111111111111111111111111111111; return;
            case 37: data &= 0b1111111111111111111111111101111111111111111111111111111111111111; return;
            case 38: data &= 0b1111111111111111111111111011111111111111111111111111111111111111; return;
            case 39: data &= 0b1111111111111111111111110111111111111111111111111111111111111111; return;
            case 40: data &= 0b1111111111111111111111101111111111111111111111111111111111111111; return;
            case 41: data &= 0b1111111111111111111111011111111111111111111111111111111111111111; return;
            case 42: data &= 0b1111111111111111111110111111111111111111111111111111111111111111; return;
            case 43: data &= 0b1111111111111111111101111111111111111111111111111111111111111111; return;
            case 44: data &= 0b1111111111111111111011111111111111111111111111111111111111111111; return;
            case 45: data &= 0b1111111111111111110111111111111111111111111111111111111111111111; return;
            case 46: data &= 0b1111111111111111101111111111111111111111111111111111111111111111; return;
            case 47: data &= 0b1111111111111111011111111111111111111111111111111111111111111111; return;
            case 48: data &= 0b1111111111111110111111111111111111111111111111111111111111111111; return;
            case 49: data &= 0b1111111111111101111111111111111111111111111111111111111111111111; return;
            case 50: data &= 0b1111111111111011111111111111111111111111111111111111111111111111; return;
            case 51: data &= 0b1111111111110111111111111111111111111111111111111111111111111111; return;
            case 52: data &= 0b1111111111101111111111111111111111111111111111111111111111111111; return;
            case 53: data &= 0b1111111111011111111111111111111111111111111111111111111111111111; return;
            case 54: data &= 0b1111111110111111111111111111111111111111111111111111111111111111; return;
            case 55: data &= 0b1111111101111111111111111111111111111111111111111111111111111111; return;
            case 56: data &= 0b1111111011111111111111111111111111111111111111111111111111111111; return;
            case 57: data &= 0b1111110111111111111111111111111111111111111111111111111111111111; return;
            case 58: data &= 0b1111101111111111111111111111111111111111111111111111111111111111; return;
            case 59: data &= 0b1111011111111111111111111111111111111111111111111111111111111111; return;
            case 60: data &= 0b1110111111111111111111111111111111111111111111111111111111111111; return;
            case 61: data &= 0b1101111111111111111111111111111111111111111111111111111111111111; return;
            case 62: data &= 0b1011111111111111111111111111111111111111111111111111111111111111; return;
            case 63: data &= 0b0111111111111111111111111111111111111111111111111111111111111111; return;
            default: ASSERT_FAIL("Index may not be outside of the interval [0..63]!");
        }
    }
}

bool Bitboard::test(int64_t index) const {
    return 0 != (data & (1ull << index));
}

void Bitboard::set(int64_t index, bool value){
    if(value){
        data |= (1ull << index);
    } else {
        data &= ~(1ull << index);
    }
}

std::vector<int> Bitboard::positions() const {
    uint64_t tmp = data;
    std::vector<int> out;
    while(tmp != 0){
        int pos = __builtin_ffsll(tmp) - 1;
        out.push_back(pos);
        tmp &= ~(1ull<<pos);
    }
    return out;
}

std::ostream &operator<<(std::ostream &os, const Bitboard &bitboard) {
    os << bitboard.to_string();
    return os;
}

std::string Bitboard::to_string() const noexcept {
    std::stringstream out;
    for(int_fast8_t i = 0; i < 56; i+=8){
        out << (test(i)?'X':'.') << (test(i+1)?'X':'.') << (test(i+2)?'X':'.') << (test(i+3)?'X':'.') << (test(i+4)?'X':'.') << (test(i+5)?'X':'.') << (test(i+6)?'X':'.') << (test(i+7)?'X':'.') << '\n';
    }
    out << (test(56)?'X':'.') << (test(57)?'X':'.') << (test(58)?'X':'.') << (test(59)?'X':'.') << (test(60)?'X':'.') << (test(61)?'X':'.') << (test(62)?'X':'.') << (test(63)?'X':'.');
    return out.str();
}

Bitboard &Bitboard::sym_reflect_horizontal() noexcept {
    data = __builtin_bswap64(data);
    return *this;
}

Bitboard &Bitboard::sym_reflect_vertical() noexcept {
    data = ((data >> 1) & 0x5555555555555555) | ((data & 0x5555555555555555) << 1);
    data = ((data >> 2) & 0x3333333333333333) | ((data & 0x3333333333333333) << 2);
    data = ((data >> 4) & 0x0f0f0f0f0f0f0f0f) | ((data & 0x0f0f0f0f0f0f0f0f) << 4);
    return *this;
}

Bitboard &Bitboard::sym_reflect_maindiagonal() noexcept {
    uint64_t tmp;
    tmp  = 0x0f0f0f0f00000000 & (data ^ (data << 28));
    data ^= tmp ^ (tmp >> 28) ;
    tmp  = 0x3333000033330000 & (data ^ (data << 14));
    data ^= tmp ^ (tmp >> 14) ;
    tmp  = 0x5500550055005500 & (data ^ (data <<  7));
    data ^= tmp ^ (tmp >>  7) ;
    return *this;
}

Bitboard &Bitboard::sym_reflect_antidiagonal() noexcept {
    uint64_t tmp;
    tmp  =  data ^ (data << 36) ;
    data ^= 0xf0f0f0f00f0f0f0f & (tmp ^ (data >> 36));
    tmp  = 0xcccc0000cccc0000 & (data ^ (data << 18));
    data ^=  tmp ^ (tmp >> 18) ;
    tmp  = 0xaa00aa00aa00aa00 & (data ^ (data <<  9));
    data ^=  tmp ^ (tmp >>  9) ;
    return *this;
}
