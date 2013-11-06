#include "QueryNode.h"
#include "QueryScore.h"


QueryNode::QueryNode(QueryClass *main) {
	mainClass = main;
	// cache the variable name;
	var1 = main->getParameterList().at(0)->getVariableName();
	var2 = main->getParameterList().at(1)->getVariableName();
}

QueryClass* QueryNode::getMainClass() {
	return mainClass;
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

double QueryNode::calculateScore() {
	int noOfUpdatableVariable = 0;

	vector<ASTParameter*> paramList = mainClass->getParameterList();
	vector<ASTParameter*>::iterator iterParamList;

	for (iterParamList = paramList.begin(); iterParamList != paramList.end(); iterParamList++)  {
		if ((*iterParamList)->updateAble())
			noOfUpdatableVariable++;
	}

	double basicScore = QueryScore::getScore(mainClass->getQueryType(), noOfUpdatableVariable);

	double armScore = (leftArm.size() + rightArm.size()) * QueryScore::getArmScore();
	armScore = armScore * QueryScore::getMultiplierArm(mainClass->getQueryType());

	return basicScore + armScore;
}
	
