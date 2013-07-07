#include "ParseException.h"

ParseException::ParseException(int stmtNum, std::string token, std::string message)
{
	_message += "Line: " + std::to_string(long double(stmtNum)) + "\n";
	_message += "Token: \"" + token + "\"\n";
	_message += "\n";
	_message += "Message:\n";
	_message += message;
}

const char* ParseException::what() const throw()
{
	return _message.c_str();
}