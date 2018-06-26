#pragma once
#include <fstream>
#include <list>

class Token;

class TokenParser 
{
private:
    std::fstream& sourceStream;
    std::list<Token*> tokenList;
public:
    TokenParser(std::fstream& stream);

    bool parseTokens();
    void printTokens();
};
