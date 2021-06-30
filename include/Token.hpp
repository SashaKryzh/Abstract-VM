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
	
	Token(const Token &);
	Token(Token &&);
	Token &operator=(Token &&);

	Token operator=(const Token &) = delete;

	Type getType() const;
	std::string const &getLexeme() const;
	eOperandType getOType() const;
	std::string getOString() const;
	size_t getLine() const;

	std::string const toString(void) const;

private:
	Type type;
	std::string lexeme;
	eOperandType oType;
	size_t line;
};

static const std::string tokenTypeStrings[Token::Type::UNKNOWN + 1] = {
	"INSTR",
	"INSTR WITH VALUE",
	"VALUE",
	"SEP",
	"UNKNOWN",
};

#endif