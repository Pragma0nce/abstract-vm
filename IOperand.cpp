#include "IOperand.hpp"
#include <iostream>
#include <string>

template <typename T>
int Operand<T>::getPrecision( void ) const
{
    return 0;
}

template <typename T>
eOperandType Operand<T>::getType( void ) const
{
    return type;
}

template <typename T>
void Operand<T>::setType(eOperandType _type)
{
    type = _type;
}

template <typename T>
IOperand const * Operand<T>::operator+(  IOperand const & rhs ) const
{
    Operand *op = const_cast<Operand*>(dynamic_cast<const Operand*>(&rhs));
    op->getValue(); 

    return &rhs;
}

template <typename T>
IOperand const * Operand<T>::operator-(  IOperand const & rhs ) const
{
    return &rhs;
}

template <typename T>
IOperand const * Operand<T>::operator*( IOperand const & rhs ) const
{
    return &rhs;
}

template <typename T>
IOperand const * Operand<T>::operator/( IOperand const & rhs ) const 
{
    return &rhs;
}

template <typename T>
IOperand const * Operand<T>::operator%( IOperand const & rhs ) const
{
    return &rhs;
}

template <typename T>
std::string const & Operand<T>::toString( void ) const
{
    std::string *str = new std::string();
    str->clear();
    *str += std::to_string(value.int8);

    return *str;
}

template <typename T>
U_OperandType Operand<T>::getValue()
{
    return value;
}

template <typename T>
void Operand<T>::setValue(U_OperandType _value)
{
    value = _value;
}



/*
 IOperand const * OperandInt8::operator+(  IOperand const & rhs ) const
{
    if (rhs.getType() == eOperandType::t_int8)
    {
        OperandInt8 *ptr = const_cast<OperandInt8*>(dynamic_cast<const OperandInt8 *>(&rhs));
        ptr->value = ptr->value + this->value;
        std::cout << "VALUE: " << (int)ptr->value << std::endl;
    }
    return &rhs;
}
*/