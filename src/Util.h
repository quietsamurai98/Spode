
#ifndef SPODE_UTIL_H
#define SPODE_UTIL_H


#include <string>
#include <sstream>

class Util {
public:
    static std::string human_readable_bytes(uintmax_t bytes){
        uintmax_t b = bytes;
        uintmax_t kb = b/1024;
        uintmax_t mb = kb/1024;
        kb-= (mb*1024);
        b -= (mb*1024*1024) + (kb*1024);
        std::stringstream outstream;
        if(mb)
            outstream << mb << "MB ";
        if(kb)
            outstream << kb << "KB ";
        if(b)
            outstream << b << "B ";
        auto out = outstream.str();
        out.pop_back();
        return out;
    }

    /**
     * Shorthand for (min <= value && value <= max)
     * @tparam T Any type that supports the leq and geq operators.
     * @param value The value in question
     * @param min The minimum allowed value (inclusive)
     * @param max The maximum allowed value (inclusive)
     * @return min <= value && value <= max
     */
    inline static bool on_range(int const value, int const min, int const max){
        return  min <= value && value <= max;
    }
    template <typename T>
    inline static bool on_range(T const& value, T const& min, T const& max){
        return  min <= value && value <= max;
    }
};


#endif //SPODE_UTIL_H
