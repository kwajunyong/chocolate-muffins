#pragma once
#include <vector>
#include "QueryClass.h"
class QueryNode {
public:
	QueryNode(QueryClass*);
	double calculateScore();
	void addLeftArm(QueryNode*);
	void addRightArm(QueryNode*);

	string &getVariable1Name();
	string &getVariable2Name();
	QueryClass* getMainClass();

private:
	QueryClass *mainClass;
	vector<QueryNode*> leftArm;
	vector<QueryNode*> rightArm;
	string var1;
	string var2;
};