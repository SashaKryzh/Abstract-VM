#include "OperandFactory.hpp"
#include "Operand.hpp"

const OperandFactory::fnPtrCreateOperand OperandFactory::fnPtrCreateOperands[eOperandType::MaxOperandType] = {
	&OperandFactory::createInt8,
	&OperandFactory::createInt16,
	&OperandFactory::createInt32,
	&OperandFactory::createFloat,
	&OperandFactory::createDouble,
};

OperandFactory::OperandFactory() {}
OperandFactory::~OperandFactory() {}

IOperand const *OperandFactory::createOperand(eOperandType type, std::string const &value) const
{
	return (this->*fnPtrCreateOperands[type])(value);
}

IOperand const *OperandFactory::createInt8(std::string const &value) const
{
	return new Operand<int8_t>(eOperandType::Int8, value);
}

IOperand const *OperandFactory::createInt16(std::string const &value) const
{
	return new Operand<int16_t>(eOperandType::Int16, value);
}

IOperand const *OperandFactory::createInt32(std::string const &value) const
{
	return new Operand<int32_t>(eOperandType::Int32, value);
}

IOperand const *OperandFactory::createFloat(std::string const &value) const
{
	return new Operand<float>(eOperandType::Float, value);
}

IOperand const *OperandFactory::createDouble(std::string const &value) const
{
	return new Operand<double>(eOperandType::Double, value);
}