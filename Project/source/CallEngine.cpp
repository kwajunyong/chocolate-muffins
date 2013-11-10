#include "CallEngine.h"
#include "QueryManager.h"
#include "CommonUtility.h"

CallEngine::CallEngine(QueryManager* qm, PKB *pkb) : QueryClass(QT_CALLS, qm, pkb){


}
void CallEngine::run() {


	// if it's procedure and variable combination
	ASTParameter *astParam1 = parameterList.at(0);
	ASTParameter *astParam2 = parameterList.at(1);	

	FastSearchString second;
	FastSearchString first;

	// there is no need to check if both is underscore
	if (astParam1->getParameterType() == VT_UNDERSCORE && astParam2->getParameterType() == VT_UNDERSCORE) {
	
		failed = !pkbManager->getCalls()->exists();
		return;
	}

	// A call cannnot call itself
	if (astParam1->getParameterType() == astParam2->getParameterType() 
		&& astParam1->getVariableName().compare(astParam2->getVariableName()) == 0) {
			failed = true;
			return;
	}


	if (astParam1->getParameterType() == VT_UNDERSCORE) 
		CommonUtility::convertToMap(pkbManager->getProcTable()->getAllNames(), first);
	else
		loadVariable(0, first);


	if (astParam2->getParameterType() == VT_UNDERSCORE) {
		CommonUtility::convertToMap(pkbManager->getProcTable()->getAllNames(), second);
	}else
		loadVariable(1, second);


	FastSearchString finalListOne;
	FastSearchString finalListTwo; 

	FastSearchString ::iterator iter;
	vector<string>::const_iterator iterParentList;
	FastSearchString::iterator iterSecond;

	bool exist;
	bool keepRelationship = astParam1->updateAble() && astParam2->updateAble() ;

	vector<pair<string, string>> resultList;

	if (first.size() < second.size()) {
		for (iter = first.begin();  iter != first.end(); iter++) { // for every statement find the modified value
			vector<string> &childList = pkbManager->getCalls()->getCalls(iter->first, false);
			exist = false;

			for (iterParentList = childList.begin(); iterParentList  != childList.end(); iterParentList++) { // for each variable returned check against the variable list
				iterSecond = second.find(*iterParentList);

				if (iterSecond != second.end()) {
					exist = true;

					if (keepRelationship)
						resultList.push_back(pair<string, string>(iter->first, iterSecond->first));					
					else if (astParam2->updateAble()) 
						finalListTwo[iterSecond->first] = true;
					else if (!astParam1->updateAble()) {
						return; // both are not updatable. 
					}								
				}
			}
			if (exist && !keepRelationship && astParam1->updateAble()) 
				finalListOne[iter->first] = true;

		}
	} else {

		for (iter = second.begin();  iter != second.end(); iter++) { // for every statement find the modified value
			vector<string> &childList = pkbManager->getCalls()->getCalled(iter->first, false);
			exist = false;

			for (iterParentList = childList.begin(); iterParentList  != childList.end(); iterParentList++) { // for each variable returned check against the variable list

				iterSecond = first.find(*iterParentList);

				if (iterSecond != first.end()) {
					exist = true;

					if (keepRelationship)
						resultList.push_back(pair<string, string>(iterSecond->first, iter->first));					
					else if (astParam1->updateAble()) 
						finalListOne[iterSecond->first] = true;
					else if (!astParam2->updateAble()) 
						return; // both are not updatable. 
												
				}
			}
			if (exist && !keepRelationship && astParam2->updateAble()) 
				finalListTwo[iter->first] = true;

		}
	}


	updateVariable(resultList, finalListOne, finalListTwo, keepRelationship);

	failed = (finalListOne.size() == 0 && finalListTwo.size() == 0 && resultList.size() == 0);




}