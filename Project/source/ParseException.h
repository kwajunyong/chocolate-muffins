#pragma once

#include <exception>
#include <string>

class ParseException: public std::exception
{
public:
	ParseException(std::string token, std::string message);
	ParseException(int stmtNum, std::string token, std::string message);

	const char* what() const throw();

private:
	std::string _message;
};