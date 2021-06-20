#ifndef OPERAND_HPP
#define OPERAND_HPP

#include <sstream>

#include "IOperand.hpp"
#include "OperandFactory.hpp"

template <typename T>
class Operand : public IOperand
{
public:
	Operand(eOperandType type, std::string valueString);
	~Operand(void);

	Operand(Operand const &) = delete;
	Operand &operator=(Operand const &) = delete;

	int getPrecision(void) const;
	eOperandType getType(void) const;

	IOperand const *operator+(IOperand const &rhs) const;
	IOperand const *operator-(IOperand const &rhs) const;
	IOperand const *operator*(IOperand const &rhs) const;
	IOperand const *operator/(IOperand const &rhs) const;
	IOperand const *operator%(IOperand const &rhs) const;

	std::string const &toString(void) const;

private:
	T _value;
	eOperandType _type;
	std::string _valueString;
};

template <typename T>
Operand<T>::Operand(eOperandType type, std::string valueString) : _type(type), _valueString(valueString)
{
}

template <typename T>
Operand<T>::~Operand() {}

template <typename T>
eOperandType Operand<T>::getType() const
{
	return _type;
}

template <typename T>
int Operand<T>::getPrecision() const
{
	// TODO: implement
	return -1;
}

template <typename T>
IOperand const *Operand<T>::operator+(IOperand const &rhs) const
{
	// TODO: implement
	return gOperandFactory.createOperand(eOperandType::MaxOperandType, "");
}

template <typename T>
IOperand const *Operand<T>::operator-(IOperand const &rhs) const
{
	// TODO: implement
	return gOperandFactory.createOperand(eOperandType::MaxOperandType, "");
}

template <typename T>
IOperand const *Operand<T>::operator*(IOperand const &rhs) const
{
	// TODO: implement
	return gOperandFactory.createOperand(eOperandType::MaxOperandType, "");
}

template <typename T>
IOperand const *Operand<T>::operator/(IOperand const &rhs) const
{
	// TODO: implement
	return gOperandFactory.createOperand(eOperandType::MaxOperandType, "");
}

template <typename T>
IOperand const *Operand<T>::operator%(IOperand const &rhs) const
{
	// TODO: implement
	return gOperandFactory.createOperand(eOperandType::MaxOperandType, "");
}

template <typename T>
std::string const &Operand<T>::toString() const
{
	return _valueString;
}

#endif