#include "Parser.hpp"
#include <iostream>
#include <iterator>
#include "OperandFactory.hpp"
#include "IOperand.hpp"
#include <string>

bool Parser::isValidInt(std::list<Token*>::iterator &itt)
{
    if ((*itt )->getValue() == "int32" || (*itt )->getValue() == "int8"
    || (*itt )->getValue() == "int16")
    {
        auto punct= std::next(itt, 1);
        if ((*punct)->getValue() == "(")
        {
            auto value = std::next(punct, 1);

            if ((*value)->getType() == TOKEN_TYPE::t_integer && (*std::next(value,1))->getValue() == ")")
            {
                return true;
            }
            else
            {
                std::cout << "Exception: '" << (*itt)->getValue() << "' expects an integer value" << std::endl;
                return false;
            }
        }
        else 
        {
            std::cout << "Exception: '" << (*itt)->getValue() << "' should be followed by a '('" << std::endl;
            return false;
        }
    }

    return false;
}

bool Parser::isValidFloat(std::list<Token*>::iterator &itt)
{
    if ((*itt )->getValue() == "float" || (*itt )->getValue() == "double")
    {
        auto punct= std::next(itt, 1);
        if ((*punct)->getValue() == "(")
        {
            auto value = std::next(punct, 1);


            if ((*value)->getType() == TOKEN_TYPE::t_integer && ((*std::next(value,1))->getValue() == ")" 
            || ((*std::next(value,1))->getValue() == "." && (*std::next(value,2))->getType() == TOKEN_TYPE::t_integer && (*std::next(value,3))->getValue()==")")))
            {
                return true;
            }
            else
            {
                std::cout << "Exception: '" << (*itt)->getValue() << "' expects an integer value" << std::endl;
                return false;
            }
        }
        else 
        {
            std::cout << "Exception: '" << (*itt)->getValue() << "' should be followed by a '('" << std::endl;
            return false;
        }
    }
    return false;
}

void Parser::printStack()
{
    auto stackCopy = stack;
    int i = 0;

    while (stackCopy.size() > 0)
    {
        auto ptr = stackCopy.top();

            std::cout << "STACK[" << i << "]" << ptr->toString() << std::endl; 
        stackCopy.pop();
        i++;
    }

}

void Parser::Parse(std::list<Token*> tokenList)
{
    std::list<Token*>::iterator itt;
    OperandFactory opFactory;

    for (itt = tokenList.begin(); itt != tokenList.end(); itt++)
    {
        if ((*itt)->getType() == TOKEN_TYPE::t_instruction)
        {
            if ((*itt)->getValue() == "push")
            {
                auto instr = std::next(itt, 2);
                if (((*instr )->getType() == TOKEN_TYPE::t_instruction))
                {
                    if (isValidInt(instr))
                    {
                        auto value = std::next(instr, 2);
                        IOperand const *op;

                        if ((*instr)->getValue() == "int8")
                            op  = opFactory.createOperand(eOperandType::t_int8, (*value)->getValue());
                        else if ((*instr)->getValue() == "int16")
                            op  = opFactory.createOperand(eOperandType::t_int16, (*value)->getValue());
                        else if ((*instr)->getValue() == "int32")
                            op  = opFactory.createOperand(eOperandType::t_int32, (*value)->getValue());

                        stack.push(const_cast<IOperand*>(op));                        
                    }
                    else if (isValidFloat(instr))
                    {
                        IOperand const *op;
                        auto value = std::next(instr, 2);
                        if ((*instr)->getValue() == "float")
                        {
                            if ((*std::next(value, 1))->getValue() == ")")
                                op  = opFactory.createOperand(eOperandType::t_float, (*value)->getValue());
                            else 
                                op = opFactory.createOperand(eOperandType::t_float, (*value)->getValue() + (*std::next(value,1))->getValue() + (*std::next(value,2))->getValue() );
                        }
                        else if ((*instr)->getValue() == "double")
                        {
                                if ((*std::next(value, 1))->getValue() == ")")
                                op  = opFactory.createOperand(eOperandType::t_double, (*value)->getValue());
                            else 
                                op = opFactory.createOperand(eOperandType::t_double, (*value)->getValue() + (*std::next(value,1))->getValue() + (*std::next(value,2))->getValue() );                                   
                        }
                        stack.push(const_cast<IOperand*>(op));
                    }
                    else 
                    {
                        std::cout << "You are trying to push an operand that does not exist" << std::endl;
                    }
                }    
            }
            else if ((*itt)->getValue() == "add")
            {
                if (stack.size() >= 2)
                {
                    auto val1 = stack.top();
                    stack.pop();
                    auto val2 = stack.top();
                    stack.pop();

                    auto result = *val1 + *val2;
                    stack.push(const_cast<IOperand*>(result));
                }
                else 
                {
                    std::cout << "Exception: stack needs atleast 2 values" << std::endl;
                }
            }
            else if ((*itt)->getValue() == "sub")
            {
                 if (stack.size() >= 2)
                {
                    auto val1 = stack.top();
                    stack.pop();
                    auto val2 = stack.top();
                    stack.pop();

                    auto result = *val1 - *val2;
                    stack.push(const_cast<IOperand*>(result));
                }
                else 
                {
                    std::cout << "Exception: stack needs atleast 2 values" << std::endl;
                }               
            }
            else if ((*itt)->getValue() == "mul")
            {
                if (stack.size() >= 2)
                {
                    auto val1 = stack.top();
                    stack.pop();
                    auto val2 = stack.top();
                    stack.pop();

                    auto result = *val1 * *val2;
                    stack.push(const_cast<IOperand*>(result));
                }
                else 
                {
                    std::cout << "Exception: stack needs atleast 2 values" << std::endl;
                }              
            }
            else if ((*itt)->getValue() == "div")
            {
                if (stack.size() >= 2)
                {
                    auto val1 = stack.top();
                    stack.pop();
                    auto val2 = stack.top();
                    stack.pop();

                    auto result = *val1 / *val2;
                    stack.push(const_cast<IOperand*>(result));
                }
                else 
                {
                    std::cout << "Exception: stack needs atleast 2 values" << std::endl;
                }                  
            }
            else if ((*itt)->getValue() == "dump")
            {
                printStack();
            }
            else if ((*itt)->getValue() == "pop")
            {
                stack.pop();
            }
            else if ((*itt)->getValue() == "assert")
            {
                auto type = std::next(itt, 2);
                if (isValidInt(type) || isValidFloat(type))
                {
                    IOperand const *op;
                    if (isValidInt(type)){
                        auto value = std::next(type, 2);

                        if ((*type)->getValue() == "int8")
                            op  = opFactory.createOperand(eOperandType::t_int8, (*value)->getValue());
                        else if ((*type)->getValue() == "int16")
                            op  = opFactory.createOperand(eOperandType::t_int16, (*value)->getValue());
                        else if ((*type)->getValue() == "int32")
                            op  = opFactory.createOperand(eOperandType::t_int32, (*value)->getValue());
                    }
                    else if (isValidFloat(type))
                    {
                        std::cout << "Got here: " << (*type)->getValue() << std::endl;
                        auto value = std::next(type, 2);
                        if ((*type)->getValue() == "float")
                        {
                            if ((*std::next(value, 1))->getValue() == ")")
                                op  = opFactory.createOperand(eOperandType::t_float, (*value)->getValue());
                            else 
                                op = opFactory.createOperand(eOperandType::t_float, (*value)->getValue() + (*std::next(value,1))->getValue() + (*std::next(value,2))->getValue() );
                        }
                        else if ((*type)->getValue() == "double")
                        {
                                if ((*std::next(value, 1))->getValue() == ")")
                                op  = opFactory.createOperand(eOperandType::t_double, (*value)->getValue());
                            else 
                                op = opFactory.createOperand(eOperandType::t_double, (*value)->getValue() + (*std::next(value,1))->getValue() + (*std::next(value,2))->getValue() );                                   
                        }                        
                    }

                    auto val1 = stack.top();
                    if (op->toString() == val1->toString())
                    {
                        std::cout << "match" << std::endl;
                    }
                    std::cout << "assertion" << std::endl;
                }
                else 
                {
                    std::cout << "Exception: Assert requires a type specifier" << std::endl;
                }
            }
        }
    }
}