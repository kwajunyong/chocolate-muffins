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

void AST::joinChild(ASTNode* parent, ASTNode* child)
{
	parent->setChild(child);
	child->setParent(parent);
}

void AST::joinNext(ASTNode* previous, ASTNode* next)
{
	previous->setNext(next);
	next->setPrevious(previous);

	next->setParent(previous->getParent());
}

std::vector<std::string> AST::traverse(ASTNode* node)
{
	std::vector<std::string> list;

	traverse(node, list, 0);

	return list;
}

void AST::traverse(ASTNode* node, std::vector<std::string> &list, int level)
{
	while (node != NULL) {
		list.push_back(indent(level) + node->print());
		
		if (node->getChild() != NULL) {
			traverse(node->getChild(), list, level + 1);
		}
		
		node = node->getNext();
	}
}

std::string AST::indent(int level)
{
	std::string indent;

	for (int i = 0; i < level; i++) {
		indent.append("  ");
	}

	return indent;
}

bool AST::matchTree(ASTNode* tree, ASTNode* compare)
{
	if (tree == NULL && compare == NULL) {
		return true;
	}

	if (tree == NULL || compare == NULL) {
		return false;
	}

	if (tree->equals(compare)) {
		ASTNode* nodeChild = tree->getChild();
		ASTNode* compareChild = compare->getChild();

		while (true) {
			if (nodeChild != NULL && compareChild != NULL) {
				if (matchTree(nodeChild, compareChild)) {
					nodeChild = nodeChild->getNext();
					compareChild = compareChild->getNext();

					continue;
				} else {
					return false;
				}
			}

			if (nodeChild == NULL && compareChild == NULL) {
				return true;
			}

			if (nodeChild == NULL || compareChild == NULL) {
				return false;
			}
		}
	}
}

bool AST::matchSubTree(ASTNode* tree, ASTNode* subtree)
{
	if (subtree == NULL) {
		return true;
	}

	if (tree == NULL) {
		return false;
	}

	if (matchTree(tree, subtree)) {
			return true;
	}

	ASTNode* child = tree->getChild();

	while (child != NULL) {
		if (matchSubTree(child, subtree)) {
			return true;
		} else {
			child = child->getNext();
		}
	}

	return false;
}

ASTNode* AST::getStatementNode(int stmtNum)
{
	std::vector<ASTNode*> list;

	search(_root, list, stmtNum, NONE);

	return list.front();
}

std::vector<ASTNode*> AST::getStatementNodes(ASTType type)
{
	std::vector<ASTNode*> list;

	search(_root, list, 0, type);

	return list;
}

std::vector<int> AST::getStatementNumbers(ASTType type)
{
	std::vector<int> list;

	search(_root, list, type);

	return list;
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