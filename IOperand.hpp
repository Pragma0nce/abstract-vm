#pragma once
#include <string>

enum eOperandType
{
    t_int8,
    t_int16,
    t_int32,
    t_float,
    t_double
};

class IOperand {
protected:
    eOperandType type;
public:
    virtual int getPrecision( void ) const = 0; // Precision of the type of the instance
    virtual eOperandType getType( void ) const = 0; // Type of the instance
    virtual IOperand const * operator+( IOperand const & rhs ) const = 0; // Sum
    virtual IOperand const * operator-( IOperand const & rhs ) const = 0; // Difference
    virtual IOperand const * operator*( IOperand const & rhs ) const = 0; // Product
    virtual IOperand const * operator/( IOperand const & rhs ) const = 0; // Quotient
    virtual IOperand const * operator%( IOperand const & rhs ) const = 0; // Modulo
    virtual std::string const & toString( void ) const = 0; // String representation of the instance
    virtual ~IOperand( void ) {}
};

class OperandInt : public IOperand
{
public:
    int getPrecision( void ) const override; // Precision of the type of the instance
    eOperandType getType( void ) const override; // Type of the instance

    IOperand const * operator+(  IOperand const & rhs ) const override;
    IOperand const * operator-(  IOperand const & rhs ) const override;
    IOperand const * operator*( IOperand const & rhs ) const override; // Product
    IOperand const * operator/( IOperand const & rhs ) const override; // Quotient
    IOperand const * operator%( IOperand const & rhs ) const override; // Modulo
    std::string const & toString( void ) const override; // String representation of the instance
    ~OperandInt( void ) {}
};