#pragma once

#include "ASTNode.h"

class AST
{
public:
	AST(void);
	~AST(void);

	ASTNode* getRootNode();
	void setRootNode(ASTNode* root);

	void joinChild(ASTNode* parent, ASTNode* child);
	void joinNext(ASTNode* previous, ASTNode* next);

	std::vector<std::string> traverse(ASTNode* node);

	bool matchTree(ASTNode* tree, ASTNode* compare);
	bool matchSubTree(ASTNode* tree, ASTNode* subtree);

	ASTNode* getStatementNode(int stmtNum);
	std::vector<ASTNode*> getStatementNodes(ASTType type);
	std::vector<int> getStatementNumbers(ASTType type);
private:
	ASTNode* _root;

	void traverse(ASTNode* node, std::vector<std::string> &list, int level);

	std::string indent(int level);

	void search(ASTNode* node, std::vector<ASTNode*> &list, int stmtNum, ASTType type);
	void search(ASTNode* node, std::vector<int> &list, ASTType type);
};

