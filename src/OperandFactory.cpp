#include "OperandFactory.hpp"

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
	std::cout << static_cast<int>(type) << " " << value << std::endl;
	return NULL;
}

IOperand const *OperandFactory::createInt8(std::string const &value) const
{
	return NULL;
}

IOperand const *OperandFactory::createInt16(std::string const &value) const { return NULL; }

IOperand const *OperandFactory::createInt32(std::string const &value) const { return NULL; }

IOperand const *OperandFactory::createFloat(std::string const &value) const { return NULL; }

IOperand const *OperandFactory::createDouble(std::string const &value) const { return NULL; }