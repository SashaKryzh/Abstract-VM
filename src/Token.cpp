
#include <sstream>

#include "Token.hpp"

Token::Token() {}
Token::Token(Type type, std::string string) : type(type), string(string), oType(eOperandType::MaxOperandType) {}
Token::Token(Type type, std::string string, eOperandType oType) : type(type), string(string), oType(oType) {}

std::string const Token::toString(void)
{
	static const char *const names[]{
		"INSTR_NO_VALUE",
		"INSTR_WITH_VALUE",
		"VALUE",
		"SEP",
	};
	std::ostringstream ss;
	ss << names[static_cast<int>(type)] << " "
	   << operandTypeNames[static_cast<int>(oType)] << " "
	   << string;
	return ss.str();
}