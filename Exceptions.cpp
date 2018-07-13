#include "Exceptions.hpp"

char const * ExceptionDivideByZero::what( void ) const _NOEXCEPT { return "Cannot divide by zero"; }
char const * ExceptionOverflow::what(void) const _NOEXCEPT {return "Overflow"; }
char const * ExceptionPopOnEmptyStack::what(void) const _NOEXCEPT {return "Pop on empty stack";};
char const * ExceptionUnderflow::what(void) const _NOEXCEPT {return "Underflow";};

char const * ExceptionUnknownInstruction::what( void ) const _NOEXCEPT 
{ 
    return errorMsg.c_str(); 
}

ExceptionUnknownInstruction::ExceptionUnknownInstruction(std::string msg)
{
    errorMsg = msg;
}