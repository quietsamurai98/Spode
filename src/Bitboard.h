
#ifndef SPODE_BITBOARD_H
#define SPODE_BITBOARD_H


#include <cstdint>
#include <ostream>
#include <vector>

class Bitboard {
private:
    uint64_t data;
public: //constructors and converters
    Bitboard() noexcept : data(0ULL) {};
    Bitboard(uint64_t const data) noexcept : data(data) {};
    operator uint64_t() const{ return data; }

public: //Data accessors and asymmetric modifiers
    /**
     * Tests if the bit at a given index is set
     * @param index The position of the bit. 0 is the LSB, 64 is the MSB
     * @return true iff the specified bit is set, false otherwise
     * @asserts 0 <= index <= 63
     */
    bool test(int64_t index) const;

    /**
     * Tests if any bit is set
     * @return true iff any bit is set, false otherwise
     */
    bool any() const noexcept { return data != 0;};

    /**
     * Tests if all bits are set
     * @return true iff all bits are set, false otherwise
     */
    bool all() const noexcept { return data == 0xFFFFFFFFFFFFFFFFull;};

    /**
     * Sets the bit at a given index if the passed in value is true, resets the bit otherwise.
     * @param index The position of the bit. 0 is the LSB, 64 is the MSB
     * @param value Whether to set (true) or reset (false) the bit. Defaults to true.
     * @asserts 0 <= index <= 63
     * @modifies data
     */
    void set(int64_t index, bool value = true);

    /**
     * Sets all bits.
     * @modifies data
     */
    void set() noexcept {data = ~0ULL;};

    /**
     * Resets the bit at a given index.
     * @param index The position of the bit. 0 is the LSB, 64 is the MSB
     * @asserts 0 <= index <= 63
     * @modifies data
     */
    void reset(int64_t index){ set(index, false); };

    /**
     * Resets all bits.
     * @modifies data
     */
    void reset() noexcept {data = 0ULL;};

    /**
     * Flips the bit at a given index.
     * @param index The position of the bit. 0 is the LSB, 64 is the MSB
     * @asserts 0 <= index <= 63
     * @modifies data
     */
    void flip(int64_t index){ set(index, !test(index)); };

    /**
     * Flips all bits.
     * @modifies data
     */
    void flip() noexcept {data = ~data;};

public: //methods concerning the count and position of set bits
    /**
     * Gets the number of set bits
     * @returns the total number of bits that are set
     */
    int count() const noexcept {
        return __builtin_popcountll(data);
    }

    /**
     * Gets the index positions of each set bit
     * @return A vector holding the indices of each set bit
     */
    std::vector<int> positions() const;

public: //operation overloads and to_string
    bool operator==(Bitboard const &rhs) const {
        return data == rhs.data;
    }

    bool operator!=(Bitboard const &rhs) const {
        return !(rhs == *this);
    }

    Bitboard operator&(Bitboard const &rhs) const noexcept{
        return Bitboard(data & rhs.data);
    }

    Bitboard operator|(Bitboard const &rhs) const noexcept{
        return Bitboard(data | rhs.data);
    }

    Bitboard operator^(Bitboard const &rhs) const noexcept{
        return Bitboard(data ^ rhs.data);
    }

    Bitboard operator<<(Bitboard const &rhs) const noexcept{
        return Bitboard(data << rhs.data);
    }

    Bitboard operator>>(Bitboard const &rhs) const noexcept{
        return Bitboard(data >> rhs.data);
    }

    Bitboard& operator&=(Bitboard const &rhs) noexcept{
        data &= rhs.data;
        return *this;
    }

    Bitboard& operator|=(Bitboard const &rhs) noexcept{
        data |= rhs.data;
        return *this;
    }

    Bitboard& operator^=(Bitboard const &rhs) noexcept{
        data ^= rhs.data;
        return *this;
    }

    Bitboard& operator<<=(Bitboard const &rhs) noexcept{
        data <<= rhs.data;
        return *this;
    }

    Bitboard& operator>>=(Bitboard const &rhs) noexcept{
        data >>= rhs.data;
        return *this;
    }

    Bitboard operator~() const noexcept{
        return Bitboard(~data);
    }

    friend std::ostream &operator<<(std::ostream &os, Bitboard const &bitboard);

    std::string to_string() const noexcept;

public: //symmetric transformation modifiers
    /**
     * Reflects the board over the horizontal axis. Rank N is swapped with rank 9-N (1 and 8, 2 and 7, 3 and 6, etc).
     * @return A reference to *this
     * @modifies data
     */
    Bitboard& sym_reflect_horizontal() noexcept;

    /**
     * Reflects the board over the vertical axis. File N is swapped with file 'i'-N (a and h, b and g, c and f, etc).
     * @return A reference to *this
     * @modifies data
     */
    Bitboard& sym_reflect_vertical() noexcept;
    /**
     * Reflects the board over the main-diagonal. a1 maps to h8
     * @return A reference to *this
     * @modifies data
     */
    Bitboard& sym_reflect_maindiagonal() noexcept;

    /**
     * Reflects the board over the anti-diagonal. a8 maps to h1
     * @return A reference to *this
     * @modifies data
     */
    Bitboard& sym_reflect_antidiagonal() noexcept;

    /**
     * Rotates the board 90 degrees clockwise
     * @return A reference to *this
     * @modifies data
     */
    Bitboard& sym_rot_cw() noexcept{
        return sym_reflect_maindiagonal().sym_reflect_vertical();
    }

    /**
     * Rotates the board 90 degrees counter-clockwise
     * @return A reference to *this
     * @modifies data
     */
    Bitboard& sym_rot_ccw() noexcept{
        return sym_reflect_antidiagonal().sym_reflect_vertical();
    }

    /**
     * Rotates the board 180 degrees
     * @return A reference to *this
     * @modifies data
     */
    Bitboard& sym_rot_180() noexcept{
        return sym_reflect_vertical().sym_reflect_horizontal();
    }
};


#endif //SPODE_BITBOARD_H
