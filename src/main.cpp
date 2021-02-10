#include "Parser.hpp"

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
