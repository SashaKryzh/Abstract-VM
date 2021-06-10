#ifndef PARSER_HPP
#define PARSER_HPP

#include <vector>

#include "IOperand.hpp"
#include "Token.hpp"

class Parser
{
public:
	Parser() {};

	void parseTokens(std::vector<Token> tokens)
	{
		auto it = tokens.begin();
		while (it != tokens.end())
		{
			while (it->type == Token::Type::SEP)
				it++;

			switch (it->type)
			{
			case Token::Type::INSTR_NO_VALUE:
				parseInstrNoValue(it);
			case Token::Type::INSTR_WITH_VALUE:
				parseInstrWithValue(it);
			default:
				throw "Unexpected token";
			}
		}
		std::cout << "OK" << std::endl;
	};

	void parseInstrNoValue(std::vector<Token>::iterator &it)
	{
		it++;
		if (it->type != Token::Type::SEP)
			throw "No seperator after instr";
	}

	void parseInstrWithValue(std::vector<Token>::iterator &it)
	{
		it++;
		if (it->type != Token::Type::VALUE)
			throw "No value after instr with value";
		parseValue(it);
	}

	void parseValue(std::vector<Token>::iterator &it)
	{
		it++;
		if (it->type != Token::Type::SEP)
			throw "No seperator after value";
	}
};

#endif