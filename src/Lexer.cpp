#include "Lexer.hpp"
#include <fstream>

Lexer::Lexer() {}
Lexer::~Lexer() {}

std::vector<Token> Lexer::parseFile(std::string const &fileName)
{
	std::ifstream file(fileName);
	if (file.is_open())
	{
		std::string line;

		size_t count = 0;

		while (std::getline(file, line))
		{
			for (auto it = line.begin(); it != line.end(); ++it)
			{
				if (isspace(*it))
					continue;
				else if (*it == ';')
					break;
				else
				{
					std::string::iterator start = it;
					while (it != line.end() && !isspace(*it))
						it++;
					std::string tokenString = std::string(start, it);

					try
					{
						tokens.push_back(createToken(tokenString));
					}
					catch (const std::exception &e)
					{
						std::cerr << e.what() << '\n';
					}

					if (it == line.end())
						break;
				}
			}
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

Token Lexer::createToken(std::string tokenString)
{
	int parPos;
	if ((parPos = tokenString.find('(')) != std::string::npos && tokenString.back() == ')')
	{
		std::string typeString = tokenString.substr(0, parPos);
		for (int i = 0; i < eOperandType::MaxOperandType; ++i)
		{
			if (operandTypeNames[i] == typeString)
				return Token(Token::Type::VALUE, tokenString, (eOperandType)i);
		}
	}
	else
	{
		for (int i = 0; i < COUNT_NO_VALUE_INSTRS; ++i)
		{
			if (instrNoValue[i] == tokenString)
				return Token(Token::Type::INSTR_NO_VALUE, tokenString);
		}

		for (int i = 0; i < COUNT_WITH_VALUE_INSTRS; ++i)
		{
			if (instrWithValue[i] == tokenString)
				return Token(Token::Type::INSTR_WITH_VALUE, tokenString);
		}
	}

	throw "Unexpected";
}