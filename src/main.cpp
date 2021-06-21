#include <iostream>

#include "abstract.hpp"
#include "Parser.hpp"
#include "OperandFactory.hpp"
#include "AVM.hpp"

int main(int ac, char *av[])
{
	--ac;
	++av;

	Parser p;
	AVM avm;

	auto tokens = ac ? p.parseFile(*av) : p.parseStandartInput();
	// utils::printTokens(tokens);
	if (!tokens.empty())
		avm.executeTokens(tokens);

	return 0;
}
