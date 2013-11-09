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
#include "NextStarEngine.h"
#include "ParentEngine.h"
#include "ParentStarEngine.h"
#include "UsesEngine.h"
#include "ExpressionPattern.h"
#include "BinaryRelationEngine.h"
#include "IfPattern.h"
#include "WhilePattern.h"
#include "CallEngine.h"
#include "CallStarEngine.h"
#include "AffectEngine.h"
#include "AffectStarEngine.h"


//testing
#include "Parser.h"
#include "DesignExtractor.h"
#include "QueryTree.h"
#include <map>

using namespace std;

class QueryValidator{

public:
	QueryValidator(QueryManager *qm, PKB *p);
	~QueryValidator(void);

	bool processQuery(string inputQuery);
	
private:
	string preprocessInput(string input);
	void initCheckingTables();
	void initQueryClauseTable();
	void initDesignEntityTable();
	void initQueryTypeTable();

	//General Functions
	bool replaceSubstring(string& inputString, const string& replaceTarget, const string& replaceValue);
	bool is_number(const string& s);
	bool processDeclarationStmt(string declarationStmt);
	bool processSelectStmt(string selectStmt);
	bool processQueryClauses(vector<string> queryClauses);
	bool processPatternClauses(vector<string> patternClauses);
	string getRawVariableType(string variableName);
	pair<vector<string>, vector<string>> getAllowableParaType(string entityType);
	bool paraTypeAllowed(vector<string> allowedParameterTypes, string paraType);
	VARIABLETYPE getVariableType(std::string unkVarType);
	bool addToQueryManager(vector < pair<string, pair<string, string>>> clausesList);
	bool getValidReturnResultType(string returnResultVariable);

	//Variables
	vector<string> tblQueryClauses, tblDesignEntities;
	vector< pair<string, pair<vector<string>, vector<string>>>> tblQueryTypes;
	vector < pair<string, pair<string, string>>> entityList;
	vector< pair<string, string> > varList;

	QueryManager *queryManager;
	PKB *pkb;
};