#include "Lexer.hpp"
#include <fstream>
#include <regex>

Lexer::Lexer() : _isValid(true) {}
Lexer::~Lexer() {}

std::vector<Token> Lexer::parseFile(std::string const &fileName)
{
	std::ifstream file(fileName);
	if (file.is_open())
	{
		std::string line;
		size_t lineCount = 1;
		while (std::getline(file, line))
		{
			auto it = line.begin();
			while (it != line.end())
			{
				if (*it == ';')
					break;
				else if (isspace(*it))
					it++;
				else
				{
					auto tokenStart = it;
					while (it != line.end() && !isspace(*it))
						it++;
					std::string tokenString = std::string(tokenStart, it);
					tokens.push_back(createToken(tokenString, lineCount));
				}
			}
			if (!file.eof())
				tokens.push_back(Token(Token::Type::SEP, "", eOperandType::MaxOperandType, lineCount));
			lineCount++;
		}
		file.close();
	}
	else
	{
		// TODO: Exception
		std::cout << "error opening file" << std::endl;
	}

	validate();
	return tokens;
}

std::vector<Token> Lexer::parseStandartInput()
{
	return tokens;
}

Token Lexer::createToken(std::string tokenString, size_t lineCount)
{
	Token::Type type = Token::Type::UNKNOWN;
	eOperandType oType = eOperandType::MaxOperandType;

	static const std::regex value(R"(((int8|int16|int32)\([-]?[0-9]+\))|((float|double)\([-]?[0-9]+\.[0-9]+\)))");
	if (std::regex_match(tokenString, value))
	{
		std::string typeString = tokenString.substr(0, tokenString.find('('));
		for (int i = 0; i < eOperandType::MaxOperandType; ++i)
		{
			if (operandTypeNames[i] == typeString)
			{
				type = Token::Type::VALUE;
				oType = static_cast<eOperandType>(i);
			}
		}
	}

	for (int i = 0; i < COUNT_NO_VALUE_INSTRS; ++i)
	{
		if (instrNoValue[i] == tokenString)
			type = Token::Type::INSTR_NO_VALUE;
	}

	for (int i = 0; i < COUNT_WITH_VALUE_INSTRS; ++i)
	{
		if (instrWithValue[i] == tokenString)
			type = Token::Type::INSTR_WITH_VALUE;
	}

	return Token(type, tokenString, oType, lineCount);
}

// Checks for tokens.end(), UNKNOWN, != expectedType
bool Lexer::checkToken(std::vector<Token>::iterator it, Token::Type expectedType)
{
	if (it == tokens.end())
	{
		displayError(ErrorType::UNEXPECTED_END, (--it)->lineCount);
		return false;
	}
	else if (it->type == Token::Type::UNKNOWN)
	{
		// Displays error in validate() function
		return false;
	}
	else if (it->type != expectedType)
	{
		displayError(ErrorType::UNEXPECTED_TOKEN, it->lineCount, *it, expectedType);
		return false;
	}
	return true;
}

void Lexer::validate()
{
	auto it = tokens.begin();
	while (it != tokens.end())
	{
		switch (it->type)
		{
		case Token::Type::INSTR_NO_VALUE:
			if (it->string == "exit")
				it++;
			else
				checkToken(++it, Token::Type::SEP);
			break;

		case Token::Type::INSTR_WITH_VALUE:
			if (checkToken(++it, Token::Type::VALUE))
				checkToken(++it, Token::Type::SEP);
			break;

		case Token::Type::VALUE:
			displayError(ErrorType::NEW_LINE_VALUE, it->lineCount);
			it++;
			break;

		case Token::Type::SEP:
			it++;
			break;

		case Token::Type::UNKNOWN:
			displayError(ErrorType::UNKNOWN_TOKEN, it->lineCount);
			while (it != tokens.end() && it->type != Token::Type::SEP)
				it++;
			break;
		}
	}
}

void Lexer::displayError(ErrorType errorType, size_t line, Token const &token, Token::Type expectedType)
{
	_isValid = false;
	switch (errorType)
	{
	case ErrorType::UNKNOWN_TOKEN:
		std::cout << "Lexical error : Unknown token " << token.string << " at line " << line << std::endl;
		break;

	case ErrorType::UNEXPECTED_END:
		std::cout << "Syntatic error : Unexpected end of tokens at line " << line << std::endl;
		break;

	case ErrorType::UNEXPECTED_TOKEN:
		std::cout << "Syntatic error : Got " << tokenTypeStrings[token.type]
				  << " while expected " << tokenTypeStrings[expectedType] << " at line " << line << std::endl;
		break;

	case ErrorType::NEW_LINE_VALUE:
		std::cout << "Syntatic error : Got VALUE while expected INSTR "
				  << " at line " << line << std::endl;
		break;
	}
}