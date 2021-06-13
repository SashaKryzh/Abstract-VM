
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

std::string utils::trim(const std::string &s)
{
    auto start = s.begin();
    while (start != s.end() && std::isspace(*start)) {
        start++;
    }
 
    auto end = s.end();
    do {
        end--;
    } while (std::distance(start, end) > 0 && std::isspace(*end));
 
    return std::string(start, end + 1);
}