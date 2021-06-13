#ifndef ABSTRACT_HPP
#define ABSTRACT_HPP

#include <iostream>
#include <vector>

#include "Token.hpp"

namespace utils
{
	void printTokens(std::vector<Token> tokens);
	std::string trim(const std::string &s);
}

#endif