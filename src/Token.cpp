
#include <sstream>

#include "Token.hpp"

Token::Token() : type(Token::Type::UNKNOWN), string(""), oType(eOperandType::MaxOperandType), lineCount(0) {}
Token::Token(Type type, std::string string, eOperandType oType, size_t lineCount)
	: type(type), string(string), oType(oType), lineCount(lineCount) {}
Token::~Token() {}

std::string const Token::toString(void)
{
	static const char *const names[]{
		"INSTR_NO_VALUE",
		"INSTR_WITH_VALUE",
		"VALUE",
		"SEP",
		"UNKNOWN",
	};
	std::ostringstream ss;
	ss << names[static_cast<int>(type)] << "(";
	if (type == Type::VALUE)
		ss << "[" << operandTypeNames[static_cast<int>(oType)] << "]";
	ss << string << ")";
	return ss.str();
}