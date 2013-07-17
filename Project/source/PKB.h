#pragma once

#include "AST.h"
#include "VarTable.h"
#include "ProcTable.h"
#include "Follows.h"
#include "Parent.h"
#include "Modifies.h"
#include "Uses.h"

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

	Follows* getFollows();
	void setFollows(Follows* follows);

	Parent* getParent();
	void setParent(Parent* parent);

	Modifies* getModifies();
	void setModifies(Modifies* modifies);

	Uses* getUses();
	void setUses(Uses* uses);

	int getStmtNum();
	void setStmtNum(int stmtNum);
private:
	AST* _ast;
	VarTable* _varTable;
	ProcTable* _procTable;
	Follows* _follows;
	Parent* _parent;
	Modifies* _modifies;
	Uses* _uses;

	int _stmtNum;
};

