#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
#include <vector>
#include <iostream>

#include "IOperand.hpp"
#include "Token.hpp"

#define COUNT_NO_VALUE_INSTRS 12
#define COUNT_WITH_VALUE_INSTRS 2

static const std::string instrNoValue[COUNT_NO_VALUE_INSTRS] = {"pop", "dump", "add", "sub", "mul",
																"div", "div2", "mod", "print", "min", "max", "exit"};
static const std::string instrWithValue[COUNT_WITH_VALUE_INSTRS] = {"push", "assert"};

// To use as default value in displayError function
static const Token _defaultToken;

class Parser
{
public:
	Parser();
	~Parser();

	Parser(const Parser &) = delete;
	Parser operator=(const Parser &) = delete;
	Parser(Parser &&) = delete;
	Parser &operator=(Parser &&) = delete;

	std::vector<Token> parseFile(std::string const &fileName);
	std::vector<Token> parseStandartInput();
	std::vector<Token> parseStandartInputLine();

	bool isOk() const;

private:
	bool _isValid;
	std::vector<Token> _tokens;

	bool _isOk;
	bool _exitBeforeError;

	void parseLine(std::string const &, size_t lineCount);
	Token createToken(std::string tokenString, size_t lineCount);

	void validate();
	bool checkToken(std::vector<Token>::iterator it, Token::Type expectedType);
	void goToNextLine(std::vector<Token>::iterator &it);
};

static Parser gParser;

#endif