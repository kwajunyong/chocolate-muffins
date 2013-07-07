#pragma once

#include "AST.h"
#include "VarTable.h"
#include "ProcTable.h"

class PKB
{
public:
	PKB(void);
	~PKB(void);

	AST* getAST();
	void setAST(AST* ast);

	VarTable* getVarTable();
	void setVarTable(VarTable* varTable);

	ProcTable* getProcTable();
	void setProcTable(ProcTable* procTable);

	int getStmtNum();
	void setStmtNum(int stmtNum);
private:
	AST* _ast;
	VarTable* _varTable;
	ProcTable* _procTable;

	int _stmtNum;
};

