#include "QueryManager.h"

void QueryManager::updateRelationship(const string &variable1, const string &variable2, 
	const vector<pair<string, string>> &relationship) {		

		listManager->updateList(variable1, variable2, relationship);

}

string QueryManager::getVariableType(const string &variableName) {

	ASTParameterValue &asp = getASTParameterValue(variableName);		  	
	if (asp.getASTParameter().getParameterType() == VT_WHILE || 
		asp.getASTParameter().getParameterType() == VT_ASSIGNMENT || 
		asp.getASTParameter().getParameterType() == VT_IF || 
		asp.getASTParameter().getParameterType() == VT_STATEMENTLIST || 
		asp.getASTParameter().getParameterType() == VT_CALL||
		asp.getASTParameter().getParameterType() == VT_PROG_LINE ||
		asp.getASTParameter().getParameterType() == VT_CONSTANT 
		)
		return "integer";
	else
		return "string";

}

void QueryManager::updateRelationship(const string &variable, 	  const vector<string> &relationship) {		
	listManager->updateList(variable, relationship);
}

void QueryManager::execute() { // multithreading 

	while (!qt.isEmpty()) {
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
	listManager = new ListManager(this);	
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
	/*ASTParameterValue &astParamValue = getASTParameterValue(variableName);
	astParamValue.setValueList(vectorString);*/
}

void QueryManager::updateVectorInteger(string variableName, vector<int> &vectorString) {
	/*ASTParameterValue &astParamValue = getASTParameterValue(variableName);
	astParamValue.setValueListInteger (vectorString);*/
}

vector<int> QueryManager::getAllList(ASTType asttype) {
	return pkbLibrary->getAST()->getStatementNumbers(asttype);		
}
vector<string> QueryManager::getValueList(string variableName)  {    	
	ASTParameterValue &astParamValue = getASTParameterValue(variableName);
	// will create an intermediate called cache manager that will store all the information sorted 
	// instead of just returning vector
	if (astParamValue.hasNotInitialized()) {
		astParamValue.initialize(pkbLibrary);
		return astParamValue.getValueList();
	} else
		return listManager->getValueListString(variableName);

	
}


vector<string> QueryManager::getAllVariable() {
	return pkbLibrary->getVarTable()->getAllNames();
}
vector<int> QueryManager::getValueListInteger(string variableName)  {    	
	ASTParameterValue &astParamValue = getASTParameterValue(variableName);
	// will create an intermediate called cache manager that will store all the information sorted 
	// instead of just returning vector
	if (astParamValue.hasNotInitialized()) {
		astParamValue.initialize(pkbLibrary);
		return astParamValue.getValueListInteger();	
	}else		
		return listManager->getValueListInteger(variableName);
}

FastSearchInteger QueryManager::getValueListIntegerMap(string variableName)  {    	
	ASTParameterValue &astParamValue = getASTParameterValue(variableName);
	// will create an intermediate called cache manager that will store all the information sorted 
	// instead of just returning vector
	if (astParamValue.hasNotInitialized()) {
		astParamValue.initialize(pkbLibrary);
		return astParamValue.getValueListIntegerMap();	
	}else		{
		FastSearchInteger result;
		listManager->getValueListMapInteger(variableName, result);
		return result;		
	}
}


FastSearchString QueryManager::getValueListMap(string variableName)  {    	
	ASTParameterValue &astParamValue = getASTParameterValue(variableName);
	// will create an intermediate called cache manager that will store all the information sorted 
	// instead of just returning vector
	if (astParamValue.hasNotInitialized()) {
		astParamValue.initialize(pkbLibrary);
		return astParamValue.getValueListMap();	
	}else {
		FastSearchString result;
		listManager->getValueListMapString(variableName, result);
		return result;	
	}
}


const vector<int> &QueryManager::getAllStatementList() {

	if (myAllList.size() ==0) 
		for (int i = 1; i <= pkbLibrary->getNumOfStmt(); i++) 
			myAllList.push_back(i);		

	return myAllList;
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
	expressionValueList.clear();

//	pkbLibrary->getAffects()->clearCache();

	resultList.clear();
	qt.clear();
	listManager->clear();
	failed = false;
}

void QueryManager::addResultExpression(string variableName) {
	// validation to make sure the variableName is there. 
	resultList.push_back(variableName);
}

list<string> QueryManager::outputResult() {

	// assume only one query

	list<string> returnList;
	if (resultList.size() == 0 )  {
		if (failed)
			returnList.push_back("false");
		else 
			returnList.push_back("true");
	  return returnList;
	}

	string variableName = resultList.front();

	if (variableName.compare("BOOLEAN") == 0) { //HACK  {
		if (failed){
			returnList.push_back("false");
		} else 
			returnList.push_back("true");
		return returnList;
	}  else if (failed) {
		return returnList;
	}

	
	listManager->prepareResultList(returnList, resultList);

	return returnList;
} // has re



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
