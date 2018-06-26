#include "Token.hpp"
#include <iostream>

// parse an integer token
int TokenInteger::parseToken(std::fstream &stream, int input_char)
{
    integer_string = input_char;
    if (input_char == '0')
    {
        input_char = stream.peek();
        if (input_char == 'X' || input_char == 'x')
        {
            integer_string += input_char;
            input_char = stream.get();
            while (true)
            {
                input_char = stream.get();
                if (isxdigit(input_char)){
                    integer_string += input_char;
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
            integer_string += input_char;
            continue;
        }
        return input_char;
    }
}

void TokenInteger::printToken() 
{
    std::cout << "TOKEN[\"integer\" , " << integer_string << "]" << std::endl;
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
    symbol = input_char;
    while (true)
    {
        input_char = stream.get();
        if (isalpha(input_char) || isdigit(input_char))
        {
            symbol += input_char;
            continue;
        }
        return input_char;
    }
}

void TokenInstruction::printToken()
{
    std::cout << "TOKEN[\"symbol , \"" << symbol<< "\"]" << std::endl;
} 

//============================================= PUNCTUATION ============================================ //
int TokenPunctuation::parseToken(std::fstream& stream, int input_char)
{
    punctuation_string = input_char;
    switch (input_char)
    {

    }
    input_char = stream.get();
    return input_char;
}

void TokenPunctuation::printToken()
{
    std::cout << "TOKEN[\"punctuation , \"" << punctuation_string<< "\"]" << std::endl;
}