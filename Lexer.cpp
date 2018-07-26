#include "Lexer.hpp"
#include "Token.hpp"
#include <iostream>

TokenLexer::TokenLexer(std::fstream &stream)
:sourceStream(stream)
{

}

bool TokenLexer::parseTokens()
{
    Token *token;

    while (!sourceStream.eof())
    {
        int input_char = sourceStream.get();
        while (!sourceStream.eof())
        {
            do 
            {
                // remove comments from the file
                if (input_char == ';')
                {
                    int peek_character = sourceStream.peek();
                    while (peek_character != 0x0A && !sourceStream.eof()){
                        peek_character = sourceStream.get();
                    }
                    token = new TokenEOL;
                    break;
                }
                if (isdigit(input_char))
                {
                    token = new TokenInteger;
                    break;
                }
                if (input_char == 0x0A   || input_char =='\0')
                {
                    token = new TokenEOL;
                    break;
                }
                if (input_char == ' ' || input_char == '\t')
                {
                    token = new TokenSpace;
                    break;
                }
                if (isalpha(input_char))
                {
                    token = new TokenInstruction;
                    break;
                }
                if (ispunct(input_char))
                {
                    token = new TokenPunctuation();
                    break;
                }
            }
            while (false);
            if (token == NULL) return false;
            input_char = token->parseToken(sourceStream, input_char);

            // Push the token to the list
            tokenList.push_back(token);
            continue ;
        }
    }

    // Add the EOF token to the end of the list TODO
    return true;
}

void TokenLexer::printTokens()
{
    for (auto i : tokenList)
    {
        i->printToken();
    }
}

std::list<Token*> *TokenLexer::getTokenList()
{
    return &tokenList;
}