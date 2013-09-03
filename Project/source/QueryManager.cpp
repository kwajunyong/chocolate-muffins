#include "QueryManager.h"

void QueryManager::execute() { // multithreading 

	if (!qt.isEmpty()) {
		QueryClass *qc = qt.pop();
		qc->run();

		if (!qc->hasResult()) {
			failed=true;
			return;
		}
		delete qc;

	}
}
QueryManager::QueryManager(PKB *pkb) {
	pkbLibrary = pkb;
	failed = false;
}
void QueryManager::addExpression(VARIABLETYPE variableType, string variableName) {
	ASTParameter param(variableName, variableType);		
	ASTParameterValue paramValue(param);

	expressionValueList[variableName] = paramValue;
}

ASTParameterValue &QueryManager::getASTParameterValue(string variableName) {
	map<string, ASTParameterValue>::iterator iter;
	iter = expressionValueList.find(variableName);
	if (iter == expressionValueList.end()) {
		throw exception("Expression not found");
	}	
	return iter->second;
}; 

void QueryManager::addQueryClass(QueryClass* qc)  {
	qt.addQueryClass(qc);
}

void QueryManager::updateVector(string variableName, vector<string> &vectorString) {
	ASTParameterValue &astParamValue = getASTParameterValue(variableName);
	astParamValue.setValueList(vectorString);
}

void QueryManager::updateVectorInteger(string variableName, vector<int> &vectorString) {
	ASTParameterValue &astParamValue = getASTParameterValue(variableName);
	astParamValue.setValueListInteger (vectorString);
}

const vector<string>& QueryManager::getValueList(string variableName)  {    	
	ASTParameterValue &astParamValue = getASTParameterValue(variableName);
	// will create an intermediate called cache manager that will store all the information sorted 
	// instead of just returning vector
	if (astParamValue.hasNotInitialized()) 
		astParamValue.initialize(pkbLibrary);

	return astParamValue.getValueList();
}

const vector<int>& QueryManager::getValueListInteger(string variableName)  {    	
	ASTParameterValue &astParamValue = getASTParameterValue(variableName);
	// will create an intermediate called cache manager that will store all the information sorted 
	// instead of just returning vector
	if (astParamValue.hasNotInitialized()) 
		astParamValue.initialize(pkbLibrary);
	return astParamValue.getValueListInteger();
}

// consider removing this. 
void QueryManager::initializeExpression(string variableName) {	
	map<string, ASTParameterValue>::iterator iter;

	iter = expressionValueList.find(variableName);

	if (iter == expressionValueList.end()) {
		throw exception("Expression not found");
	}

	ASTParameterValue &paramValue = iter->second;
	paramValue.initialize(pkbLibrary);
}

bool QueryManager::variableExists(string variableName) {	
	map<string, ASTParameterValue>::iterator iter;

	iter = expressionValueList.find(variableName);
	if (iter == expressionValueList.end()) {
		return false;
	}
	return true;
}



void QueryManager::resetEverything() {
	map<string, ASTParameterValue>::iterator iter;

	for (iter = expressionValueList.begin(); iter != expressionValueList.end(); iter++) {
		iter->second.reset();
	}	
	resultList.clear();
	qt.clear();
}

void QueryManager::addResultExpression(string variableName) {
	// validation to make sure the variableName is there. 

	resultList[variableName] = 1;
}

list<string> QueryManager::outputResult() {

	// assume only one query

	list<string> returnList;
	if (resultList.size() == 0 )  {
		if (failed){
			returnList.push_back("false");
		} else 
			returnList.push_back("true");
	} else {
		ASTParameterValue &astParameterv = getASTParameterValue(resultList.begin()->first);
		ASTParameter &astParam = astParameterv.getASTParameter();

		if (astParam.getParameterType() != VT_PROCEDURE && astParam.getParameterType() != VT_VARIABLELIST) {
			convertVector(astParameterv.getValueListInteger(), returnList);
			
		} else {
			convertVector(astParameterv.getValueList(), returnList);
		}
	}
	return returnList;

}


void QueryManager::convertVector(const vector<int> &from, list<string>& to) {

	vector<int>::const_iterator iterfrom;

	for (iterfrom = from.begin(); iterfrom != from.end(); iterfrom++) {
		to.push_back(NumberToString((*iterfrom)));
	}
}

void QueryManager::convertVector(const vector<string> &from, list<string>& to) {

	vector<string>::const_iterator iterfrom;

	for (iterfrom = from.begin(); iterfrom != from.end(); iterfrom++) {
		to.push_back((*iterfrom));
	}
}

string QueryManager::NumberToString(int pNumber)
{
	ostringstream oOStrStream;
	oOStrStream << pNumber;
	return oOStrStream.str();
}
