#ifndef OPERAND_FACTORY_HPP
#define OPERAND_FACTORY_HPP

#include "IOperand.hpp"

class OperandFactory
{
public:
	OperandFactory();
	~OperandFactory();

	OperandFactory(OperandFactory const &) = delete;
	OperandFactory &operator=(OperandFactory const &) = delete;

	IOperand const *createOperand(eOperandType type, std::string const &value) const;

private:
	typedef IOperand const *(OperandFactory::*fnPtrCreateOperand)(std::string const &) const;
	static const fnPtrCreateOperand fnPtrCreateOperands[MaxOperandType];

	IOperand const *createInt8(std::string const &value) const;
	IOperand const *createInt16(std::string const &value) const;
	IOperand const *createInt32(std::string const &value) const;
	IOperand const *createFloat(std::string const &value) const;
	IOperand const *createDouble(std::string const &value) const;
};

static const OperandFactory gOperandFactory;

#endif
