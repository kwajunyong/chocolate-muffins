#pragma once

#include "EnumType.h"
#include "ASTParameter.h"
#include "PKB.h"
#include <string>
#include <vector>
using namespace std;
class QueryManager;
class QueryClass {
public:
	QueryClass();
	QueryManager *getQueryManager();

	QueryClass(QUERYTYPE queryType, QueryManager* qm, PKB *pkb);
	void addParam(const string &parameterName, VARIABLETYPE parameterType);
	void addParam(const string &parameterName, VARIABLETYPE parameterType, const string &attribute);
	virtual void run();
	void updateResult();
	vector<ASTParameter*> &getParameterList();
	
	bool hasResult();
	void convertVector(const map<string, int> &mapList, vector<string>& resultList);
	void convertVector(const map<int, int> &mapList, vector<int>& resultList);
	void convertVector(const map<int, int> &mapList, vector<string>& resultList);
protected:
	

	bool failed;

	QueryManager* myQM; 
	vector<ASTParameter*> parameterList;
	QUERYTYPE myQueryType;  

	PKB* pkbManager ;
};
