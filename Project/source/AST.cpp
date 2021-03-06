#include "AST.h"

AST::AST(void)
{
	_root = NULL;
}

AST::~AST(void)
{}

ASTNode* AST::getRootNode()
{
	return _root;
}

void AST::setRootNode(ASTNode* root)
{
	_root = root;
}

bool AST::storeStatementNode(ASTNode* node)
{
	switch (node->getType()) {
		case ASSIGN:
			_assignStmt.push_back(node->getStatementNumber());
			
			break;
		case CALL:
			_callStmt.push_back(node->getStatementNumber());
			
			break;
		case WHILE:
			_whileStmt.push_back(node->getStatementNumber());
			_varWhileMap[node->getChild()->getName()].push_back(node->getStatementNumber());

			break;
		case IF:
			_ifStmt.push_back(node->getStatementNumber());
			_varIfMap[node->getChild()->getName()].push_back(node->getStatementNumber());

			break;
		default:
			return false;
	}

	_stmt.push_back(node->getStatementNumber());
	_stmtNodes.push_back(node);
	
	if (node->getPrevious() == NULL && node->getParent() != NULL && node->getParent()->getType() == STATEMENT_LIST) {
		_stmtListFirstChildren.push_back(node->getStatementNumber());
	}

	return true;
}

ASTNode* AST::getStatementNode(int stmtNum)
{
	if (stmtNum < 1 || stmtNum > _stmtNodes.size()) {
		return NULL;
	}

	return _stmtNodes[stmtNum - 1];
}

ASTType AST::getStatementType(int stmtNum)
{
	ASTNode* node = getStatementNode(stmtNum);

	return (node != NULL) ? node->getType() : NONE;
}

std::string AST::getCalledProcedure(int stmtNum)
{
	ASTNode* node = getStatementNode(stmtNum);

	if (node->getType() == CALL) {
		return node->getName();
	} else {
		return "";
	}
}

std::vector<int> AST::getStatementNumbers(ASTType type)
{	
	switch (type) {
		case ASSIGN:
			return _assignStmt;
		case WHILE:
			return _whileStmt;
		case IF:
			return _ifStmt;
		case CALL:
			return _callStmt;
		case ALL:
			return _stmt;
		default:
			return std::vector<int>();
	}
}

std::vector<int> AST::getStatementNumbers(ASTType type, std::string controlVariable)
{	
	switch (type) {
		case WHILE:
			return _varWhileMap[controlVariable];
		case IF:
			return _varIfMap[controlVariable];
		default:
			return std::vector<int>();
	}
}

std::vector<ASTNode*> AST::getStatementNodes(ASTType type)
{
	if (type == ALL) {
		return _stmtNodes;
	}

	std::vector<int> stmtNumList = getStatementNumbers(type);
	std::vector<ASTNode*> stmtNodes;

	for (size_t i = 0; i < stmtNumList.size(); i++) {
		stmtNodes.push_back(getStatementNode(stmtNumList[i]));
	}

	return stmtNodes;
}

void AST::search(ASTNode* node, std::vector<ASTNode*> &list, int stmtNum, ASTType type)
{
	while (node != NULL) {
		if (node->getType() != NONE && node->getType() == type) {
			list.push_back(node);
		}

		if (node->getStatementNumber() != 0 && node->getStatementNumber() == stmtNum) {
			list.push_back(node);
		}

		if (node->getChild() != NULL) {
			search(node->getChild(), list, stmtNum, type);
		}
		
		node = node->getNext();
	}
}

std::vector<int> AST::allStmtListFirstChildren()
{
	return _stmtListFirstChildren;
}

void AST::search(ASTNode* node, std::vector<int> &list, ASTType type)
{
	while (node != NULL) {
		if (node->getType() != NONE && node->getType() == type) {
			list.push_back(node->getStatementNumber());
		}

		if (node->getChild() != NULL) {
			search(node->getChild(), list, type);
		}
		
		node = node->getNext();
	}
}