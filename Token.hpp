#pragma once
#include <fstream>
#include <string>

enum TOKEN_TYPE {
    t_invalid_token,
    t_symbol,
    t_integer,
    t_integer_16,
    t_literal,
    t_comment,
    t_punctuation,
    t_instruction,
    t_whitespace,
    t_eof,
    t_eol
};

class Token 
{
private: 
    TOKEN_TYPE type;
public: 
    Token(TOKEN_TYPE token) : type(token){};

    virtual int parseToken(std::fstream& stream, int input_char) = 0;
    virtual void printToken() = 0;
};

class TokenInteger : public Token 
{
private:
    std::string integer_string;
public:
    TokenInteger() : Token(t_integer) { };
    int parseToken(std::fstream& stream, int input_char);
    void printToken();
};

class TokenSpace : public Token 
{
public: 
    TokenSpace() : Token(t_whitespace) {};
    int parseToken(std::fstream& stream, int input_char);
    void printToken();
};

class TokenEOL : public Token 
{
public: 
    TokenEOL() : Token(t_eol) {};
    int parseToken(std::fstream& stream, int input_char);
    void printToken();
};

class TokenPunctuation : public Token 
{
private:
    std::string punctuation_string;
public:
    TokenPunctuation() : Token(t_punctuation) {};
    int parseToken(std::fstream& stream, int input_char);
    void printToken();    
};

class TokenInstruction : public Token 
{
private:
    std::string symbol;
public:
    TokenInstruction() : Token(t_instruction) {};
    int parseToken(std::fstream& stream, int input_char);
    void printToken();    
};