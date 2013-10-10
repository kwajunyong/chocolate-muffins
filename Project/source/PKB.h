#pragma once

#include "AST.h"
#include "ASTTraverser.h"
#include "ASTMatcher.h"
#include "ASTExpressionBuilder.h"
#include "VarTable.h"
#include "ProcTable.h"
#include "ConstTable.h"
#include "Follows.h"
#include "Parent.h"
#include "Modifies.h"
#include "Uses.h"
#include "Calls.h"
#include "Next.h"

class PKB
{
public:
	PKB(void);
	~PKB(void);

	AST* getAST();
	void setAST(AST* ast);

	ASTTraverser* getASTTraverser();
	ASTMatcher* getASTMatcher();
	ASTExpressionBuilder* getASTExpressionBuilder();

	VarTable* getVarTable();
	void setVarTable(VarTable* varTable);

	ProcTable* getProcTable();
	void setProcTable(ProcTable* procTable);

	ConstTable* getConstTable();
	void setConstTable(ConstTable* constTable);

	Follows* getFollows();
	void setFollows(Follows* follows);

	Parent* getParent();
	void setParent(Parent* parent);

	Modifies* getModifies();
	void setModifies(Modifies* modifies);

	Uses* getUses();
	void setUses(Uses* uses);

	Calls* getCalls();
	void setCalls(Calls* calls);

	Next* getNext();
	void setNext(Next* next);

	int getNumOfStmt();
	void setNumOfStmt(int numOfStmt);
private:
	AST* _ast;
	ASTTraverser* _traverser;
	ASTMatcher* _matcher;
	ASTExpressionBuilder* _exprBuilder;
	
	VarTable* _varTable;
	ProcTable* _procTable;
	ConstTable* _constTable;

	Follows* _follows;
	Parent* _parent;
	
	Modifies* _modifies;
	Uses* _uses;
	
	Calls* _calls;
	Next* _next;

	int _numOfStmt;
};