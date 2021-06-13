
#ifndef LEXER_HPP
#define LEXER_HPP

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

static const Token _ttt = Token();

class Lexer
{
public:
	Lexer();
	~Lexer();
	Lexer(const Lexer &) = delete;
	void operator=(const Lexer &) = delete;

	std::vector<Token> parseFile(std::string const &fileName);
	std::vector<Token> parseStandartInput();

private:
	enum ErrorType
	{
		UNKNOWN_TOKEN = 0,
		UNEXPECTED_END,
		UNEXPECTED_TOKEN,
		NEW_LINE_VALUE,
	};

	bool _isValid;
	std::vector<Token> tokens;

	Token createToken(std::string tokenString, size_t lineCount);

	void validate();
	bool checkToken(std::vector<Token>::iterator it, Token::Type expectedType);
	void displayError(ErrorType errorType, size_t line, Token const &token = _ttt, Token::Type expectedType = Token::Type::UNKNOWN);
};

#endif