#pragma once

#include "ASTNode.h"
#include "ExpressionParser.h"

class AST
{
public:
	AST(void);
	~AST(void);

	ASTNode* getRootNode();
	void setRootNode(ASTNode* root);

	ASTNode* getStatementNode(int stmtNum);
	ASTType getStatementType(int stmtNum);
	std::vector<ASTNode*> getStatementNodes(ASTType type);
	std::vector<int> getStatementNumbers(ASTType type);

	std::vector<std::string> traverse(ASTNode* node);

	bool matchTree(ASTNode* tree, ASTNode* compare);
	bool matchSubTree(ASTNode* tree, ASTNode* subtree);

	ASTNode* buildExpressionNode(std::string expression);

private:
	ASTNode* _root;
	ExpressionParser _expParser;

	void search(ASTNode* node, std::vector<ASTNode*> &list, int stmtNum, ASTType type);
	void search(ASTNode* node, std::vector<int> &list, ASTType type);
	
	void traverse(ASTNode* node, std::vector<std::string> &list, int level);

	std::string indent(int level);
};