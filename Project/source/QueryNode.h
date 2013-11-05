#pragma once
#include <vector>
#include "QueryClass.h"
class QueryNode {
public:
	QueryNode(QueryClass*);
	void calculateScore();
	void addLeftArm(QueryClass*);
	void addRightArm(QueryClass*);
private:
	QueryClass *mainClass;
	vector<QueryClass*> leftArm;
	vector<QueryClass*> rightArm;
};