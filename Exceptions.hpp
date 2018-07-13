#pragma once
#include <exception>
#include <string>

struct ExceptionDivideByZero : public std::exception { char const * what( void ) const _NOEXCEPT; };
struct ExceptionOverflow : public std::exception { char const * what(void) const _NOEXCEPT; };
struct ExceptionUnderflow : public std::exception {char const *what(void) const _NOEXCEPT; } ;
struct ExceptionPopOnEmptyStack : public std::exception { char const * what(void) const _NOEXCEPT; };

class ExceptionUnknownInstruction : public std::exception 
{
private: 
    std::string errorMsg;
public: 
    ExceptionUnknownInstruction(std::string msg);
    char const * what( void ) const _NOEXCEPT; 
    ~ExceptionUnknownInstruction() throw() {};
};