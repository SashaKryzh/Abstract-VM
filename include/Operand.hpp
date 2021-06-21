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

	IOperand const *operators(char const op, IOperand const &rhs) const;
};

// TODO: Is this the best way to check for overflow?
template <typename T>
Operand<T>::Operand(eOperandType type, std::string valueString) : _type(type)
{
	std::istringstream iss(valueString);
	iss >> _value;

	std::ostringstream ss;
	ss << _value;
	_valueString = ss.str();
}

template <typename T>
Operand<T>::~Operand() {}

template <typename T>
eOperandType Operand<T>::getType() const
{
	return _type;
}

// TODO: Is the implementation correct?
template <typename T>
int Operand<T>::getPrecision() const
{
	return static_cast<int>(_type);
}

// TODO: Is the implementation correct?
static bool willNewValueOverflowType(long double const newValue, eOperandType const newType)
{
	int64_t int64 = static_cast<int64_t>(newValue);
	switch (newType)
	{
	case eOperandType::Int8:
		return int64 < INT8_MIN || int64 > INT8_MAX;
	case eOperandType::Int16:
		return int64 < INT16_MIN || int64 > INT16_MAX;
	case eOperandType::Int32:
		return int64 < INT32_MIN || int64 > INT32_MAX;
	case eOperandType::Float:
		return newValue < -__FLT_MAX__ || newValue > __FLT_MAX__;
	case eOperandType::Double:
		return newValue < -__DBL_MAX__ || newValue > __DBL_MAX__;
	default:
		return true;
	}
}

template <typename T>
IOperand const *Operand<T>::operators(char const op, IOperand const &rhs) const
{
	eOperandType newType = std::max(_type, rhs.getType());

	// TODO: Is the implementation correct?
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
			throw "Division by zero";
		newValue = value / rhsValue;
		break;

	case '%':
		if (_type >= eOperandType::Float || _type >= eOperandType::Float)
			throw "Floating-point operand";
		if (rhsValue == 0)
			throw "Modulo by zero";
		newValue = static_cast<int32_t>(value) % static_cast<int32_t>(rhsValue);
		break;

	default:
		return NULL;
	}

	if (willNewValueOverflowType(newValue, newType))
		throw "Overflow";

	std::ostringstream ss;
	ss << (newType >= eOperandType::Float ? newValue : static_cast<int32_t>(newValue));
	return gOperandFactory.createOperand(newType, ss.str());
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