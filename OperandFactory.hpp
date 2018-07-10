#pragma once 

#include <string>
#include "IOperand.hpp"

class OperandFactory 
{
private:
    IOperand const * createInt8( std::string const & value ) const;
    IOperand const * createInt16( std::string const & value ) const;
    IOperand const * createInt32( std::string const & value ) const;
    IOperand const * createFloat( std::string const & value ) const;
    IOperand const * createDouble( std::string const & value ) const;
public: 
    typedef IOperand const * (OperandFactory::*Memfuncts)(std::string const &) const;
    IOperand const * createOperand( eOperandType type, std::string const & value ) const;
};