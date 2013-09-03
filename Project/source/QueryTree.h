#pragma once
#include <string>
#include "EnumType.h"
#include "QueryClass.h"

using namespace std;

class QueryTree {
public:
	QueryTree() ;
	bool isVariableImportant(string variableName); // is it going to be used in future handling? if not, we don't need to update it. 
    void addQueryClass(QueryClass* qc); 
	QueryClass* pop();
	bool isEmpty();
	void clear();
private:
	vector<QueryClass*> queryList; // temporary
	
};