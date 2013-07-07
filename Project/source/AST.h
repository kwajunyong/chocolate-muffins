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

private:
	ASTNode* _root;

	void traverse(ASTNode* node, std::vector<std::string> &list, int level);

	std::string indent(int level);
};

