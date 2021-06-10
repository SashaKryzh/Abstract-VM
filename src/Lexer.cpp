#include "Lexer.hpp"
#include <fstream>
#include <regex>

Lexer::Lexer() {}
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