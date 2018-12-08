
#ifndef SPODE_ASSERT_H
#define SPODE_ASSERT_H


#include <exception>
#include <sstream>

class AssertionFailure{
public:
    AssertionFailure(const char* expr, const char* msg, const char* file, const int line, const char* func){
        std::stringstream ss;
        ss << "Assertion failed! ("<<func<<"@"<<file<<":"<<line<<")\n";
        ss << "\tAssertion condition:\t\"" << expr << "\"\n";
        std::string msg_str = std::string(msg);
        auto pos = msg_str.find('\n');
        while(pos != std::string::npos){
            msg_str.replace(pos, 1, "\n\t\t");
            pos = msg_str.find('\n', pos+3);
        }
        ss << "\tDetails:\n\t\t" << msg_str;
        throw std::runtime_error(ss.str().c_str());
    }

    AssertionFailure(const char* msg, const char* file, const int line, const char* func){
        std::stringstream ss;
        ss << "A failure state was asserted! ("<<func<<"@"<<file<<":"<<line<<")\n";
        std::string msg_str = std::string(msg);
        auto pos = msg_str.find('\n');
        while(pos != std::string::npos){
            msg_str.replace(pos, 1, "\n\t\t");
            pos = msg_str.find('\n', pos+3);
        }
        ss << "\tDetails:\n\t\t" << msg_str;
        throw std::runtime_error(ss.str().c_str());
    }

};

#ifdef ASSERT
#error "ASSERT macro already defined!"
#else
#ifndef DISABLE_ASSERT //Disabling assertions will increase performance, but will potentially allow the program to enter into invalid states.
#define ASSERT(expr, msg) if(!(expr)){AssertionFailure(#expr, msg, __FILE__, __LINE__, __PRETTY_FUNCTION__);} (void)0
#else
#define ASSERT(expr, msg) (void)0
#endif
#endif

#ifdef ASSERT_FAIL
#error "ASSERT_FAIL macro already defined!"
#else
#ifndef DISABLE_ASSERT_FAIL //There is no reason for ASSERT_FAILs to be disabled, as they are only ever callable when the program has entered into a known invalid state.
#define ASSERT_FAIL(msg) AssertionFailure(msg, __FILE__, __LINE__, __PRETTY_FUNCTION__); exit(-1)
#else
#define ASSERT_FAIL(MSG) (void)0
#endif
#endif


#endif //SPODE_ASSERT_H
