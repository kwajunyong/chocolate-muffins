#pragma once

#include "ASTNode.h"

class AST
{
public:
	AST(void);
	~AST(void);

	ASTNode* getRootNode();
	void setRootNode(ASTNode* root);

	bool addStatementNodeToList(ASTNode* node);

	ASTNode* getStatementNode(int stmtNum);
	ASTType getStatementType(int stmtNum);
	std::vector<ASTNode*> getStatementNodes(ASTType type);
	std::vector<int> getStatementNumbers(ASTType type);

private:
	ASTNode* _root;

	std::vector<ASTNode*> _stmtNodes;
	std::vector<int> _assignStmt;
	std::vector<int> _whileStmt;
	std::vector<int> _ifStmt;
	std::vector<int> _callStmt;

	void search(ASTNode* node, std::vector<ASTNode*> &list, int stmtNum, ASTType type);
	void search(ASTNode* node, std::vector<int> &list, ASTType type);
};