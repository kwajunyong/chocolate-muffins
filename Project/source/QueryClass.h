#pragma once

#include "EnumType.h"
#include "ASTParameter.h"
#include "PKB.h"
#include <string>
#include <vector>
#include "CommonUtility.h"
using namespace std;
class QueryManager;
class QueryClass {
public:
	QueryClass();
	QueryManager *getQueryManager();

	QueryClass(QUERYTYPE queryType, QueryManager* qm, PKB *pkb);
	void addParam(const string &parameterName, VARIABLETYPE parameterType);
	virtual void addParam(const string &parameterName, VARIABLETYPE parameterType, const string &attribute);

	bool keepRelationship();

	virtual void run();
	void updateResult();
	vector<ASTParameter*> &getParameterList();
	
	bool hasResult();
	void loadVariable(int paramIndex, FastSearchString &varList);
	void loadVariable(int paramIndex, FastSearchInteger &varList);
	void updateVariable(vector<pair<string, string>> &relationship, const FastSearchString &finalListOne, const FastSearchString &finalTwo, const bool &keepRelation);
	QUERYTYPE getQueryType();
	void setDebug(bool val);
protected:
	
	bool debug; 
	bool failed;

	QueryManager* myQM; 
	vector<ASTParameter*> parameterList;
	QUERYTYPE myQueryType;  

	PKB* pkbManager ;
};
