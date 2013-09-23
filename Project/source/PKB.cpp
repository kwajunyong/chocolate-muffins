#include "PKB.h"

PKB::PKB(void)
{
	_traverser = new ASTTraverser();
	_matcher = new ASTMatcher();
	_exprBuilder = new ASTExpressionBuilder();
}

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

ASTTraverser* PKB::getASTTraverser()
{
	return _traverser;
}

ASTMatcher* PKB::getASTMatcher()
{
	return _matcher;
}

ASTExpressionBuilder* PKB::getASTExpressionBuilder()
{
	return _exprBuilder;
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

Follows* PKB::getFollows()
{
	return _follows;
}

void PKB::setFollows(Follows* follows)
{
	_follows = follows;
}

Parent* PKB::getParent()
{
	return _parent;
}

void PKB::setParent(Parent* parent)
{
	_parent = parent;
}

Modifies* PKB::getModifies()
{
	return _modifies;
}

void PKB::setModifies(Modifies* modifies)
{
	_modifies = modifies;
}

Uses* PKB::getUses()
{
	return _uses;
}

void PKB::setUses(Uses* uses)
{
	_uses = uses;
}

Calls* PKB::getCalls()
{
	return _calls;
}

void PKB::setCalls(Calls* calls)
{
	_calls = calls;
}

Next* PKB::getNext()
{
	return _next;
}

void PKB::setNext(Next* next)
{
	_next = next;
}

int PKB::getNumOfStmt()
{
	return _numOfStmt;
}

void PKB::setNumOfStmt(int numOfStmt)
{
	_numOfStmt = numOfStmt;
}