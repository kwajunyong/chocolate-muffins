#pragma once

#include <exception>
#include <string>

class ParseException: public std::exception
{
public:
	ParseException(int stmtNum, std::string token, std::string message);
	ParseException(std::string token, std::string message);
	ParseException(std::string message);

	void setStatementNumber(int stmtNum);

	const char* what() const throw();

private:
	int _stmtNum;
	std::string _token;
	std::string _message;

	std::string _what;

	void updateWhat();
};