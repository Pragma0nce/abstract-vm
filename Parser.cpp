#include "Parser.hpp"
#include <iostream>
#include <iterator>
#include "OperandFactory.cpp"

void Parser::printStack()
{
    // auto stackCopy = stack;
    // int i = 0;

    // while (stackCopy.size() > 0)
    // {
    //     auto ptr = dynamic_cast<Operand<char>*>(stackCopy.top());

    //         std::cout << "STACK[" << i << "]" << (int)ptr->getValue().int8 << std::endl; 
    //     stackCopy.pop();
    //     i++;
    // }
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
                    if ((*instr )->getValue() == "int32" || (*instr )->getValue() == "int8"
                    || (*instr )->getValue() == "int16")
                    {
                        auto punct= std::next(instr, 1);
                        if ((*punct)->getValue() == "(")
                        {
                            auto value = std::next(punct, 1);


                            if ((*value)->getType() == TOKEN_TYPE::t_integer && (*std::next(value,1))->getValue() == ")")
                            {
                                IOperand const *op  = opFactory.createOperand(eOperandType::t_int8, (*value)->getValue());
                                stack.push(const_cast<IOperand*>(op));
                            }
                            else
                            {
                                std::cout << "Exception: '" << (*instr)->getValue() << "' expects an integer value" << std::endl;
                            }
                        }
                        else 
                        {
                            std::cout << "Exception: '" << (*instr)->getValue() << "' should be followed by a '('" << std::endl;
                        }
                    }
                    else if ((*instr )->getValue() == "float" || (*instr )->getValue() == "double")
                    {
                        std::cout << "Float or double" << std::endl;
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

                    /*OperandInt8 *intVal1;
                    OperandInt8 *intVal2;

                    if (val1->getType() == eOperandType::t_int8)
                        intVal1 = dynamic_cast<OperandInt8*>(val1);
                    if (val2->getType() == eOperandType::t_int8)
                        intVal2 = dynamic_cast<OperandInt8*>(val2);
                     
                    OperandInt8 *op = new OperandInt8();
                    std::cout << "Sum result: " << int(intVal1->getValue() + intVal2->getValue()) << std::endl;*/
                }
                else 
                {
                    std::cout << "Exception: stack needs atleast 2 values" << std::endl;
                }
            }
        }
    }
}