#pragma once

#include "PKB.h"

#include <vector>
#include <utility>
#include <iostream>

class DesignExtractor
{
public:
	DesignExtractor(void);
	~DesignExtractor(void);

	void extract(PKB* pkb);

private:
	PKB* _pkb;
	
	AST* _ast;

	VarTable* _varTable;
	ProcTable* _procTable;

	Follows* _follows;
	Parent* _parent;
	
	Modifies* _modifies;
	Uses* _uses;

	Calls* _calls;

	int _numOfStmt;

	std::vector<ASTNode*> _callNodes;

	void traverseAST(ASTNode* node, std::vector<int> statements, std::string procedure);

	void updateStatements(ASTNode* node, std::vector<int> &statements);
	void updateProcedure(ASTNode* node, std::string &procedure);

	void extractStatementNodes(ASTNode* node);

	void extractFollows(ASTNode* node);
	void extractParent(ASTNode* node);

	void extractModifies(ASTNode* node, std::vector<int> statements, std::string procedure);
	void extractUses(ASTNode* node, std::vector<int> statements, std::string procedure);

	void extractCalls(ASTNode* node, std::string procedure);
	void validateCall(ASTNode* node);

	void traverseCalls();
	void traverseCalls(std::string procedure, std::vector<int> &visited, std::vector<std::pair<std::string, std::string>> &calls);

	void extractModifiesFromCall(std::pair<std::string, std::string> call);
	void extractUsesFromCall(std::pair<std::string, std::string> call);

	void extractFromCallNodes();

	void extractModifiesFromCallNodes();
	void extractUsesFromCallNodes();

	bool isStatement(ASTNode* node);
	bool isFirstChild(ASTNode* node);
	
	bool isFollows(ASTNode* node);
	bool isParent(ASTNode* node);
	bool isModifies(ASTNode* node);
	bool isUses(ASTNode* node);
};