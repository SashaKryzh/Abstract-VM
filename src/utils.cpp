
#include "abstract.hpp"

void utils::printTokens(std::vector<Token> tokens)
{
	for (auto &token : tokens)
	{
		std::cout << token.toString() << std::endl;
	}
}