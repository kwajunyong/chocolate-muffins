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
	//void test(); 
	void switchToTraditionalMode(bool value);
private:
	vector<QueryNode*> queryNodeList; // for traditional mode
	vector<QueryNode*>::iterator iterQueryNode; // for traditional mode
	
	map<double, QueryNode*> rankingList;
	map<double, QueryNode*>::reverse_iterator iterRankingList;

	// store variable and its respective query node 
	VariableDict variableDictionary;
	bool TraditionalMode; 
};