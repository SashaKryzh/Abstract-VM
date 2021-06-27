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
	AVM operator=(AVM const &) = delete;
	AVM(AVM &&) = delete;
	AVM &operator=(AVM &&) = delete;

	void executeFull(std::vector<Token> &tokens);
	void execute(std::vector<Token> &tokens);

	bool isExit();

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
	void div2();
	void mod();
	void print();
	void min(); // Bonus
	void max(); // Bonus
	void exit();

	std::map<std::string, void (AVM::*)()> _instrs;

	void expression(const char op);
	void minmax(bool isMax);

	// Utils
	void assertMoreThanOne();

	bool _exit;
};

static AVM gAvm;

#endif