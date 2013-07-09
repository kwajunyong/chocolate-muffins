#pragma once

#include "ASTNode.h"

class AST
{
public:
	AST(void);
	~AST(void);

	ASTNode* getRootNode();
	void setRootNode(ASTNode* root);

	ASTNode* getStatementNode(int stmtNum);
	std::vector<ASTNode*> getStatementNodes(ASTType type);
	std::vector<int> getStatementNumbers(ASTType type);

	static void joinChild(ASTNode* parent, ASTNode* child);
	static void joinNext(ASTNode* previous, ASTNode* next);

	static std::vector<std::string> traverse(ASTNode* node);

	static bool matchTree(ASTNode* tree, ASTNode* compare);
	static bool matchSubTree(ASTNode* tree, ASTNode* subtree);
private:
	ASTNode* _root;

	void search(ASTNode* node, std::vector<ASTNode*> &list, int stmtNum, ASTType type);
	void search(ASTNode* node, std::vector<int> &list, ASTType type);

	static void traverse(ASTNode* node, std::vector<std::string> &list, int level);

	static std::string indent(int level);
};

