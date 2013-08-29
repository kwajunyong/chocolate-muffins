#include "ASTMatcher.h"

ASTMatcher::ASTMatcher(void)
{}

ASTMatcher::~ASTMatcher(void)
{}

bool ASTMatcher::matchTree(ASTNode* tree, ASTNode* compare)
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
			
			if (nodeChild != NULL && compareChild != NULL) {
				break;
			}
		}
	}

	return false;
}

bool ASTMatcher::matchSubTree(ASTNode* tree, ASTNode* subtree)
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