#pragma once
#include <fstream>
#include <list>

class Token;

class TokenLexer 
{
private:
    std::fstream *sourceStream;
    std::list<Token*> tokenList;

protected:
public:
    TokenLexer (const TokenLexer  & _op);
    TokenLexer  & operator=(const TokenLexer & _rhs);
    TokenLexer ();
    TokenLexer(std::fstream* stream);

    bool parseTokens();
    void printTokens();

    std::list<Token*> *getTokenList();
    ~TokenLexer();
};
