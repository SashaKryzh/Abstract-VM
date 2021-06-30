#ifndef AVM_EXCEPTION_HPP
#define AVM_EXCEPTION_HPP

#include <exception>
#include <string>

#include "Token.hpp"

class AvmException : public std::exception
{
public:
	AvmException();
	AvmException(std::string const &msg);
	~AvmException();

	AvmException(AvmException const &);

	AvmException &operator=(AvmException const &) = delete;
	AvmException(AvmException &&) = delete;
	AvmException &operator=(AvmException &&) = delete;

	const char *what() const noexcept;

protected:
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

class UnknownToken : public AvmException
{
public:
	UnknownToken(size_t line, std::string lexeme);
};

class UnexpectedEnd : public AvmException
{
public:
	UnexpectedEnd(size_t line);
};

class UnexpectedToken : public AvmException
{
public:
	UnexpectedToken(size_t line, Token::Type tokenType, Token::Type expectedType);
};

class NewLineValue : public AvmException
{
public:
	NewLineValue(size_t line);
};

#endif