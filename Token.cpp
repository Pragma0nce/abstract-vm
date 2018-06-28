#include "Token.hpp"
#include <iostream>

// parent class
std::string Token::getValue()
{
    return value;
}

TOKEN_TYPE Token::getType()
{
    return type;
}


// parse an integer token
int TokenInteger::parseToken(std::fstream &stream, int input_char)
{
    value = input_char;
    if (input_char == '0')
    {
        input_char = stream.peek();
        if (input_char == 'X' || input_char == 'x')
        {
            value += input_char;
            input_char = stream.get();
            while (true)
            {
                input_char = stream.get();
                if (isxdigit(input_char)){
                    value += input_char;
                    continue;
                }
                return input_char;
            }
        }
    }
    while (true)
    {
        input_char = stream.get();
        if (isxdigit(input_char)){
            value += input_char;
            continue;
        }
        return input_char;
    }
}

void TokenInteger::printToken() 
{
    std::cout << "TOKEN[\"integer\" , " << value << "]" << std::endl;
}

//============================================= WHITE SPACE ==================================================== //
int TokenSpace::parseToken(std::fstream& stream, int input_char)
{
    while (true)
    {
        input_char = stream.get();
        if (isspace(input_char)){
            continue;
        }
        return input_char;
    }
}
void TokenSpace::printToken()
{
     std::cout << "TOKEN[\"whitespace\" , \" \"]" << std::endl;
}

//===================================================== EOL =========================================== //
int TokenEOL::parseToken(std::fstream& stream, int input_char)
{
    while (true)
    {
        input_char = stream.get();
        return input_char;
    }
}

void TokenEOL::printToken()
{
    std::cout << "TOKEN[\"EOL\"]" << std::endl;
}

//===================================================== TOKEN =========================================== //

int TokenInstruction::parseToken(std::fstream& stream, int input_char)
{
    value = input_char;
    while (true)
    {
        input_char = stream.get();
        if (isalpha(input_char) || isdigit(input_char))
        {
            value += input_char;
            continue;
        }
        return input_char;
    }
}

void TokenInstruction::printToken()
{
    std::cout << "TOKEN[\"instruction , \"" << value << "\"]" << std::endl;
} 

//============================================= PUNCTUATION ============================================ //
int TokenPunctuation::parseToken(std::fstream& stream, int input_char)
{
    value = input_char;
    switch (input_char)
    {

    }
    input_char = stream.get();
    return input_char;
}

void TokenPunctuation::printToken()
{
    std::cout << "TOKEN[\"punctuation , \"" << value << "\"]" << std::endl;
}

//============================================= OPERAND ============================================ //
int TokenOperand::parseToken(std::fstream& stream, int input_char)
{

}

void TokenOperand::printToken()
{
    std::cout << "TOKEN[\"operand, \"" << value << "\"]" << std::endl;
}   