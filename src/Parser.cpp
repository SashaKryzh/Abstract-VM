#include "Parser.hpp"

#include <fstream>
#include <regex>

#include "abstract.hpp"

Parser::Parser() : _isValid(true), _isOk(true) {}
Parser::~Parser() {}

std::vector<Token> Parser::parseFile(std::string const &fileName)
{
	std::ifstream file(fileName);
	if (file.is_open())
	{
		std::string line;
		size_t lineCount = 1;
		while (std::getline(file, line))
		{
			parseLine(line, lineCount);
			if (!file.eof())
				_tokens.push_back(Token(Token::Type::SEP, "", eOperandType::MaxOperandType, lineCount));
			lineCount++;
		}
		file.close();
	}
	else
	{
		_isValid = false;
		std::cout << "Error while opening a file" << std::endl;
	}

	validate();
	if (_isValid)
		return _tokens;
	else
		return {};
}

std::vector<Token> Parser::parseStandartInput()
{
	std::string line;
	size_t lineCount = 1;
	while (true)
	{
		std::getline(std::cin, line);
		if (std::cin.bad() || std::cin.eof() || std::cin.fail())
		{
			std::cout << "Error while reading from the standart input" << std::endl;
			_isValid = false;
			break;
		}
		else
		{
			if (utils::trim(line) == ";;")
				break;
			parseLine(line, lineCount);
			_tokens.push_back(Token(Token::Type::SEP, "", eOperandType::MaxOperandType, lineCount));
			lineCount++;
		}
	}

	validate();
	if (_isValid)
		return _tokens;
	else
		return {};
}

std::vector<Token> Parser::parseStandartInputLine()
{
	_isValid = true;
	_tokens.clear();

	std::string line;
	std::getline(std::cin, line);
	if (std::cin.bad() || std::cin.eof() || std::cin.fail())
	{
		std::cout << "Error while reading from the standart input" << std::endl;
		_isOk = false;
		return {};
	}

	parseLine(line, 0);
	validate();
	if (_isValid)
		return _tokens;
	else
		return {};
}

bool Parser::isOk() const
{
	return _isOk;
}

void Parser::parseLine(std::string const &line, size_t lineCount)
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
			_tokens.push_back(createToken(std::string(tokenStart, it), lineCount));
		}
	}
}

Token Parser::createToken(std::string const tokenString, size_t lineCount)
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

// TODO: rewrite (errors in screenshots)
void Parser::validate()
{
	if (!_isValid)
		return;

	auto it = _tokens.begin();
	while (it != _tokens.end())
	{
		switch (it->getType())
		{
		case Token::Type::INSTR_NO_VALUE:
			checkToken(++it, Token::Type::SEP);
			break;

		case Token::Type::INSTR_WITH_VALUE:
			if ((!checkToken(++it, Token::Type::VALUE) || !checkToken(++it, Token::Type::SEP)) &&
				it->getType() != Token::Type::SEP && it != _tokens.end())
				goToNextLine(++it);
			break;
		case Token::Type::VALUE:
			displayError(ErrorType::NEW_LINE_VALUE, it->getLine());
			goToNextLine(++it);
			break;

		case Token::Type::SEP:
			it++;
			break;

		case Token::Type::UNKNOWN:
			displayError(ErrorType::UNKNOWN_TOKEN, it->getLine(), *it);
			goToNextLine(++it);
			break;
		}
	}
}

void Parser::goToNextLine(std::vector<Token>::iterator &it)
{
	while (it != _tokens.end() && it->getType() != Token::Type::SEP)
	{
		if (it->getType() == Token::Type::UNKNOWN)
			displayError(ErrorType::UNKNOWN_TOKEN, it->getLine(), *it);
		it++;
	}
}

// Checks for tokens.end(), != expectedType
bool Parser::checkToken(std::vector<Token>::iterator it, Token::Type expectedType)
{
	if (it == _tokens.end())
	{
		// It is possible to have end if the SEP required
		if (expectedType != Token::Type::SEP)
		{
			displayError(ErrorType::UNEXPECTED_END, (--it)->getLine());
			return false;
		}
		else
			return true;
	}
	else if (it->getType() == Token::Type::UNKNOWN)
	{
		displayError(ErrorType::UNKNOWN_TOKEN, it->getLine(), *it);
		return false;
	}
	else if (it->getType() != expectedType)
	{
		displayError(ErrorType::UNEXPECTED_TOKEN, it->getLine(), *it, expectedType);
		return false;
	}
	return true;
}

void Parser::displayError(ErrorType errorType, size_t line, Token const &token, Token::Type expectedType)
{
	_isValid = false;
	if (line != 0)
		std::cout << "Line " << std::setw(3) << std::left << line << " : ";
	switch (errorType)
	{
	case ErrorType::UNKNOWN_TOKEN:
		std::cout << "Lexical error  : Unknown token : " << token.getLexeme() << std::endl;
		break;

	case ErrorType::UNEXPECTED_END:
		std::cout << "Syntatic error : Unexpected end of tokens" << std::endl;
		break;

	case ErrorType::UNEXPECTED_TOKEN:
		std::cout << "Syntatic error : Got " << tokenTypeStrings[token.getType()]
				  << " while expected " << tokenTypeStrings[expectedType] << std::endl;
		break;

	case ErrorType::NEW_LINE_VALUE:
		std::cout << "Syntatic error : Got VALUE while expected INSTR or INSTR WITH VALUE " << std::endl;
		break;
	}
}