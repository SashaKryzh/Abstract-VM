#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>

#include "IOperand.hpp"

class Token
{
public:
	enum Type
	{
		INSTR_NO_VALUE = 0,
		INSTR_WITH_VALUE,
		VALUE,
		SEP,
	};

	Token();
	Token(Type type, std::string string);
	Token(Type type, std::string string, eOperandType oType);

	Type type;
	std::string string;
	eOperandType oType;

	std::string const toString(void);
};

#endif