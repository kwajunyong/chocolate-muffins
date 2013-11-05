#pragma once
#include <string>
#include <vector>
#include "EnumType.h"
#include "QueryClass.h"
#include "QueryNode.h"
typedef map<string, vector<QueryNode*>> VariableDict;
typedef vector<QueryNode*> QueryNodeList;
using namespace std;

class QueryTree {
public:
	QueryTree() ;
	// is it going to be used in future handling? if not, we don't need to update it. 
	bool isVariableImportant(string variableName); 

    void addQueryClass(QueryClass* qc); 
	QueryClass* pop();
	bool isEmpty();
	void clear();
	// once solidified, the querytree disallow any kind of query class addition
	// and before any solidictioant
	void solidify();

private:
	//vector<QueryClass*> queryList; // temporary
	
	
	// store variable and its respective query node 
	VariableDict variableDictionary;
};