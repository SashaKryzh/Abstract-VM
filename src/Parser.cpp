#include "Parser.hpp"
#include <fstream>

Parser::Parser() {}
Parser::~Parser() {}

void Parser::parseFile(std::string const &fileName)
{
	std::ifstream file(fileName);
	if (file.is_open())
	{
		std::string line;
		size_t count = 0;

		while (std::getline(file, line))
		{
			for (std::string::iterator it = line.begin(); it != line.end(); ++it)
			{
				if (isspace(*it))
					continue;
				else if (*it == ';')
					break;
				else
				{
					bool openParentasisEncounted = false;
					std::string::iterator start = it;
					while (it != line.end() && !isspace(*it))
					{
						if (*it == '(')
							openParentasisEncounted = true;
						it++;
					}
					std::string tokenString = std::string(start, it);
					Token *token = NULL;
					if ((token = createToken(tokenString)) != NULL)
						tokens.push_back(token);
					else
						std::cout << "Unexpected" << std::endl;

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

	for (std::vector<Token *>::iterator it = tokens.begin(); it != tokens.end(); ++it)
	{
		std::cout << (*it)->toString() << std::endl;
	}
}

Token *Parser::createToken(std::string tokenString)
{
	int parPos;
	if ((parPos = tokenString.find('(')) != std::string::npos)
	{
		if (tokenString.back() != ')')
			return NULL;
		std::string typeString = tokenString.substr(0, parPos);
		for (int i = 0; i < MaxOperandType; ++i)
		{
			if (valueTypes[i] == typeString)
			{
				return new Token(VALUE, tokenString, (eOperandType)i);
			}
		}
	}

	for (int i = 0; i < COUNT_NO_VALUE_INSTRS; ++i)
	{
		if (instrNoValue[i] == tokenString)
		{
			return new Token(INSTR_NO_VALUE, tokenString);
		}
	}

	for (int i = 0; i < COUNT_WITH_VALUE_INSTRS; ++i)
	{
		if (instrWithValue[i] == tokenString)
		{
			return new Token(INSTR_WITH_VALUE, tokenString);
		}
	}

	return NULL;
}

void Parser::_tokenize(std::string::iterator &it)
{
	// size_t tokenLen = 0;
	// while
}