#ifndef _MUSX_EXCEPTION_HPP_
#define _MUSX_EXCEPTION_HPP_

#include <exception>
#include <cstdio>

//! This macro is use to throw exception under most cases.
#define MUSX_THROW(_what, _func) throw musx::musx_exception(_what, #_func , __FILE__, __LINE__)
//! These macros can stuff in "what" under most cases, of course you can set your own.
#define MUSX_SET_ERR "Musx set error!"
#define MUSX_GET_ERR "Musx get error!"
#define MUSX_ARG_ERR "Musx invalid arguments!"

namespace musx{

class musx_exception : public std::exception
{
public:
    //! summary:
    //! This virtual function inheritage from std::exception::what.
    virtual const char* what() const throw() override 
    {
        static char ThrowStr[(1 << 10)]; // Should be eqaul to 1024.
        std::sprintf(ThrowStr, "%s, %s, %s, %lu", __WhatStr__, __FuncStr__, __FileStr__, __Line__);
        return ThrowStr;
    }
    //! summary:
    //! This function is the constructor of the custom
    //! exception class, which has many useful features that didn't
    //! contain in the original C++ std::exception.
    musx_exception(const char* _What, const char* _Function = "null\0",
              const char* _File = __FILE__, std::size_t _Line = __LINE__)
    {
        std::sprintf(__WhatStr__, "%s", _What);
        std::sprintf(__FuncStr__, "%s", _Function);
        std::sprintf(__FileStr__, "%s", _File);
        __Line__ = _Line;
    }
    //! summary: Return what.
    const char* getWhat(void) const { return __WhatStr__; }
    //! summary: Return file.
    const char* getFile(void) const { return __FileStr__; }
    //! summary: Return function.
    const char* getFunc(void) const { return __FuncStr__; }
    //! summary: Return line.
    std::size_t getLine(void) const { return __Line__; }
    //! summary:
    //! This virtual function also inheritage from std::exception::~exception().
    virtual ~musx_exception() = default;
private:
    // Four strings to store all neccessary strings.
    char __WhatStr__[256];
    char __FileStr__[256];
    char __FuncStr__[64];
    std::size_t __Line__ = 0;
};
}//! namespace musx
#endif //! _MUSX_EXCEPTION_HPP_