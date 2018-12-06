
#ifndef SPODE_UTILS_H
#define SPODE_UTILS_H


#include <string>
#include <sstream>

class Utils {
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
};


#endif //SPODE_UTILS_H
