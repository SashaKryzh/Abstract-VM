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
		
		for (auto &token : tokens)
		{
			std::cout << token.toString() << std::endl;
		}

		
	}

	return 0;
}
