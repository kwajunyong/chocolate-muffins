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