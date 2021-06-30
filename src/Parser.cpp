#include "Parser.hpp"

#include <fstream>
#include <regex>
#include <algorithm>

#include "abstract.hpp"

Parser::Parser() : _isValid(true), _isOk(true), _exitBeforeError(false) {}
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
	if (_isValid || _exitBeforeError)
		return tokensWithoutSep();
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
	if (_isValid || _exitBeforeError)
		return tokensWithoutSep();
	else
		return {};
}

std::vector<Token> Parser::parseStandartInputLine()
{
	_isValid = true;
	_exitBeforeError = false;
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
	if (_isValid || _exitBeforeError)
		return tokensWithoutSep();
	else
		return {};
}

std::vector<Token> Parser::tokensWithoutSep()
{
	auto newEnd = std::remove_if(
		_tokens.begin(), _tokens.end(),
		[](Token &t)
		{
			return t.getType() == Token::Type::SEP;
		});
	_tokens.erase(newEnd, _tokens.end());
	return _tokens;
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

void Parser::validate()
{
	if (!_isValid)
		return;

	auto it = _tokens.begin();
	while (it != _tokens.end())
	{
		auto firstInLine = it;

		switch (it->getType())
		{
		case Token::Type::INSTR_NO_VALUE:
			checkToken(++it, Token::Type::SEP);
			if (it != _tokens.end())
				goToNextLine(++it);
			break;

		case Token::Type::INSTR_WITH_VALUE:
			if (checkToken(++it, Token::Type::VALUE))
				checkToken(++it, Token::Type::SEP);
			if (it != _tokens.end())
				goToNextLine(++it);
			break;

		case Token::Type::VALUE:
			std::cout << NewLineValue(it->getLine()).what() << std::endl;
			_isValid = false;
			goToNextLine(++it);
			break;

		case Token::Type::SEP:
			it++;
			break;

		case Token::Type::UNKNOWN:
			std::cout << UnknownToken(it->getLine(), it->getLexeme()).what() << std::endl;
			_isValid = false;
			goToNextLine(++it);
			break;
		}

		if (_isValid && firstInLine->getLexeme() == "exit")
			_exitBeforeError = true;
	}
}

bool Parser::checkToken(std::vector<Token>::iterator it, Token::Type expectedType)
{
	try
	{
		if (it == _tokens.end())
		{
			if (expectedType != Token::Type::SEP)
				throw UnexpectedEnd((--it)->getLine());
		}
		else if (it->getType() == Token::Type::UNKNOWN)
			throw UnknownToken(it->getLine(), it->getLexeme());
		else if (it->getType() != expectedType)
			throw UnexpectedToken(it->getLine(), it->getType(), expectedType);
	}
	catch (std::exception const &e)
	{
		_isValid = false;
		std::cout << e.what() << std::endl;
		return false;
	}
	return true;
}

void Parser::goToNextLine(std::vector<Token>::iterator &it)
{
	while (it != _tokens.end() && it->getType() != Token::Type::SEP)
	{
		try
		{
			if (it->getType() == Token::Type::UNKNOWN)
				throw UnknownToken(it->getLine(), it->getLexeme());
		}
		catch (std::exception const &e)
		{
			_isValid = false;
			std::cout << e.what() << std::endl;
		}
		it++;
	}
}