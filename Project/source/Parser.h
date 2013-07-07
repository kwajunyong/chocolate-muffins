#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <ctype.h>
#include <queue>
#include <stack>

#include "PKB.h"
#include "ParseException.h"

class Parser
{
public:
	Parser(void);
	~Parser(void);

	PKB* parse(std::string fileName);
private:
	std::ifstream _file;
	
	std::string _token;
	void getToken();
	
	int _stmtNum;
	AST* _ast;
	VarTable* _varTable;
	ProcTable* _procTable;

	ASTNode* program();
	ASTNode* procedure();
	ASTNode* statementList();
	ASTNode* statement();
	ASTNode* assignStmt();
	ASTNode* whileStmt();
	ASTNode* ifStmt();
	ASTNode* callStmt();
	ASTNode* expression();

	bool isDigits();
	void matchDigits();

	bool isName();
	void matchName();
	
	bool isKeyword(std::string keyword);
	void matchKeyword(std::string keyword);

	int getOprPriority(std::string operate);

	ASTNode* shuntingYardAlgorithm();
};