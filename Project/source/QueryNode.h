#pragma once
#include <vector>
#include "QueryClass.h"
class QueryNode {
public:
	QueryNode(QueryClass*);
	void calculateScore();
	void addLeftArm(QueryNode*);
	void addRightArm(QueryNode*);

	string &getVariable1Name();
	string &getVariable2Name();

private:
	QueryClass *mainClass;
	vector<QueryNode*> leftArm;
	vector<QueryNode*> rightArm;
	string var1;
	string var2;
};