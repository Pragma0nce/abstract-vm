#include "Parser.hpp"
#include <iostream>
#include <iterator>
#include "OperandFactory.hpp"
#include "IOperand.hpp"
#include <string>
#include "Exceptions.hpp"

std::string validWords[] = 
{
    "int8",
    "int16",
    "int32",
    "double",
    "float",
    "push",
    "pop",
    "dump",
    "mod",
    "add",
    "mul",
    "div",
    "exit",
    "assert",
    "print",
    "add",
    "sub"
};

Parser::Parser(std::stack<IOperand*> * _stack)
:stack(_stack)
{

}

bool Parser::isValidWord(std::list<Token*>::iterator &itt)
{
    for (auto i : validWords)
    {
        if (i == (*itt)->getValue())
        {
            return true;
        }
    }
    return false;
}

bool Parser::isValidInt(std::list<Token*>::iterator &itt)
{
        if ((*itt )->getValue() == "int32" || (*itt )->getValue() == "int8"
        || (*itt )->getValue() == "int16")
        {
            auto punct= std::next(itt, 1);
            if ((*punct)->getValue() == "(")
            {
                auto value = std::next(punct, 1);

                if ((*value)->getType() == TOKEN_TYPE::t_punctuation && (*value)->getValue() == "-")
                {
                    value = std::next(value, 1);
                    if ((*value)->getType() == TOKEN_TYPE::t_integer && (*std::next(value,1))->getValue() == ")")
                    {
                        if ((*std::next(value,2))->getType() != TOKEN_TYPE::t_eol)
                            throw ExceptionUnknownInstruction((*itt)->getValue() + " EOL expected after instruction");
                        return true;
                    }
                    else
                    {
                        
                        throw ExceptionUnknownInstruction((*itt)->getValue() + " expects an integer value followed by a ')'");
                        return false;
                    }
                }
                else  if ((*value)->getType() == TOKEN_TYPE::t_integer && (*std::next(value,1))->getValue() == ")")
                    {
                        if ((*std::next(value,2))->getType() != TOKEN_TYPE::t_eol)
                            throw ExceptionUnknownInstruction((*itt)->getValue() + " EOL expected after instruction");
                        return true;
                    }
                    else
                    {
                        throw ExceptionUnknownInstruction((*itt)->getValue() + " expects an integer value followed by a ')'");
                        return false;
                    }
            }
            else 
            {
                throw ExceptionUnknownInstruction((*itt)->getValue() + " should be followed by a '('");
                return false;
            }
        }
        else 
        {
            return false;
        }
}


bool Parser::isValidFloat(std::list<Token*>::iterator &itt)
{
    if ((*itt )->getValue() == "float" || (*itt )->getValue() == "double")
    {
        auto punct= std::next(itt, 1);
        if ((*punct)->getValue() == "(")
        {
            auto value = std::next(punct, 1);
            if ((*value)->getValue() == "-") 
            {
                value = std::next(value, 1);
                if ((*value)->getType() == TOKEN_TYPE::t_integer && ((*std::next(value,1))->getValue() == ")" 
                || ((*std::next(value,1))->getValue() == "." && (*std::next(value,2))->getType() == TOKEN_TYPE::t_integer && (*std::next(value,3))->getValue()==")")))
                {
                    return true;
                }
                else
                {
                    throw ExceptionUnknownInstruction((*itt)->getValue() + " expects a value.");
                    return false;
                }
            }
            else 
            {
                 if ((*value)->getType() == TOKEN_TYPE::t_integer && ((*std::next(value,1))->getValue() == ")" 
                || ((*std::next(value,1))->getValue() == "." && (*std::next(value,2))->getType() == TOKEN_TYPE::t_integer && (*std::next(value,3))->getValue()==")")))
                {
                    return true;
                }
                else
                {
                    throw ExceptionUnknownInstruction((*itt)->getValue() + " expects a value.");
                    return false;
                }               
            }
        }
        else 
        {
            throw ExceptionUnknownInstruction((*itt)->getValue() + " should be followed by a '('");
            return false;
        }
    }
    return false;
}



void Parser::printStack()
{
    auto stackCopy = stack;
    int i = 0;

    while (stackCopy->size() > 0)
    {
        auto ptr = stackCopy->top();

            std::cout << "STACK[" << i << "]" << ptr->toString() << std::endl; 
        stackCopy->pop();
        i++;
    }

}

// std::list<Token*>::iterator &nextToken(std::list<Token*>::iterator &it, int n)
// {

// }

std::string checkForNegative(std::list<Token*>::iterator &val)
{
    std::string result;
    result.clear();

    if ((*val)->getValue() == "-"){
        auto next = std::next(val,1);
        result += '-';
        result += (*next)->getValue();

    }
    else 
        result = (*val)->getValue();
    
    return result;
}

void Parser::Parse(std::list<Token*> tokenList)
{
    std::list<Token*>::iterator itt;
    OperandFactory opFactory;

try {
    for (itt = tokenList.begin(); itt != tokenList.end(); itt++)
    {
        if ((*itt)->getType() == TOKEN_TYPE::t_instruction)
        {
            if ((*itt)->getValue() == "push")
            {
                auto next = std::next(itt, 1);
                if ((*next)->getType() != TOKEN_TYPE::t_whitespace){
                    throw ExceptionUnknownInstruction("Push should be followed by whitespace");
                }

                auto instr = std::next(itt, 2);

                if (((*instr )->getType() == TOKEN_TYPE::t_instruction))
                {
                    if (isValidInt(instr))
                    {
                        auto value = std::next(instr, 2);
                        std::string strValue = checkForNegative(value);

                        IOperand const *op = NULL;

                        if ((*instr)->getValue() == "int8")
                            op  = opFactory.createOperand(eOperandType::t_int8, strValue);
                        else if ((*instr)->getValue() == "int16")
                            op  = opFactory.createOperand(eOperandType::t_int16, strValue);
                        else if ((*instr)->getValue() == "int32")
                            op  = opFactory.createOperand(eOperandType::t_int32, strValue);

                        stack->push(const_cast<IOperand*>(op));                        
                    }
                    else if (isValidFloat(instr))
                    {
                        IOperand const *op = NULL;
                        auto value = std::next(instr, 2);
                        std::string strValue = checkForNegative(value);
                        int offset = 0;

                        if (strValue[0] == '-'){
                            offset = 1;
                        }

                        if ((*instr)->getValue() == "float")
                        {
                            if ((*std::next(value, 1))->getValue() == ")")
                                op  = opFactory.createOperand(eOperandType::t_float, strValue);
                            else 
                                op = opFactory.createOperand(eOperandType::t_float, strValue + (*std::next(value,1 + offset))->getValue() + (*std::next(value,2 + offset))->getValue() );
                        }
                        else if ((*instr)->getValue() == "double")
                        {
                                if ((*std::next(value, 1))->getValue() == ")")
                                op  = opFactory.createOperand(eOperandType::t_double, strValue);
                            else 
                                op = opFactory.createOperand(eOperandType::t_double, strValue + (*std::next(value,1 + offset))->getValue() + (*std::next(value,2 + offset))->getValue() );                                   
                        }
                        stack->push(const_cast<IOperand*>(op));
                    }
                    else 
                    {
                        throw ExceptionUnknownInstruction("You are trying to push an operand that does not exist");
                    }
                }    
                else 
                {
                    throw ExceptionUnknownInstruction("Push should be followed by operator");
                }
            }
            else if ((*itt)->getValue() == "add")
            {
                auto next = std::next(itt, 1);
                if ((*next)->getType() != TOKEN_TYPE::t_eol){
                    throw ExceptionUnknownInstruction("add should be followed by an EOL");
                }

                if (stack->size() >= 2)
                {
                    auto val1 = stack->top();
                    stack->pop();
                    auto val2 = stack->top();
                    stack->pop();

                    auto result = *val1 + *val2;
                    stack->push(const_cast<IOperand*>(result));
                }
                else 
                {
                    throw ExceptionUnknownInstruction("add instruction requires 2 values on the stack");
                }
            }
            else if ((*itt)->getValue() == "sub")
            {
                auto next = std::next(itt, 1);
                if ((*next)->getType() != TOKEN_TYPE::t_eol){
                    throw ExceptionUnknownInstruction("sub should be followed by an EOL");
                }

                 if (stack->size() >= 2)
                {
                    auto val1 = stack->top();
                    stack->pop();
                    auto val2 = stack->top();
                    stack->pop();

                    auto result = *val1 - *val2;
                    stack->push(const_cast<IOperand*>(result));
                }
                else 
                {
                    throw ExceptionUnknownInstruction("sub instruction requires 2 values on the stack");
                }               
            }
            else if ((*itt)->getValue() == "mul")
            {
                auto next = std::next(itt, 1);
                if ((*next)->getType() != TOKEN_TYPE::t_eol){
                    throw ExceptionUnknownInstruction("mul should be followed by an EOL");
                }
                if (stack->size() >= 2)
                {
                    auto val1 = stack->top();
                    stack->pop();
                    auto val2 = stack->top();
                    stack->pop();

                    auto result = *val1 * *val2;
                    stack->push(const_cast<IOperand*>(result));
                }
                else 
                {
                    throw ExceptionUnknownInstruction("mul instruction requires 2 values on the stack");
                }              
            }
            else if ((*itt)->getValue() == "div")
            {
                auto next = std::next(itt, 1);
                if ((*next)->getType() != TOKEN_TYPE::t_eol){
                    throw ExceptionUnknownInstruction("div should be followed by an EOL");
                }

                if (stack->size() >= 2)
                {
                    auto val1 = stack->top();
                    stack->pop();
                    auto val2 = stack->top();
                    stack->pop();

                    auto result = *val2 / *val1;
                    stack->push(const_cast<IOperand*>(result));
                }
                else 
                {
                    throw ExceptionUnknownInstruction("div instruction requires 2 values on the stack");
                }                  
            }
            else if ((*itt)->getValue() == "mod")
            {
                auto next = std::next(itt, 1);
                if ((*next)->getType() != TOKEN_TYPE::t_eol){
                    throw ExceptionUnknownInstruction("mod should be followed by an EOL");
                }

                if (stack->size() >= 2)
                {
                    auto val1 = stack->top();
                    stack->pop();
                    auto val2 = stack->top();
                    stack->pop();

                    auto result = *val1 % *val2;
                    stack->push(const_cast<IOperand*>(result));
                }
                else 
                {
                    throw ExceptionUnknownInstruction("mod instruction requires 2 values on the stack");
                }                  
            }
            else if ((*itt)->getValue() == "dump")
            {
                auto next = std::next(itt, 1);
                if ((*next)->getType() != TOKEN_TYPE::t_eol){
                    throw ExceptionUnknownInstruction("dump should be followed by an EOL");
                }
                printStack();
            }
            else if ((*itt)->getValue() == "pop")
            {
                auto next = std::next(itt, 1);
                if ((*next)->getType() != TOKEN_TYPE::t_eol){
                    throw ExceptionUnknownInstruction("pop should be followed by an EOL");
                }

                if (stack->empty()){
                    throw ExceptionPopOnEmptyStack();
                }

                stack->pop();
            }
            else if ((*itt)->getValue() == "print")
            {
                auto val1 = stack->top();
                if (val1->getType() == eOperandType::t_int8){
                    std::cout << char(std::stoi(val1->toString()));
                }
                else 
                {
                    throw ExceptionUnknownInstruction("print instruction requires an int8 value");
                }
            }
            else if ((*itt)->getValue() == "assert")
            {
                auto type = std::next(itt, 2);
                if (isValidInt(type) || isValidFloat(type))
                {
                    IOperand const *op;
                    op = NULL;

                    if (isValidInt(type)){
                        auto value = std::next(type, 2);
                        std::string strValue = checkForNegative(value);

                        if ((*type)->getValue() == "int8")
                            op  = opFactory.createOperand(eOperandType::t_int8, strValue);
                        else if ((*type)->getValue() == "int16")
                            op  = opFactory.createOperand(eOperandType::t_int16, strValue);
                        else if ((*type)->getValue() == "int32")
                            op  = opFactory.createOperand(eOperandType::t_int32, strValue);
                    }
                    else if (isValidFloat(type))
                    {
                        auto value = std::next(type, 2);
                        std::string strValue = checkForNegative(value);
                        int offset = 0;

                        if (strValue[0] == '-'){
                            offset = 1;
                        }

                        if ((*type)->getValue() == "float")
                        {
                            if ((*std::next(value, 1))->getValue() == ")")
                                op  = opFactory.createOperand(eOperandType::t_float, strValue);
                            else 
                                op = opFactory.createOperand(eOperandType::t_float, strValue + (*std::next(value,1 + offset))->getValue() + (*std::next(value,2 + offset))->getValue() );
                        }
                        else if ((*type)->getValue() == "double")
                        {
                                if ((*std::next(value, 1))->getValue() == ")")
                                op  = opFactory.createOperand(eOperandType::t_double, strValue);
                            else 
                                op = opFactory.createOperand(eOperandType::t_double, strValue + (*std::next(value,1 + offset))->getValue() + (*std::next(value,2 + offset))->getValue() );                                   
                        }                        
                    }

                    auto val1 = stack->top();
                    // PDF is unclear if operand type should be checked, if this is the case use this:
                    // if (op->toString() != val1->toString()|| op->getType() != val1->getType())
                    if (op->toString() != val1->toString())
                    {
                        throw ExceptionUnknownInstruction("Assertion failed");
                    }
                }
                else 
                {
                    throw ExceptionUnknownInstruction("assert command requires a type specifier");
                }
            }
            else if (!isValidWord(itt))
            {
                std::cout << (*itt)->getValue() << std::endl;
                 throw ExceptionUnknownInstruction("Invalid instruction");
            }
        }
    }
}
catch (ExceptionUnknownInstruction &e)
{
    std::cout << "Exception raised: "<< e.what() << std::endl;
}
catch (std::exception &e)
{
    std::cout << "Exception raised: "<< e.what() << std::endl;
}
}

Parser  & Parser::operator=(const Parser & _rhs)
{
    stack = _rhs.stack;
    return (*this);
}

Parser::Parser (const Parser  & _op)
{
    stack = _op.stack;
}

Parser::Parser()
{

}

Parser::~Parser()
{

}