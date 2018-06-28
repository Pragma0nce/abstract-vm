#include "IOperand.hpp"

int OperandInt::getPrecision( void ) const
{

}

eOperandType OperandInt::getType( void ) const
{
    return type;
}

 IOperand const * OperandInt::operator+(  IOperand const & rhs ) const
{
    return &rhs;
}
 IOperand const * OperandInt::operator-(  IOperand const & rhs ) const
{
    return &rhs;
}
IOperand const * OperandInt::operator*( IOperand const & rhs ) const
{
    return &rhs;
}
IOperand const * OperandInt::operator/( IOperand const & rhs ) const
{
    return &rhs;
}
IOperand const * OperandInt::operator%( IOperand const & rhs ) const
{
    return &rhs;
}
std::string const & OperandInt::toString( void ) const
{
    return "heh";
}