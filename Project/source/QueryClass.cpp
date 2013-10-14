#include "QueryClass.h"
#include "PKB.h"
#include "CommonUtility.h"
#include "QueryManager.h"

//QueryClass *QueryClass::instantiate() {
//
//}

// DON'T HANDLE UNDERSCORE
void QueryClass::loadVariable(int paramIndex, FastSearchString &varList) {
	if (parameterList.at(paramIndex)->getParameterType() == VT_CONSTANTSTRING) 
		varList[parameterList.at(paramIndex)->getVariableName()] = true;
	else
		varList = myQM->getValueListMap(parameterList.at(paramIndex)->getVariableName());	
}

// DON'T HANDLE UNDERSCORE
void QueryClass::loadVariable(int paramIndex, FastSearchInteger &varList) {

	if (parameterList.at(paramIndex)->getParameterType() == VT_CONSTANTSTRING) 
		varList[atoi(parameterList.at(paramIndex)->getVariableName().c_str())] = true;
	else
		varList = myQM->getValueListIntegerMap(parameterList.at(paramIndex)->getVariableName());
}

bool QueryClass::keepRelationship() {

	ASTParameter *astParam1 = parameterList.at(0);
	ASTParameter *astParam2 = parameterList.at(1);	

	return astParam1->updateAble() && astParam2->updateAble();
}


QueryClass::QueryClass () {
}
QueryClass::QueryClass(QUERYTYPE queryType, QueryManager* qm, PKB *pkb) {
	myQueryType = queryType;
	myQM = qm;	
	pkbManager = pkb;
	failed = false;
}

void QueryClass::run() {
	 cout << "Dummy";
}
QueryManager* QueryClass::getQueryManager() {
  return myQM;
}
vector<ASTParameter*> &QueryClass::getParameterList() {
	return parameterList;
}

void QueryClass::addParam(const string &parameterName, VARIABLETYPE parameterType) {
	// validation goes here
	ASTParameter* astParameter = new ASTParameter(parameterName, parameterType);
	parameterList.push_back(astParameter);
}

void QueryClass::addParam(const string &parameterName, VARIABLETYPE parameterType, const string &attribute) {
	cout << "Implement in children";
}




bool QueryClass::hasResult() {
	return !failed;
}
