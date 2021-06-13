
#include "abstract.hpp"

void utils::printTokens(std::vector<Token> tokens)
{
	for (auto const &token : tokens)
	{
		if (token.getType() == Token::Type::SEP)
			continue;
		std::cout << "[" << token.getLine() << "] " << token.toString() << std::endl;
	}
}