#ifndef OPERAND_HPP
#define OPERAND_HPP

#include "IOperand.hpp"
#include "OperandFactory.hpp"

template <typename T>
class Operand : public IOperand
{
public:
	Operand(T value);
	~Operand(void);

	Operand(Operand const &) = delete;
	Operand &operator=(Operand const &) = delete;

	int getPrecision(void);
	eOperandType getType(void);

	IOperand const *operator+(IOperand const &rhs);
	IOperand const *operator-(IOperand const &rhs);
	IOperand const *operator*(IOperand const &rhs);
	IOperand const *operator/(IOperand const &rhs);
	IOperand const *operator%(IOperand const &rhs);

	std::string const &toString(void);

private:
	T _value;
};

template <typename T>
Operand<T>::Operand(T value) : _value(value) {}

template <typename T>
Operand<T>::~Operand() {}

template <typename T>
IOperand const Operand<T>::*operator+(IOperand const &rhs)
{
}

#endif