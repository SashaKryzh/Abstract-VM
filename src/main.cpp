#include "Parser.hpp"
#include "OperandFactory.hpp"

int main(int ac, char *av[])
{
	--ac;
	++av;

	Parser p;

	if (ac)
	{
		p.parseFile(*av);
	}

	OperandFactory f;
	f.createOperand(Int8, "5");
	f.createOperand(Int8, "4235324");

	return 0;
}
