#include "PKB.h"

PKB::PKB(void)
{}

PKB::~PKB(void)
{}

AST* PKB::getAST()
{
	return _ast;
}

void PKB::setAST(AST* ast)
{
	_ast = ast;
}

VarTable* PKB::getVarTable()
{
	return _varTable;
}

void PKB::setVarTable(VarTable* varTable)
{
	_varTable = varTable;
}

ProcTable* PKB::getProcTable()
{
	return _procTable;
}

void PKB::setProcTable(ProcTable* procTable)
{
	_procTable = procTable;
}

int PKB::getStmtNum()
{
	return _stmtNum;
}

void PKB::setStmtNum(int stmtNum)
{
	_stmtNum = stmtNum;
}