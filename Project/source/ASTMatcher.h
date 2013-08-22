#pragma once

#include "ASTNode.h"

class ASTMatcher
{
public:
	ASTMatcher(void);
	~ASTMatcher(void);

	bool matchTree(ASTNode* tree, ASTNode* compare);
	bool matchSubTree(ASTNode* tree, ASTNode* subtree);
};

