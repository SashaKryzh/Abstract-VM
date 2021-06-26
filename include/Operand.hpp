#ifndef OPERAND_HPP
#define OPERAND_HPP

#include <sstream>

#include "IOperand.hpp"
#include "OperandFactory.hpp"
#include "AvmException.hpp"

template <typename T>
class Operand : public IOperand
{
public:
	Operand(eOperandType type, std::string valueString);
	~Operand(void);

	Operand(Operand const &) = delete;
	Operand &operator=(Operand const &) = delete;
	Operand(Operand &&) = delete;
	Operand &operator=(Operand &&) = delete;

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

	IOperand const *operators(char const op, IOperand const &rhs) const;
	bool willNewValueOverflowType(long double const newValue, eOperandType const newType) const;
};

template <typename T>
Operand<T>::Operand(eOperandType type, std::string valueString) : _type(type), _valueString(valueString)
{
	try
	{
		long double ld = std::stold(valueString);
		if (willNewValueOverflowType(ld, type))
			throw std::out_of_range("");
		_value = static_cast<T>(ld);
	}
	catch (std::out_of_range &)
	{
		throw OperandException("Overflow");
	}
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
	return static_cast<int>(_type);
}

template <typename T>
IOperand const *Operand<T>::operators(char const op, IOperand const &rhs) const
{
	eOperandType newType = std::max(_type, rhs.getType());

	long double value = std::stold(this->toString());
	long double rhsValue = std::stold(rhs.toString());
	long double newValue = 0;

	switch (op)
	{
	case '+':
		newValue = value + rhsValue;
		break;

	case '-':
		newValue = value - rhsValue;
		break;

	case '*':
		newValue = value * rhsValue;
		break;

	case '/':
		if (rhsValue == 0)
			throw OperandException("Division by zero");
		newValue = value / rhsValue;
		break;

	case '%':
		if (_type >= eOperandType::Float || rhs.getType() >= eOperandType::Float)
			throw OperandException("Floating-point operand during modulo");
		if (rhsValue == 0)
			throw OperandException("Modulo by zero");
		newValue = static_cast<int32_t>(value) % static_cast<int32_t>(rhsValue);
		break;
	}

	if (willNewValueOverflowType(newValue, newType))
		throw OperandException("Overflow");

	auto str = newType >= eOperandType::Float ? std::to_string(newValue) : std::to_string(static_cast<int32_t>(newValue));
	return gOperandFactory.createOperand(newType, str);
}

template <typename T>
bool Operand<T>::willNewValueOverflowType(long double const newValue, eOperandType const newType) const
{
	switch (newType)
	{
	case eOperandType::Int8:
		return newValue < INT8_MIN || newValue > INT8_MAX;
	case eOperandType::Int16:
		return newValue < INT16_MIN || newValue > INT16_MAX;
	case eOperandType::Int32:
		return newValue < INT32_MIN || newValue > INT32_MAX;
	case eOperandType::Float:
		return newValue < -__FLT_MAX__ || newValue > __FLT_MAX__;
	case eOperandType::Double:
		return newValue < -__DBL_MAX__ || newValue > __DBL_MAX__;
	default:
		return true;
	}
}

template <typename T>
IOperand const *Operand<T>::operator+(IOperand const &rhs) const { return operators('+', rhs); }
template <typename T>
IOperand const *Operand<T>::operator-(IOperand const &rhs) const { return operators('-', rhs); }
template <typename T>
IOperand const *Operand<T>::operator*(IOperand const &rhs) const { return operators('*', rhs); }
template <typename T>
IOperand const *Operand<T>::operator/(IOperand const &rhs) const { return operators('/', rhs); }
template <typename T>
IOperand const *Operand<T>::operator%(IOperand const &rhs) const { return operators('%', rhs); }

template <typename T>
std::string const &Operand<T>::toString() const { return _valueString; }

#endif