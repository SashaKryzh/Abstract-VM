#include "Token.hpp"

#include <sstream>
#include <fstream>

Token::Token() : type(Token::Type::UNKNOWN), lexeme(""), oType(eOperandType::MaxOperandType), line(0) {}
Token::Token(Type type, std::string string, eOperandType oType, size_t lineCount)
	: type(type), lexeme(string), oType(oType), line(lineCount) {}
Token::~Token() {}

Token::Token(Token const &rhs)
{
	type = rhs.type;
	lexeme = rhs.lexeme;
	oType = rhs.oType;
	line = rhs.line;
}

Token::Token(Token &&rhs)
{
	type = rhs.type;
	lexeme = rhs.lexeme;
	oType = rhs.oType;
	line = rhs.line;
}

Token &Token::operator=(Token &&rhs)
{
	type = rhs.type;
	lexeme = rhs.lexeme;
	oType = rhs.oType;
	line = rhs.line;
	return *this;
}

Token::Type Token::getType() const
{
	return type;
}

std::string const &Token::getLexeme() const
{
	return lexeme;
}

eOperandType Token::getOType() const
{
	return oType;
}

std::string Token::getOString() const
{
	if (type == Type::VALUE)
	{
		auto str = lexeme.substr(lexeme.find('(') + 1);
		str.pop_back();
		return str;
	}
	else
		return "";
}

size_t Token::getLine() const
{
	return line;
}

std::string const Token::toString(void) const
{
	static const char *const names[]{
		"INSTR_NO_VALUE",
		"INSTR_WITH_VALUE",
		"VALUE",
		"SEP",
		"UNKNOWN",
	};
	std::ostringstream ss;
	ss << std::setw(16) << std::left << names[type] << " : ";
	if (type == Type::VALUE)
		ss << operandTypeNames[oType] << "(" << getOString() << ")";
	else
		ss << lexeme;
	return ss.str();
}