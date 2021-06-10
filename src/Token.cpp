
#include <sstream>

#include "Token.hpp"

Token::Token() : type(Token::Type::UNKNOWN), string(""), oType(eOperandType::MaxOperandType) {}
Token::Token(Type type, std::string string, eOperandType oType) : type(type), string(string), oType(oType) {}
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
	ss << names[static_cast<int>(type)] << " "
	   << operandTypeNames[static_cast<int>(oType)] << " "
	   << string;
	return ss.str();
}