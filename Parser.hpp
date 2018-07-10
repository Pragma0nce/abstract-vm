#pragma once
#include "Token.hpp"
#include <list>
#include <stack>

class IOperand;

class Parser
{
private: 
    std::stack<IOperand*> stack;  
public:
    void Parse(std::list<Token*> tokenList);
    void printStack();

    bool isValidInt(std::list<Token*>::iterator itt);
    bool isValidFloat(std::list<Token*>::iterator itt);
};