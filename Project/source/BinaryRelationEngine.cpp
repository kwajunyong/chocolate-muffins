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


	map<string, bool> secondList;
	map<string, bool> firstList;

	vector<string>::iterator iterFirst, iterSecond;
	vector<pair<string, string>> relationship;
	bool keepRelation = keepRelationship();
	bool exist;
	for (iterFirst = first.begin(); iterFirst != first.end(); iterFirst++){
		exist = false;
		for (iterSecond = second.begin(); iterSecond != second.end(); iterSecond++) {

			if (iterFirst->compare(*iterSecond) == 0 )   {
				if (keepRelation) 
					relationship.push_back(VectorRelation(*iterFirst, *iterSecond));					

				exist = true;
				if (!keepRelation && astParam2->updateAble()) 
					secondList[*iterSecond] = true;
				else {
					break;
				}
			}
		}

		if (exist && !keepRelation && astParam1->updateAble()) 
			firstList[*iterFirst] = true;

	}

	if (keepRelation) {
		myQM->updateRelationship(astParam1->getVariableName(), astParam2->getVariableName(), relationship);
	} else if (astParam1->updateAble()) {
		vector<string> result ;
		CommonUtility::convertVector(firstList, result);
		myQM->updateRelationship(astParam1->getVariableName(), result);

	} else if (astParam2->updateAble()) {
		vector<string> result ;
		CommonUtility::convertVector(secondList, result);
		myQM->updateRelationship(astParam2->getVariableName(), result);
	}


}

