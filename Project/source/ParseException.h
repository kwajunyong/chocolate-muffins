#pragma once

#include "Definition.h"

#include <exception>
#include <string>

class ParseException: public std::exception
{
public:
	ParseException(int stmtNum, std::string token, std::string message);
	
	const char* what() const throw();

private:
	std::string _message;
};