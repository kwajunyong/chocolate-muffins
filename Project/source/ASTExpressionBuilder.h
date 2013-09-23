#pragma once

#include <string>
#include <sstream>
#include <list>

#include "ASTNode.h"
#include "ParseException.h"

class ASTExpressionBuilder
{
public:
	ASTExpressionBuilder(void);
	~ASTExpressionBuilder(void);

	ASTNode* build(std::string expression);
	ASTNode* build(std::list<std::string> tokens);

private:
	std::string _token;
	std::istringstream _expression;
	std::list<std::string> _tokens;
	
	std::vector<std::string> _operators;
	std::vector<ASTNode*> _results;

	void getToken();
	void tokeniseExpression();

	bool isKeyword(std::string keyword);
	bool isName();
	bool isDigits();

	ASTNode* shuntingYardAlgorithm();
	
	int getOprPriority(std::string operate);

	void buildOperators();
	void buildOperands();
};