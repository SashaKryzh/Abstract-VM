#ifndef AVM_EXCEPTION_HPP
#define AVM_EXCEPTION_HPP

#include <exception>
#include <string>

class AvmException : public std::exception
{
public:
	AvmException(std::string const &msg);
	~AvmException();

	AvmException(AvmException const &);

	AvmException &operator=(AvmException const &) = delete;
	AvmException(AvmException &&) = delete;
	AvmException &operator=(AvmException &&) = delete;

	const char *what() const noexcept;

private:
	std::string _msg;
};

class InstructionException : public AvmException
{
public:
	InstructionException(std::string const &msg);
};

class OperandException : public AvmException
{
public:
	OperandException(std::string const &msg);
};

#endif