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

	return 0;
}
