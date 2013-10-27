#pragma once
// Query Manager is manager that needs to keep track the variables 
// under Procedure p1, p2; Assign as1, as2;

//Every QueryClass engine will come here to retrieve the variable they need
// maybe need to provide a lock and unlock in order to handle safe multithreading. 

#include "QueryClass.h"
#include "PKB.h"
#include "EnumType.h"
#include "ASTParameterValue.h"
#include <string>
#include <map>
#include <vector>
#include "ASTParameter.h"
#include "QueryTree.h"
#include <list>
#include "ListManager.h"

using namespace std;

class QueryManager {
	
public:	
	vector<int> getAllList(ASTType asttype);

	void execute(); 
	string getVariableType(const string &variableName);

	void addQueryClass(QueryClass *qc); 
	void addExpression(VARIABLETYPE variableType, string variableName);
	void addResultExpression(string variableName);
	list<string> outputResult();

	void resetEverything(); // reset all the expression to be null so that it can be reused again. might not be useful. 
	
	
	const vector<int>& getAllStatementList() ;
	vector<string> getAllVariable() ;

	bool variableExists(string);
	void initializeExpression(string variableName);

	vector<string> getValueList(string) ;
	vector<int> getValueListInteger(string variableName)  ;

	FastSearchString getValueListMap(string variableName);
	FastSearchInteger getValueListIntegerMap(string variableName)  ;

	// after the execution update the vector value. 
	void updateVector(string variableName, vector<string> &vectorString);
	void updateVectorInteger(string variableName, vector<int> &vectorInt);

	void updateRelationship(const string &variable1, const string &variable2, const vector<pair<string, string>> &relationship);
	void updateRelationship(const string &variable, const vector<string> &relationship);
	
	QueryManager(PKB *pkb);

	
	/*QueryManager() {};
	// locking mechanism 
	// locking mechanism uses trusted mechanism, everyone can lock and unlock expression. 
	// if expression is not locked, it can be updated
	string lockExpression(string variableName){}; // future expansion, need to check out the expression to update its variable list 
	 // return a key for use when updating an expression. 
	void updateVector(string variableName, vector<string> &vectorString, string key) {};
	void updateVectorInteger(string variableName, vector<int> &vectorInt, string key) {};
	bool unlockExpression(string variableName){}; // future expansion, need to unlock so that other engine can lock it. 
	// for Youli, this is OS's trick (mutex).	
	// ----------------------------
	*/
		
private:
	//void loadVariable(string variableName) ;
	map<string, ASTParameterValue> expressionValueList;	
	vector<string> resultList;	

	PKB* pkbLibrary;
	ASTParameterValue &getASTParameterValue(string variableName);
	QueryTree qt;
	bool failed;
	void convertVector(const vector<int> &from, list<string>& to);
	void convertVector(const vector<string> &from, list<string>& to);
	string NumberToString(int pNumber);
	ListManager * listManager;
	vector<int> myAllList;
};