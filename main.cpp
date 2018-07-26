#include <iostream>
#include "Lexer.hpp"
#include "Token.hpp"
#include "Parser.hpp"
using namespace std;

int startParsingFile(std::string filename, std::stack<IOperand*> &stack)
{
    // open the file
    std::fstream source;

    source.open(filename.c_str(), ios_base::in);
    if (source.fail()){
        std::cout << "An error has occurred while opening the file" << std::endl;
        return (0);
    }

    // Create the token list
    TokenLexer lexer(source);
    lexer.parseTokens();
    //lexer.printTokens();

    Parser parser(stack);
    parser.Parse(*lexer.getTokenList());
    return (0);
}

int readFromInput(std::stack<IOperand*> &stack)
{
    std::string input;
    std::ofstream tempFile;

    tempFile.open("temp.file");
    for(;;)
    {
        std::getline(std::cin, input);
        if (input == "exit")
        {
            break;
        }

        if (input == ";;")
        {
            break;
        }

        if (tempFile.is_open())
        {
            tempFile << input << std::endl;
        }
        else std::cout << "Unable to create temporary file" << std::endl;
    }
    tempFile.close();
    startParsingFile("temp.file", stack);

    return (0);
}

int main(int argc, char *argv[])
{
    std::stack<IOperand*> stack; 

    if (argc < 2){
        readFromInput(stack);
        return (0);
    }

    std::string filename = argv[argc - 1];
    startParsingFile(filename, stack);

    // parser.printStack();;;
    return (0);
}