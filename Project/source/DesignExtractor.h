#pragma once

#include "PKB.h"

#include <vector>
#include <iostream>

class DesignExtractor
{
public:
	DesignExtractor(void);
	~DesignExtractor(void);

	void extract(PKB* pkb);

private:
	PKB* _pkb;
	
	VarTable* _varTable;
	ProcTable* _procTable;

	Follows* _follows;
	Parent* _parent;
	
	Modifies* _modifies;
	Uses* _uses;

	int _numOfStmt;

	std::vector<ASTNode*> _calls;

	void traverseAndExtract(ASTNode* node, std::vector<int> statements, std::string procedure, int prevLine);

	void updateStatements(ASTNode* node, std::vector<int> &statements);
	void updateProcedure(ASTNode* node, std::string &procedure);

	void extractFollows(ASTNode* node);
	void extractParent(ASTNode* node);

	void extractModifies(ASTNode* node, std::vector<int> statements, std::string procedure);
	void extractUses(ASTNode* node, std::vector<int> statements, std::string procedure);

	void extractCalls(ASTNode* node, std::string procedure);

	//void extractModifiesFromCallNodes();
	//void extractUsesFromCallNodes();

	bool isStatement(ASTNode* node);
	bool isFirstChild(ASTNode* node);
	
	bool isFollows(ASTNode* node);
	bool isParent(ASTNode* node);
	bool isModifies(ASTNode* node);
	bool isUses(ASTNode* node);

	void validateCall(ASTNode* node);
};