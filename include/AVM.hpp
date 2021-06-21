#ifndef AVM_HPP
#define AVM_HPP

#include <vector>
#include <stack>
#include <map>

#include "Token.hpp"
#include "IOperand.hpp"

class AVM
{
public:
	AVM();
	~AVM();
	AVM(AVM const &) = delete;
	void operator=(AVM const &) = delete;

	void executeTokens(std::vector<Token> tokens);

private:
	std::vector<const IOperand *> _ops;
	std::vector<Token>::iterator _it;

	// Instructions
	void push();
	void pop();
	void dump();
	void assertt();
	void add();
	void sub();
	void mul();
	void div();
	void mod();
	void print();
	void exit();

	std::map<std::string, void (AVM::*)()> _instrs;

	void expression(const char op);

	// Utils
	void assertMoreThanOne();

	bool _exit;
};

#endif