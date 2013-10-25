#include "BinaryRelationEngine.h"
#include "QueryManager.h"
// jy written
// give proc get line
//pkbManager->getCalls()->getCallsStmt("hahah");
// give line get proc
//pkbManager->getAST()->getCalledProcedure(2);
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

				string procedure = pkbManager->getAST()->getCalledProcedure(atoi(iter->c_str()));
				vector<int> stmtList = pkbManager->getCalls()->getCallsStmt(procedure);
				vector<int>::iterator iterStmtList;

				for (iterStmtList = stmtList.begin(); iterStmtList != stmtList.end(); iterStmtList++) {
					iterSecond = secondMap.find(*iterStmtList);
					if (iterSecond != secondMap.end()) { 
						relationship.push_back(pair<string, string>(*iter, CommonUtility::NumberToString(iterSecond->first)));
					}
				}												
			}

		} else {

			FastSearchInteger::iterator iterSecond;
			vector<string>::iterator iter;
			vector<string>::iterator iterSecond2;
			bool exist;
			for (iter = first.begin(); iter != first.end(); iter++) {

				string procedure = pkbManager->getAST()->getCalledProcedure(atoi(iter->c_str()));
				vector<int> stmtList = pkbManager->getCalls()->getCallsStmt(procedure);
				vector<int>::iterator iterStmtList;

				for (iterStmtList = stmtList.begin(); iterStmtList != stmtList.end(); iterStmtList++) {
					exist = false;
					for (iterSecond2 = second.begin(); iterSecond2 != second.end(); iterSecond2++) {
						if (*iterStmtList ==  atoi(iterSecond2->c_str())) {
							exist =true;
							if (keepRelation) {
								relationship.push_back(pair<string, string>(*iter, CommonUtility::NumberToString(iterSecond->first)));
							}else  if (!astParam2->updateAble()) {								
								break;
							}
						}
					}

				}

				if (exist & !keepRelation) 
					result1[*iter] = true;
			}
		}
	} else if (astParam2->getParameterType() == VT_CALL) {

		FastSearchInteger::iterator iterSecond;
		vector<string>::iterator iter;
		vector<string>::iterator iterSecond2;
		bool exist;
		for (iter = second.begin(); iter != second.end(); iter++) {

			string procedure = pkbManager->getAST()->getCalledProcedure(atoi(iter->c_str()));
			vector<int> stmtList = pkbManager->getCalls()->getCallsStmt(procedure);
			vector<int>::iterator iterStmtList;

			for (iterStmtList = stmtList.begin(); iterStmtList != stmtList.end(); iterStmtList++) {
				exist = false;
				for (iterSecond2 = first.begin(); iterSecond2 != first.end(); iterSecond2++) {
					if (*iterStmtList ==  atoi(iterSecond2->c_str())) {
						exist =true;
						if (keepRelation) {
							relationship.push_back(pair<string, string>(CommonUtility::NumberToString(iterSecond->first), *iter));
						}else  if (!astParam1->updateAble()) {								
							break;
						}
					}
				}

			}

			if (exist & !keepRelation) 
				result2[*iter] = true;
		}
	}
	if (keepRelation) {
		myQM->updateRelationship(astParam1->getVariableName(), astParam2->getVariableName(), relationship);
	} else if (astParam1->updateAble()) {
		vector<string> result ;
		CommonUtility::convertVector(result1, result);
		myQM->updateRelationship(astParam1->getVariableName(), result);

	} else if (astParam2->updateAble()) {
		vector<string> result ;
		CommonUtility::convertVector(result2, result);
		myQM->updateRelationship(astParam2->getVariableName(), result);
	}

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

	failed = (firstList.size() == 0 && secondList.size() == 0 && relationship.size() == 0);



}

