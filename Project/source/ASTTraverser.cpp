#include "ASTTraverser.h"


ASTTraverser::ASTTraverser(void)
{}

ASTTraverser::~ASTTraverser(void)
{}

std::vector<std::string> ASTTraverser::traverse(ASTNode* node)
{
	std::vector<std::string> list;

	traverse(node, list, 0);

	return list;
}

void ASTTraverser::traverse(ASTNode* node, std::vector<std::string> &list, int level)
{
	while (node != NULL) {
		list.push_back(indent(level) + node->print());
		
		if (node->getChild() != NULL) {
			traverse(node->getChild(), list, level + 1);
		}
		
		node = node->getNext();
	}
}

std::string ASTTraverser::indent(int level)
{
	std::string indent;

	for (int i = 0; i < level; i++) {
		indent.append("  ");
	}

	return indent;
}