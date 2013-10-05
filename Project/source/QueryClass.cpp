#include "QueryClass.h"
#include "PKB.h"
#include "CommonUtility.h"
//QueryClass *QueryClass::instantiate() {
//
//}

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


void QueryClass::convertVector(const map<string, int> & mapList, vector<string>& resultList ) {
	map<string, int>::const_iterator mapIterator;
	
	for (mapIterator = mapList.begin(); mapIterator != mapList.end(); mapIterator++) {
		resultList.push_back(mapIterator->first);
	}
}

bool QueryClass::hasResult() {
	return !failed;
}

void QueryClass::convertVector(const map<int, int> & mapList, vector<int>& resultList ) {
	map<int, int>::const_iterator mapIterator;
	
	for (mapIterator = mapList.begin(); mapIterator != mapList.end(); mapIterator++) {
		resultList.push_back(mapIterator->first);
	}
}


void QueryClass::convertVector(const map<int, int> & mapList, vector<string>& resultList ) {
	map<int, int>::const_iterator mapIterator;
	
	for (mapIterator = mapList.begin(); mapIterator != mapList.end(); mapIterator++) {
		resultList.push_back(NumberToString(mapIterator->first));
	}
}
