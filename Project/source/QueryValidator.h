#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

#include "EnumType.h"
#include "QueryManager.h"
#include "QueryClass.h"
#include "PKB.h"
#include "ModifiesEngine.h"
#include "FollowsEngine.h"
#include "FollowsStarEngine.h"
#include "NextEngine.h"
#include "ParentEngine.h"
#include "ParentStarEngine.h"
#include "UsesEngine.h"


using namespace std;

class QueryValidator{

public:
	QueryValidator(QueryManager *qm, PKB *p);
	~QueryValidator(void);

	bool processInputQuery(string inputQuery);
	bool processSelectQuery(string inputQuery);

private:
	void initCheckingVectors();
	bool identifyRelationship(std::string unkRelationship, std::string firstParam, std::string secondParam);
	pair<std::string, std::string> processParameters(std::string firstParam, std::string secondParam);
	bool replaceSubstring(std::string& inputString, const std::string& replaceTarget, const std::string& replaceValue);
	VARIABLETYPE identifyVariableType(std::string unkVarType);
	std::string getRawVariableType(std::string varName);
	std::string preprocessInput(string input);
	bool is_number(const std::string& s);
	
	std::vector<std::string> queryClauses;
	std::vector<std::string> designEntities;
	std::vector<std::string> queryTypes;
	vector< pair<std::string, std::string> > varList;
	//vector< vector<QueryClass> > qcRelationships;
	vector<QueryClass> qcRelationships;
	QueryManager *queryManager;
	PKB *pkb;

};