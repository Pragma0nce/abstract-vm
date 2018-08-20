#pragma once
#include "IOperand.hpp"

template <typename T>
class Operand : public IOperand 
{
private:
    std::string _value;
public:
    Operand( T value );
    Operand  & operator=(const Operand & _rhs);
    Operand (const Operand  & _op);
    Operand();
    ~Operand();

    int getPrecision( void ) const override; // Precision of the type of the instance
    eOperandType getType( void ) const override; // Type of the instance
    void setType(eOperandType _type);

    IOperand const * operator+(  IOperand const & rhs ) const override;
    IOperand const * operator-(  IOperand const & rhs ) const override;
    IOperand const * operator*( IOperand const & rhs ) const override; // Product
    IOperand const * operator/( IOperand const & rhs ) const override; // Quotient
    IOperand const * operator%( IOperand const & rhs ) const override; // Modulo
    std::string const & toString( void ) const override; // String representation of the instance

};