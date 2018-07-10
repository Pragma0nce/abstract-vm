#include "Operand.hpp"
#include <iostream>
#include <string>
#include "OperandFactory.hpp"

template <typename T>
Operand<T>::Operand(T value )
{
    this->_value = std::to_string(value);
}

// template <typename T>
// int Operand<T>::getPrecision( void ) const
// {
//     return 0;
// }

// template <typename T>
// eOperandType Operand<T>::getType( void ) const
// {
//     return type;
// }

template <typename T>
void Operand<T>::setType(eOperandType _type)
{
    type = _type;
}

template <typename T>
IOperand const * Operand<T>::operator+(  IOperand const & rhs ) const
{
	if (this->getPrecision() < rhs.getPrecision()) return (rhs + *this);
	T lhs_value = static_cast<T>(stod(this->_value));
	T rhs_value = static_cast<T>(stod(rhs.toString()));

	// add_flow_check<T>(lhs_value, rhs_value);
	OperandFactory factory;
	IOperand const * ret_val = factory.createOperand(this->getType(), std::to_string(static_cast<T>(stod(this->_value)) + rhs_value));
	return ret_val;
}

template <typename T>
IOperand const * Operand<T>::operator-(  IOperand const & rhs ) const
{
    return &rhs;
}

template <typename T>
IOperand const * Operand<T>::operator*( IOperand const & rhs ) const
{
    std::cout << "Val1 prec: " << this->getPrecision() << std::endl;
    std::cout << "Val2 prec: " << rhs.getPrecision() << std::endl;

	if (this->getPrecision() < rhs.getPrecision()) return (rhs * *this);
	T lhs_value = static_cast<T>(stod(this->_value));
	T rhs_value = static_cast<T>(stod(rhs.toString()));

	// add_flow_check<T>(lhs_value, rhs_value);
	OperandFactory factory;
	IOperand const * ret_val = factory.createOperand(this->getType(), std::to_string(static_cast<T>(stod(this->_value)) * rhs_value));
	return ret_val;
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

template<class T> 
std::string const & Operand<T>::toString( void ) const 
{
	return this->_value;
}


//****************************
// CLASS TEMPLATE SPECIALIZATION
//****************************

template<> int			Operand<int8_t>::getPrecision( void ) const		{ return t_int8; }
template<> eOperandType	Operand<int8_t>::getType( void ) const			{ return t_int8; }

template<> int			Operand<int16_t>::getPrecision( void ) const	{ return t_int16; }
template<> eOperandType	Operand<int16_t>::getType( void ) const			{ return t_int16; }

template<> int			Operand<int32_t>::getPrecision( void ) const	{ return t_int32; }
template<> eOperandType	Operand<int32_t>::getType( void ) const			{ return t_int32; }

template<> int			Operand<float>::getPrecision( void ) const		{ return t_float; }
template<> eOperandType	Operand<float>::getType( void ) const			{ return t_float; }

template<> int			Operand<double>::getPrecision( void ) const		{ return t_double; }
template<> eOperandType	Operand<double>::getType( void ) const			{ return t_double; }

//****************************
// CLASS TEMPLATE HARD DECLARATION
//****************************

template class Operand<int8_t>;
template class Operand<int16_t>;
template class Operand<int32_t>;
template class Operand<float>;
template class Operand<double>;


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