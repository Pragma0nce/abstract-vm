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

ExceptionUnknownInstruction::ExceptionUnknownInstruction()
{
    errorMsg = "error";
}

ExceptionUnknownInstruction::ExceptionUnknownInstruction(const ExceptionUnknownInstruction & _instruction)
{
    this->errorMsg = _instruction.errorMsg;
}

ExceptionUnknownInstruction & ExceptionUnknownInstruction::operator=(const ExceptionUnknownInstruction & _rhs)
{
    this->errorMsg = _rhs.errorMsg;
    return *this;
}

ExceptionUnknownInstruction::~ExceptionUnknownInstruction() throw()
{

}