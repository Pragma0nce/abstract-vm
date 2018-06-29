#include "OperandFactory.hpp"
// #include "IOperand.cpp"


IOperand const * OperandFactory::createInt8( std::string const & value ) const
{
    return createOperand(eOperandType::t_int8, value);
}

IOperand const * OperandFactory::createInt16( std::string const & value ) const
{
    return createOperand(eOperandType::t_int8, value);
}

IOperand const * OperandFactory::createInt32( std::string const & value ) const
{
    return createOperand(eOperandType::t_int8, value);
}

IOperand const * OperandFactory::createFloat( std::string const & value ) const
{
    return createOperand(eOperandType::t_int8, value);
}

IOperand const * OperandFactory::createDouble( std::string const & value ) const
{
    return createOperand(eOperandType::t_int8, value);
}

IOperand const * OperandFactory::createOperand( eOperandType type, std::string const & value ) const
{
    Operand<char> *op = new Operand<char>();
    U_OperandType newValue;
    newValue.int8 = std::stoi(value);
    op->setValue(newValue);
    op->setType(eOperandType::t_int8);    
    return op;
}
