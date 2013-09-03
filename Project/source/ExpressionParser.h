#pragma once

#include <string>
#include <sstream>
#include <stack>

#include "ASTNode.h"
#include "ParseException.h"

class ExpressionParser
{
public:
	ExpressionParser(void);
	~ExpressionParser(void);

	ASTNode* parse(std::string expression);

private:
	std::string _token;
	std::istringstream _expression;

	void getToken();

	bool isKeyword(std::string keyword);
	bool isName();
	bool isDigits();

	ASTNode* shuntingYardAlgorithm();
	
	int getOprPriority(std::string operate);
};