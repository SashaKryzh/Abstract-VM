
#include "AVM.hpp"

#include <fstream>

#include "OperandFactory.hpp"
#include "AvmException.hpp"

AVM::AVM() : _exit(false)
{
	_instrs = {
		{"push", &AVM::push},
		{"pop", &AVM::pop},
		{"dump", &AVM::dump},
		{"assert", &AVM::assertt},
		{"add", &AVM::add},
		{"sub", &AVM::sub},
		{"mul", &AVM::mul},
		{"div", &AVM::div},
		{"div2", &AVM::div2},
		{"mod", &AVM::mod},
		{"print", &AVM::print},
		{"min", &AVM::min},
		{"max", &AVM::max},
		{"exit", &AVM::exit},
	};
}

AVM::~AVM()
{
	for (auto op : _ops)
		delete op;
	_ops.clear();
}

void AVM::executeFull(std::vector<Token> &tokens)
{
	try
	{
		execute(tokens);
		if (_exit)
		{
			while (_it != tokens.end() && _it->getType() == Token::Type::SEP)
				_it++;
			if (_it != tokens.end())
			{
				std::cout << "\nUnexecuted tokens:" << std::endl;
				while (_it != tokens.end())
				{
					if (_it->getType() != Token::Type::SEP)
						std::cout << _it->toString() << std::endl;
					_it++;
				}
			}
		}
		else
		{
			std::cout << "No exit instruction at the end" << std::endl;
		}
	}
	catch (const std::exception &e)
	{
		std::cout << "Line " << std::setw(3) << std::left << _it->getLine()
				  << " : Runtime error : " << e.what() << std::endl;
	}
}

void AVM::execute(std::vector<Token> &tokens)
{
	_it = tokens.begin();
	while (_it != tokens.end() && !_exit)
	{
		if (_it->getType() != Token::Type::SEP)
			(this->*_instrs.at(_it->getLexeme()))();
		_it++;
	}
}

bool AVM::isExit()
{
	return _exit;
}

//
// Instructions
//

void AVM::push()
{
	const Token &valueToken = *(++_it);
	_ops.push_back(gOperandFactory.createOperand(valueToken.getOType(), valueToken.getOString()));
}

void AVM::pop()
{
	if (!_ops.empty())
		_ops.pop_back();
	else
		throw InstructionException("Pop on empty stack");
}

void AVM::dump()
{
	if (!_ops.empty())
	{
		for (auto it = _ops.rbegin(); it != _ops.rend(); ++it)
		{
			std::cout << operandTypeNames[(*it)->getType()] << '(' << (*it)->toString() << ')' << std::endl;
		}
	}
	else
		std::cout << "Empty" << std::endl;
}

void AVM::assertt()
{
	const Token &valueToken = *(++_it);
	if (!_ops.empty())
	{
		if (_ops.back()->getType() != valueToken.getOType())
			throw InstructionException("Wrong type in assert");
		if (_ops.back()->toString() != valueToken.getOString())
			throw InstructionException("Wrong value in assert");
	}
	else
		throw InstructionException("Assert on empty stack");
}

void AVM::add() { expression('+'); }
void AVM::sub() { expression('-'); }
void AVM::mul() { expression('*'); }
void AVM::div() { expression('/'); }
void AVM::div2() { expression('2'); }
void AVM::mod() { expression('%'); }

void AVM::expression(const char op)
{
	assertMoreThanOne();
	IOperand const *op1 = _ops.back();
	_ops.pop_back();
	IOperand const *op2 = _ops.back();
	_ops.pop_back();

	switch (op)
	{
	case '+':
		_ops.push_back(*op2 + *op1);
		break;
	case '-':
		_ops.push_back(*op2 - *op1);
		break;
	case '*':
		_ops.push_back(*op2 * *op1);
		break;
	case '/':
		_ops.push_back(*op2 / *op1);
		break;
	case '%':
		_ops.push_back(*op2 % *op1);
		break;
	case '2':
		_ops.push_back(op2->div2(*op1));
		break;
	}

	delete op1;
	delete op2;
}

void AVM::print()
{
	if (!_ops.empty())
	{
		if (_ops.back()->getType() == eOperandType::Int8)
			std::cout << static_cast<int8_t>(std::stoi(_ops.back()->toString())) << std::endl;
		else
			throw InstructionException("Value is not an 8-bit integer");
	}
	else
		throw InstructionException("Print on empty stack");
}

void AVM::minmax(bool isMax)
{
	if (!_ops.empty())
	{
		IOperand const *m = *(_ops.begin());
		for (auto it = _ops.begin(); it != _ops.end(); ++it)
		{
			double vM = std::stod(m->toString());
			double vI = std::stod((*it)->toString());
			if (isMax)
			{
				if (vM < vI)
					m = *it;
			}
			else
			{
				if (vI < vM)
					m = *it;
			}
		}
		std::cout << operandTypeNames[m->getType()] << '(' << m->toString() << ')' << std::endl;
	}
	else
		std::cout << "Empty" << std::endl;
}

void AVM::min() { minmax(false); }
void AVM::max() { minmax(true); }

void AVM::exit()
{
	_exit = true;
}

//
// Utils
//

void AVM::assertMoreThanOne()
{
	if (_ops.size() > 1 == false)
		throw InstructionException("Less than two values on stack");
}