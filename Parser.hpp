#pragma once
#include "Token.hpp"
#include <list>
#include <stack>

class IOperand;

class Parser
{
private: 

    std::stack<IOperand*> stack;  

    bool isValidWord(std::list<Token*>::iterator &itt);
public:
    void Parse(std::list<Token*> tokenList);

    void printStack();
    bool assert(std::list<Token*>::iterator &itt);

    bool isValidInt(std::list<Token*>::iterator &itt);
    bool isValidFloat(std::list<Token*>::iterator &itt);

};