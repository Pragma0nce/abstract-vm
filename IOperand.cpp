#include "IOperand.hpp" 

IOperand::IOperand()
{

}

IOperand::IOperand(const IOperand & _op)
{
    this->type = _op.type;
}

IOperand & IOperand::operator=(const IOperand & _rhs)
{
    this->type = _rhs.type;
    return *this;
}