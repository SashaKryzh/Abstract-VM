#include "AvmException.hpp"

#include <sstream>
#include <fstream>

static std::string lineString(size_t line)
{
	if (line != 0)
	{
		std::ostringstream ss;
		ss << "Line " << std::setw(3) << std::left << line << " : ";
		return ss.str();
	}
	else
		return "";
}

AvmException::AvmException() {}
AvmException::AvmException(std::string const &msg) : _msg(msg) {}
AvmException::~AvmException() {}
AvmException::AvmException(AvmException const &rhs) { _msg = rhs._msg; }

const char *AvmException::what() const noexcept
{
	return _msg.c_str();
}

//
// Runtime Exceptions
//

InstructionException::InstructionException(std::string const &msg) : AvmException(msg) {}

NoExitInstruction::NoExitInstruction(size_t line)
{
	_msg = lineString(line) + "No exit instruction at the end";
}

OperandException::OperandException(std::string const &msg) : AvmException(msg) {}

//
// Parser Exceptions
//

UnknownToken::UnknownToken(size_t line, std::string lexeme)
{
	_msg = lineString(line) + "Lexical error  : Unknown token : " + lexeme;
}

UnexpectedEnd::UnexpectedEnd(size_t line)
{
	_msg = lineString(line) + "Syntatic error : Unexpected end of tokens";
}

UnexpectedToken::UnexpectedToken(size_t line, Token::Type tokenType, Token::Type expectedType)
{
	_msg = lineString(line) + "Syntatic error : Got " + tokenTypeStrings[tokenType] +
		   " while expected " + tokenTypeStrings[expectedType];
}

NewLineValue::NewLineValue(size_t line)
{
	_msg = lineString(line) + "Syntatic error : Got VALUE while expected INSTR or INSTR WITH VALUE";
}