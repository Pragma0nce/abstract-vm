#include "Parser.hpp"
#include <iostream>
#include <iterator>

void Parser::Parse(std::list<Token*> tokenList)
{
    std::list<Token*>::iterator itt;

    for (itt = tokenList.begin(); itt != tokenList.end(); itt++)
    {
        if ((*itt)->getType() == TOKEN_TYPE::t_instruction)
        {
            if ((*itt)->getValue() == "push")
            {
                auto next = std::next(itt, 2);
                if (((*next)->getType() == TOKEN_TYPE::t_instruction))
                {
                    if ((*next)->getValue() == "int32" || (*next)->getValue() == "int8"
                    || (*next)->getValue() == "int16" || (*next)->getValue() == "float" || (*next)->getValue() == "double")
                    {
                        OperandInt op;
                    }
                    else 
                    {
                        std::cout << "Exception: You are trying to push an illegal operand" << std::endl;
                    }
                }    
            }
        }
    }
}