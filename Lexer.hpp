#pragma once
#include <fstream>
#include <list>

class Token;

class TokenLexer 
{
private:
    std::fstream& sourceStream;
    std::list<Token*> tokenList;
public:
    TokenLexer(std::fstream& stream);

    bool parseTokens();
    void printTokens();

    std::list<Token*> *getTokenList();
};
