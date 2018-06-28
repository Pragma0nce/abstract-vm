#include <iostream>
#include "Lexer.hpp"
#include "Token.hpp"
#include "Parser.hpp"
using namespace std;

int main(int argc, char *argv[])
{
    if (argc < 2){
        std::cout << "Invalid command line arguments" << std::endl;
        return (0);
    }

    std::string filename = argv[argc - 1];
    std::fstream source;

    // open the file
    source.open(filename.c_str(), ios_base::in);
    if (source.fail()){
        std::cout << "An error has occurred while opening the file" << std::endl;
        return (0);
    }

    // Create the token list
    TokenLexer lexer(source);
    lexer.parseTokens();
    lexer.printTokens();

    Parser parser;
    parser.Parse(*lexer.getTokenList());
}