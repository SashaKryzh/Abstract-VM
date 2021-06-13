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
		UNKNOWN,
	};

	Token();
	Token(Type type, std::string string, eOperandType oType, size_t lineCount);
	~Token();

	// TODO: make private
	Type type;
	std::string string;
	eOperandType oType;
	size_t lineCount;

	std::string const toString(void);
};

static const std::string tokenTypeStrings[Token::Type::UNKNOWN + 1] = {
	"INSTR WITHOUT VALUE",
	"INSTR WITH VALUE",
	"VALUE",
	"SEP",
	"UNKNOWN",
};

#endif