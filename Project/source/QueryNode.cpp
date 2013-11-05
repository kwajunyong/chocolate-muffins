#include "QueryNode.h"


QueryNode::QueryNode(QueryClass *main) {
	mainClass = main;
}

void QueryNode::addLeftArm(QueryClass *leftQuery) {
	leftArm.push_back(leftQuery);
}

void QueryNode::addRightArm(QueryClass *rightQuery) {
	rightArm.push_back(rightQuery);
}

void QueryNode::calculateScore() {
	
}