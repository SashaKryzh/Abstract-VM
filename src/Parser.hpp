
#ifndef PARSER_HPP
#define PARSER_HPP

#include <iostream>

class Parser
{
public:
	Parser();
	~Parser();
	Parser(const Parser &) = delete;
	void operator=(const Parser &) = delete;

	void parseFile(std::string const &fileName);
};

#endif