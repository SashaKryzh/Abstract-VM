
#include "AVM.hpp"

#include "OperandFactory.hpp"

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
		{"mod", &AVM::mod},
		{"print", &AVM::print},
		{"exit", &AVM::exit},
	};
}

AVM::~AVM()
{
	// TODO: free _ops
}

void AVM::executeTokens(std::vector<Token> tokens)
{
	_it = tokens.begin();
	while (_it != tokens.end() && !_exit)
	{
		if (_it->getType() != Token::Type::SEP)
		{
			try
			{
				(this->*_instrs.at(_it->getLexeme()))();
			}
			catch (const char *e)
			{
				std::cout << e << '\n';
				return;
			}
		}

		_it++;
	}

	if (_exit)
	{
		// TODO: Bosun: show unexecuted tokens
	}
	else
	{
		std::cout << "No exit instruction at the end" << std::endl;
	}
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
		throw "Pop on empty stack";
}

void AVM::dump()
{
	for (auto it = _ops.rbegin(); it != _ops.rend(); ++it)
	{
		std::cout << operandTypeNames[(*it)->getType()] << '(' << (*it)->toString() << ')' << std::endl;
	}
}

void AVM::assertt()
{
	const Token &valueToken = *(++_it);
	if (!_ops.empty())
	{
		if (_ops.back()->getType() != valueToken.getOType())
			throw "Wrong type";
		if (_ops.back()->toString() != valueToken.getOString())
			throw "Wrong value";
	}
	else
		throw "Stack is empty";
}

void AVM::add() { expression('+'); }
void AVM::sub() { expression('-'); }
void AVM::mul() { expression('*'); }
void AVM::div() { expression('/'); }
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
	}

	delete op1;
	delete op2;
}

void AVM::print()
{
	if (!_ops.empty())
	{
		if (_ops.back()->getType() == eOperandType::Int8)
		{
			int8_t value = std::stoi(_ops.back()->toString());
			std::cout << static_cast<char>(value) << std::endl;
		}
		else
			throw "Value is not an 8-bit integer";
	}
	else
		throw "Stack is empty";
}

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
		throw "Less that two values on stack";
}