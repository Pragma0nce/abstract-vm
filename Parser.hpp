#pragma once
#include "Token.hpp"
#include <list>
#include <stack>
#include "IOperand.hpp"
#include "IOperand.cpp"

class Parser
{
private: 
    std::stack<IOperand*> stack;  
public:
    void Parse(std::list<Token*> tokenList);
    void printStack();
};