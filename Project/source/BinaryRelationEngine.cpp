#include "BinaryRelationEngine.h"
#include "QueryManager.h"
// jy written
// give proc get line
//pkbManager->getCalls()->getCallsStmt("hahah");
// give line get proc
//pkbManager->getAST()->getCalledProcedure(2);
BinaryRelationEngine::BinaryRelationEngine(QueryManager* qm, PKB *pkb) : QueryClass(QT_BINARYRELATION, qm, pkb){


}

void BinaryRelationEngine::addParam(const string &parameterName, VARIABLETYPE parameterType) {
	QueryClass::addParam(parameterName, parameterType);	
	attributePair.push_back("");
}

void BinaryRelationEngine::addParam(const string &parameterName, VARIABLETYPE parameterType, const string &attribute) {
	QueryClass::addParam(parameterName, parameterType);

	attributePair.push_back(attribute);
}

void BinaryRelationEngine::handleCall(vector<string> &first, vector<string> &second) {

	ASTParameter *astParam1 = parameterList.at(0);
	ASTParameter *astParam2 = parameterList.at(1);	
	vector<pair<string, string>> relationship;
	bool keepRelation  = keepRelationship();
	FastSearchString result1; 
	FastSearchString result2; 

	if (astParam1->getParameterType() == VT_CALL) {
		if (astParam2->getParameterType() == VT_CALL) {					
			FastSearchInteger secondMap  = myQM->getValueListIntegerMap(astParam2->getVariableName());
			FastSearchInteger::iterator iterSecond;
			vector<string>::iterator iter;

			for (iter = first.begin(); iter != first.end(); iter++) {

				string procedure = pkbManager->getAST()->getCalledProcedure(atoi(iter->c_str())); // called what procedure
				vector<int> stmtList = pkbManager->getCalls()->getCallsStmt(procedure); // get call statement list of that procedure
				vector<int>::iterator iterStmtList;

				for (iterStmtList = stmtList.begin(); iterStmtList != stmtList.end(); iterStmtList++) {
					iterSecond = secondMap.find(*iterStmtList); // check if it's exists
					if (iterSecond != secondMap.end()) { 
						relationship.push_back(pair<string, string>(*iter, CommonUtility::NumberToString(iterSecond->first)));
					}
				}												
			}

		} else {// first one VT CALL second not VT_CALL

			vector<string>::iterator iter;
			FastSearchString::iterator iterFound;
			FastSearchString secondMap;
			CommonUtility::convertToMap(second, secondMap);

			bool exist;
			for (iter = first.begin(); iter != first.end(); iter++) {

				string procedure = pkbManager->getAST()->getCalledProcedure(atoi(iter->c_str()));
				exist = false;
				iterFound = secondMap.find(procedure) ;
				if (iterFound != secondMap.end()){
					exist = true;
					if (keepRelation) 
						relationship.push_back(pair<string, string>(*iter, iterFound->first));

				}


				if (exist & !keepRelation) 
					result1[*iter] = true;
			}
		}
	} else if (astParam2->getParameterType() == VT_CALL) { // second VT_CALL
			vector<string>::iterator iter;
			FastSearchString::iterator iterFound;
			FastSearchString firstMap;
			CommonUtility::convertToMap(first, firstMap);

			bool exist;
			for (iter = second.begin(); iter != second.end(); iter++) {

				string procedure = pkbManager->getAST()->getCalledProcedure(atoi(iter->c_str()));
				exist = false;
				iterFound = firstMap.find(procedure) ;
				if (iterFound != firstMap.end()){
					exist = true;
					if (keepRelation) 
						relationship.push_back(pair<string, string>(iterFound->first, *iter));

				}


				if (exist & !keepRelation) 
					result2[*iter] = true;
			}
	}

	updateVariable(relationship, result1, result2, keepRelation);

	failed = (result1.size() == 0 && result2.size() == 0 && relationship.size() == 0);

}

void BinaryRelationEngine::run() {	
	// handle call differently

	ASTParameter *astParam1 = parameterList.at(0);
	ASTParameter *astParam2 = parameterList.at(1);	

	vector<string> first;

	if (astParam1->getParameterType() == VT_CONSTANTSTRING 
		||astParam1->getParameterType() == VT_CONSTANTINTEGER) {
			first.push_back(astParam1->getVariableName());
	} else if (myQM->getVariableType(astParam1->getVariableName()).compare("integer") == 0) {
		CommonUtility::convertIntVectorToString(myQM->getValueListInteger (astParam1->getVariableName()), first);
	} else {
		first = myQM->getValueList(astParam1->getVariableName());
	}

	vector<string> second;

	if (astParam2->getParameterType() == VT_CONSTANTSTRING 
		||astParam2->getParameterType() == VT_CONSTANTINTEGER) {
			second.push_back(astParam2->getVariableName());
	} else if (myQM->getVariableType(astParam2->getVariableName()).compare("integer") == 0){
		CommonUtility::convertIntVectorToString(myQM->getValueListInteger (astParam2->getVariableName()), second);
	} else {
		second= myQM->getValueList(astParam2->getVariableName());
	}

	if (astParam1->getParameterType() == VT_CALL ||
		astParam2->getParameterType() == VT_CALL) {
			handleCall(first, second);
			return;
	}


	FastSearchString secondList;
	FastSearchString firstList;




	vector<pair<string, string>> relationship;

	bool keepRelation = keepRelationship();
	bool exist;

	if (first.size() < second.size()) {
		vector<string>::iterator iterFirst;

		FastSearchString secondFast;
		CommonUtility::convertToMap(second, secondFast);

		for (iterFirst = first.begin(); iterFirst != first.end(); iterFirst++){
			exist = false;
			if (secondFast.find(*iterFirst) != secondFast.end() ) {
				exist = true;

				if (keepRelation) 
					relationship.push_back(VectorRelation(*iterFirst, *iterFirst));		// they are the same. make no mistake here
				else if (astParam2->updateAble()) 
					secondList[*iterFirst] = true;
				else if (!astParam1->updateAble()) 
					return; // we have got what we come for. 
			}

			if (exist && !keepRelation && astParam1->updateAble()) 
				firstList[*iterFirst] = true;
		}
	} else {
		vector<string>::iterator iterSecond;

		FastSearchString firstFast;
		CommonUtility::convertToMap(first, firstFast);

		for (iterSecond = second.begin(); iterSecond != second.end(); iterSecond++){
			exist = false;
			if (firstFast.find(*iterSecond) != firstFast.end() ) {
				exist = true;

				if (keepRelation) 
					relationship.push_back(VectorRelation(*iterSecond, *iterSecond));		// they are the same. make no mistake here
				else if (astParam1->updateAble()) 
					firstList[*iterSecond] = true;
				else if (!astParam1->updateAble()) 
					return; // we have got what we come for. 
			}

			if (exist && !keepRelation && astParam2->updateAble()) 
				secondList[*iterSecond] = true;
		}
	}

	updateVariable( relationship, firstList, secondList, keepRelation);

	failed = (firstList.size() == 0 && secondList.size() == 0 && relationship.size() == 0);



}

