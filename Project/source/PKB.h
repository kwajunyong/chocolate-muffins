#pragma once

#include "AST.h"
#include "ASTTraverser.h"
#include "ASTMatcher.h"
#include "ASTExpressionBuilder.h"
#include "VarTable.h"
#include "ProcTable.h"
#include "Follows.h"
#include "Parent.h"
#include "Modifies.h"
#include "Uses.h"
#include "Calls.h"

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

	int getNumOfStmt();
	void setNumOfStmt(int numOfStmt);
private:
	AST* _ast;
	ASTTraverser* _traverser;
	ASTMatcher* _matcher;
	ASTExpressionBuilder* _exprBuilder;
	
	VarTable* _varTable;
	ProcTable* _procTable;
	
	Follows* _follows;
	Parent* _parent;
	
	Modifies* _modifies;
	Uses* _uses;
	
	Calls* _calls;

	int _numOfStmt;
};