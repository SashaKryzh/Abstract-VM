
#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
#include <vector>
#include <iostream>

#include "IOperand.hpp"
#include "Token.hpp"

#define COUNT_NO_VALUE_INSTRS 10
#define COUNT_WITH_VALUE_INSTRS 2

#define MAX_LEN_TOKEN 6

static const std::string instrNoValue[COUNT_NO_VALUE_INSTRS] = {"pop", "dump", "add", "sub",
																"mul", "div", "mod", "print", "exit"};
static const std::string instrWithValue[COUNT_WITH_VALUE_INSTRS] = {"push", "assert"};
static const std::string valueTypes[MaxOperandType] = {"int8", "int16", "int32", "float", "double"};

class Parser
{
public:
	Parser();
	~Parser();
	Parser(const Parser &) = delete;
	void operator=(const Parser &) = delete;

	void parseFile(std::string const &fileName);

private:
	std::vector<Token *> tokens;

	void _tokenize(std::string::iterator &it);
	Token *createToken(std::string tokenString);
};

#endif