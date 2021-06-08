
#include <sstream>

#include "Token.hpp"

Token::Token() {}
Token::Token(TokenTypes type, std::string string) : tokenType(type), string(string) {}
Token::Token(TokenTypes type, std::string string, eOperandType oType) : tokenType(type), string(string), operandType(oType) {}

std::string const Token::toString(void)
{
	std::ostringstream ss;
	ss << tokenType << " " << operandType << " " << string;
	return ss.str();
}