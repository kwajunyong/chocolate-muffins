#pragma once

#include "ASTNode.h"

class ASTTraverser
{
public:
	ASTTraverser(void);
	~ASTTraverser(void);

	std::vector<std::string> traverse(ASTNode* node);

private:
	void traverse(ASTNode* node, std::vector<std::string> &list, int level);
	std::string indent(int level);
};