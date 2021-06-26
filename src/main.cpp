#include <iostream>

#include "abstract.hpp"
#include "Parser.hpp"
#include "OperandFactory.hpp"
#include "AVM.hpp"

void playMode()
{
	try
	{
		while (true)
		{
			auto tokens = gParser.parseStandartInputLine();
			if (!tokens.empty())
				gAvm.execute(tokens);
			if (!gParser.isOk() || gAvm.isExit())
				break;
		}
	}
	catch (const std::exception &e)
	{
		std::cout << "Runtime error : " << e.what() << std::endl;
	}
}

void regularMode(int ac, char *av[])
{
	try
	{
		auto tokens = ac ? gParser.parseFile(*av) : gParser.parseStandartInput();
		if (!tokens.empty())
			gAvm.executeFull(tokens);
	}
	catch (const std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
}

int main(int ac, char *av[])
{
	--ac;
	++av;

	if (ac && std::string(*av) == "-p")
		playMode();
	else
		regularMode(ac, av);

	return 0;
}
