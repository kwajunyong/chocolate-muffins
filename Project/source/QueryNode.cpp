#include "QueryNode.h"


QueryNode::QueryNode(QueryClass *main) {
	mainClass = main;
	// cache the variable name;
	var1 = main->getParameterList().at(0)->getVariableName();
	var2 = main->getParameterList().at(0)->getVariableName();
}

string &QueryNode::getVariable1Name() {
	return var1;
}
string &QueryNode::getVariable2Name() {
	return var2;
}

void QueryNode::addLeftArm(QueryNode *leftQuery) {
	leftArm.push_back(leftQuery);
}

void QueryNode::addRightArm(QueryNode *rightQuery) {
	rightArm.push_back(rightQuery);
}

void QueryNode::calculateScore() {
	
}