#include "PKB.h"

PKB::PKB(void)
{
	_traverser = new ASTTraverser();
	_matcher = new ASTMatcher();
	_exprBuilder = new ASTExpressionBuilder();

	_ast = NULL;
	
	_varTable = NULL;
	_procTable = NULL;
	
	_follows = NULL;
	_parent = NULL;
	
	_modifies = NULL;
	_uses = NULL;
	
	_calls = NULL;
	_next = NULL;
	_affects = NULL;

	_numOfStmt = 0;
	//_stats = NULL;
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

ConstTable* PKB::getConstTable()
{
	return _constTable;
}

void PKB::setConstTable(ConstTable* constTable)
{
	_constTable = constTable;
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

Affects* PKB::getAffects()
{
	return _affects;
}

void PKB::setAffects(Affects* affects)
{
	_affects = affects;
}

int PKB::getNumOfStmt()
{
	return _numOfStmt;
}

void PKB::setNumOfStmt(int numOfStmt)
{
	_numOfStmt = numOfStmt;
}

//Stats* PKB::getStats()
//{
//	return _stats;
//}
//
//void PKB::setStats(Stats* stats)
//{
//	_stats = stats;
//}