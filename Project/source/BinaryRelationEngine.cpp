#include "BinaryRelationEngine.h"
#include "QueryManager.h"

BinaryRelationEngine::BinaryRelationEngine(QueryManager* qm, PKB *pkb) : QueryClass(QT_MODIFIES, qm, pkb){


}

void BinaryRelationEngine::addParam(const string &parameterName, VARIABLETYPE parameterType) {
	QueryClass::addParam(parameterName, parameterType);	
	attributePair.push_back("");
}

void BinaryRelationEngine::addParam(const string &parameterName, VARIABLETYPE parameterType, const string &attribute) {
	QueryClass::addParam(parameterName, parameterType);
	
	attributePair.push_back(attribute);
}
void BinaryRelationEngine::run() {
	
	ASTParameter *astParam1 = parameterList.at(0);
	ASTParameter *astParam2 = parameterList.at(1);	

	vector<string> first;
	vector<int> callList;
	if (astParam1->getParameterType() == VT_CONSTANTSTRING 
		   ||astParam1->getParameterType() == VT_CONSTANTINTEGER) {
			   first.push_back(astParam1->getVariableName());
	} else  if (astParam1->getParameterType() == VT_CONSTANT) {	
		//first = pkbManager->
	} else if (astParam1->getParameterType() == VT_CALL) {
		// call 
		//callList = pkbManager->getCalls()->
	} else if (astParam1->getParameterType() == VT_STATEMENTLIST) {
		CommonUtility::convertIntVectorToString(myQM->getAllStatementList(), first);
	} else {
		first = myQM->getValueList(astParam1->getVariableName());
	}

	vector<string> second;
	
	if (astParam1->getParameterType() == VT_CONSTANTSTRING 
		   ||astParam1->getParameterType() == VT_CONSTANTINTEGER) {
			   second.push_back(astParam1->getVariableName());
	} else  if (astParam1->getParameterType() == VT_CONSTANT) {	
		//first = pkbManager->
	} else if (astParam1->getParameterType() == VT_CALL) {
		// call 
	} else if (astParam1->getParameterType() == VT_STATEMENTLIST) {
		CommonUtility::convertIntVectorToString(myQM->getValueListInteger(astParam1->getVariableName()), second);
	} else {
		second= myQM->getValueList(astParam1->getVariableName());
	}


	vector<string>::iterator iterFirst, iterSecond;
	vector<pair<string, string>> relationship;
	bool keepRelation = keepRelationship();
	for (iterFirst = first.begin(); iterFirst != first.end(); iterFirst++){
		for (iterSecond = second.begin(); iterSecond != second.end(); iterSecond++) {

			if (iterFirst->compare(*iterSecond))  
				if (keepRelation) 
					relationship.push_back(VectorRelation(*iterFirst, *iterSecond));					
		}
	}


}

