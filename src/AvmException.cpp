#include "AvmException.hpp"

AvmException::AvmException(std::string const &msg) : _msg(msg) {}
AvmException::~AvmException() {}
AvmException::AvmException(AvmException const &rhs) { _msg = rhs._msg; }

const char *AvmException::what() const noexcept
{
	return _msg.c_str();
}

InstructionException::InstructionException(std::string const &msg) : AvmException(msg) {}

OperandException::OperandException(std::string const &msg) : AvmException(msg) {}