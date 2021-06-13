
#include "abstract.hpp"

void utils::printTokens(std::vector<Token> tokens)
{
	for (auto &token : tokens)
	{
		if (token.type == Token::Type::SEP)
			continue;
		std::cout << "[" << token.lineCount << "] " << token.toString() << std::endl;
	}
}