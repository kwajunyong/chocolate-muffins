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
	void openFile(std::string fileName);
	void closeFile();
	
	std::string _token;
	void getToken();

	PKB* _pkb;
	
	int _stmtNum;
	AST* _ast;
	VarTable* _varTable;
	ProcTable* _procTable;
	ConstTable* _constTable;

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

	void checkRedundantToken(); 

	std::list<std::string> getExpressionTokens();
};