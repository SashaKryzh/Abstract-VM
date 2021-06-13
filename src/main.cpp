#include <iostream>

#include "abstract.hpp"
#include "Parser.hpp"
#include "OperandFactory.hpp"

int main(int ac, char *av[])
{
	--ac;
	++av;

	Parser p;

	if (ac)
	{
		auto tokens = p.parseFile(*av);
		utils::printTokens(tokens);
	}
	else
	{
		auto tokens = p.parseStandartInput();
		utils::printTokens(tokens);
	}

	return 0;
}
