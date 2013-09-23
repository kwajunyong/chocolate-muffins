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
	void addParam(string parameterName, VARIABLETYPE parameterType);
	virtual void run();
	void updateResult();
	vector<ASTParameter*> &getParameterList();
	
	bool hasResult();
	void convertVector(const map<string, int> &mapList, vector<string>& resultList);
	void convertVector(const map<int, int> &mapList, vector<int>& resultList);
protected:
	

	bool failed;

	QueryManager* myQM; 
	vector<ASTParameter*> parameterList;
	QUERYTYPE myQueryType;  

	PKB* pkbManager ;
};