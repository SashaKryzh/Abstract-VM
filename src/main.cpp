#include <iostream>

#include "abstract.hpp"
#include "Lexer.hpp"
#include "OperandFactory.hpp"

int main(int ac, char *av[])
{
	--ac;
	++av;

	Lexer p;

	if (ac)
	{
		auto tokens = p.parseFile(*av);
		utils::printTokens(tokens);
	}

	return 0;
}
