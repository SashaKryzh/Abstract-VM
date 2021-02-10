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
			++count;
			std::cout << "[" << count << "]" << line << std::endl;
		}
		file.close();
	}
	else
	{
		std::cout << "error opening file" << std::endl;
	}
}