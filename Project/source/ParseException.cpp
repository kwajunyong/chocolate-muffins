#include "ParseException.h"

ParseException::ParseException(int stmtNum, std::string token, std::string message)
{
	_stmtNum = stmtNum;
	_token = token;
	_message = message;

	updateWhat();
}

ParseException::ParseException(std::string token, std::string message)
{
	_stmtNum = 0;
	_token = token;
	_message = message;

	updateWhat();
}

ParseException::ParseException(std::string message)
{
	_stmtNum = 0;
	_token = "";
	_message = message;

	updateWhat();
}

void ParseException::setStatementNumber(int stmtNum)
{
	_stmtNum = stmtNum;

	updateWhat();
}

void ParseException::updateWhat()
{
	_what = "";

	if (_stmtNum > 0) {
		_what += "Line: " + std::to_string(long double(_stmtNum)) + "\n\n";
	}
	
	if (_token != "") {
		_what += "Token: \"" + _token + "\"\n\n";
	}

	_what += "Message:\n";
	_what += _message + "\n\n";
}

const char* ParseException::what() const throw()
{
	return _what.c_str();
}