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

	if (parameterList.at(paramIndex)->getParameterType() == VT_CONSTANTINTEGER) 
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



void QueryClass::setDebug(bool val) {
	debug = val;
}
bool QueryClass::hasResult() {
	return !failed;
}

void QueryClass::updateVariable(vector<pair<string, string>> &relationship, const FastSearchString &finalListOne, const FastSearchString &finalTwo, const bool &keepRelation){

	if (debug) {

		switch (myQueryType) {
		case QT_AFFECT:
			cout<< "affect";
			break;
		case QT_AFFECTSTAR:
			cout<< "affect star";
			break;
		case QT_NEXT:
			cout<< "next";
			break;
		case QT_NEXTSTAR:
			cout<< "next star";
			break;
		case QT_BINARYRELATION:
			cout<< "binary relation";
			break;
		case QT_CALLS:
			cout<< "call";
			break;
		case QT_CALLSSTAR:
			cout<< "call star";
			break;
		case QT_EXPRESSIONPATTERN:
			cout<< "expression pattern";
			break;
		case QT_FOLLOWS:
			cout<< "follows";

			break;
		case QT_FOLLOWSSTAR:
			cout<< "follows star";
			break;
		case QT_IFPATTERN:
			cout<< "if pattern";
			break;
		case QT_MODIFIES:
			cout<< "modifies";
			break;
		case QT_PARENT:
			cout<< "parent";
			break;
		case QT_PARENTSTAR:
			cout<< "parent star";
			break;
		case QT_USES:
			cout<< "uses ";
			break;
		case QT_WHILEPATTERN:
			cout<< "while pattern";
			break;
		}
		cout << endl;
	}

	if (keepRelation) {
		myQM->updateRelationship(parameterList.at(0)->getVariableName(), parameterList.at(1)->getVariableName(), relationship);

		if (debug) {
			cout <<parameterList.at(0)->getVariableName();
			cout << "\t";
			cout <<parameterList.at(1)->getVariableName();
			cout << endl;
			cout << "========================================================";
			cout << endl;
			vector<pair<string, string>>::iterator iter;			
			for (iter = relationship.begin(); iter != relationship.end(); iter++) {
				cout << iter->first;
				cout << "\t";
				cout << iter->second;
				cout << endl;
			}
		}
	} else if (parameterList.at(0)->updateAble()) {
		myQM->updateRelationship(parameterList.at(0)->getVariableName(), finalListOne);
		if (debug) {
			cout <<parameterList.at(0)->getVariableName();
			cout << endl;
			cout << "========================================================";
			cout << endl;
			FastSearchString::const_iterator iter;			
			for (iter = finalListOne.begin(); iter != finalListOne.end(); iter++) {
				cout << iter->first;
				cout << endl;
			}
		}
	} else if (parameterList.at(1)->updateAble()) {
		myQM->updateRelationship(parameterList.at(1)->getVariableName(), finalTwo);
		if (debug) {
			cout <<parameterList.at(1)->getVariableName();
			cout << endl;
			cout << "========================================================";
			cout << endl;
			FastSearchString::const_iterator iter;			
			for (iter = finalTwo.begin(); iter != finalTwo.end(); iter++) {
				cout << iter->first;
				cout << endl;
			}
		}
	}
}

QUERYTYPE QueryClass::getQueryType() {
	return myQueryType;
}