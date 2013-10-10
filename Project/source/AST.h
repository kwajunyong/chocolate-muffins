#pragma once

#include <map>

#include "ASTNode.h"

class AST
{
public:
	AST(void);
	~AST(void);

	ASTNode* getRootNode();
	void setRootNode(ASTNode* root);

	bool storeStatementNode(ASTNode* node);

	ASTNode* getStatementNode(int stmtNum);
	ASTType getStatementType(int stmtNum);

	std::vector<ASTNode*> getStatementNodes(ASTType type);
	std::vector<int> getStatementNumbers(ASTType type);
	std::vector<int> getStatementNumbers(ASTType type, std::string controlVariable);
private:
	ASTNode* _root;

	std::vector<ASTNode*> _stmtNodes;

	std::vector<int> _stmt;
	std::vector<int> _assignStmt;
	std::vector<int> _whileStmt;
	std::vector<int> _ifStmt;
	std::vector<int> _callStmt;

	std::map<std::string, std::vector<int>> _varWhileMap;
	std::map<std::string, std::vector<int>> _varIfMap;

	void search(ASTNode* node, std::vector<ASTNode*> &list, int stmtNum, ASTType type);
	void search(ASTNode* node, std::vector<int> &list, ASTType type);
};