SRC = Exceptions.cpp IOperand.cpp Lexer.cpp main.cpp Operand.cpp OperandFactory.cpp Parser.cpp Token.cpp
OUT = vm
FLAGS = -Wall -Werror -Wextra -std=c++11
COMP = g++

all:
	$(COMP) $(SRC) -o $(OUT) $(FLAGS)

clean:
	rm -rf $(OUT) custom.avm

fclean:	clean

re: fclean
	make all