#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>

#include "IOperand.hpp"

enum TokenTypes
{
	INSTR_NO_VALUE,
	INSTR_WITH_VALUE,
	VALUE,
	SEP,
};

class Token
{
public:
	Token();
	Token(TokenTypes type, std::string string);
	Token(TokenTypes type, std::string string, eOperandType oType);

	TokenTypes tokenType;
	eOperandType operandType;
	std::string string;

	std::string const toString(void);
};

#endif