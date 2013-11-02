#include "NextEngine.h"
#include "QueryManager.h"

NextEngine::NextEngine(QueryManager* qm, PKB *pkb) : QueryClass(QT_MODIFIES, qm, pkb){


}
void NextEngine::run() {
	

	// if it's procedure and variable combination
	ASTParameter *astParam1 = parameterList.at(0);
	ASTParameter *astParam2 = parameterList.at(1);	

	FastSearchInteger second;
	FastSearchInteger first;

	// there is no need to check if both is underscore
	if (astParam1->getParameterType() == VT_UNDERSCORE && astParam2->getParameterType() == VT_UNDERSCORE) {
		/*if (pkbManager->getFollows()->IsThereFollow) 
		failed = false;
		else
		failed true;*/

		return;
	}



	if (astParam1->getParameterType() == VT_CONSTANTINTEGER) {
		first[atoi(astParam1->getVariableName().c_str())] = true;
	} else if (astParam1->getParameterType() == VT_UNDERSCORE) {
		CommonUtility::convertToMap(myQM->getAllStatementList(), first);
	}else{
		first = myQM->getValueListIntegerMap(astParam1->getVariableName());
	}


	if (astParam2->getParameterType() == VT_CONSTANTINTEGER) {
		second[atoi(astParam2->getVariableName().c_str())] = true;
	} else if (astParam2->getParameterType() == VT_UNDERSCORE) {
		CommonUtility::convertToMap(myQM->getAllStatementList(), second);
	}	else {
		second = myQM->getValueListIntegerMap(astParam2->getVariableName());
	}


	FastSearchString finalListOne;
	FastSearchString finalListTwo; 

	FastSearchInteger::iterator iter;
	vector<int>::const_iterator iterParentList;
	FastSearchInteger::iterator iterSecond;

	bool exist;
	bool keepRelationship = astParam1->updateAble() && astParam2->updateAble() ;

	vector<pair<string, string>> resultList;

	for (iter = first.begin();  iter != first.end(); iter++) { // for every statement find the modified value

		vector<int> &childList = pkbManager->getNext()->getNext(iter->first, false);
		exist = false;

		for (iterParentList = childList.begin(); iterParentList  != childList.end(); iterParentList++) { // for each variable returned check against the variable list
			iterSecond = second.find(*iterParentList);

			if (iterSecond != second.end()) {
				exist = true;

				if (keepRelationship)
					resultList.push_back(pair<string, string>(CommonUtility::NumberToString(iter->first), CommonUtility::NumberToString(iterSecond->first)));					
				else if (astParam2->updateAble()) 
					finalListTwo[CommonUtility::NumberToString(iterSecond->first)] = true;
				else if (!astParam1->updateAble()) {
					return; // both are not updatable. 
				}								
			}
		}
		if (exist && !keepRelationship && astParam1->updateAble()) 
			finalListOne[CommonUtility::NumberToString(iter->first)] = true;


	}


	if (keepRelationship) {
		myQM->updateRelationship(astParam1->getVariableName(), astParam2->getVariableName(), resultList);
	} else if (astParam1->updateAble()) {
		myQM->updateRelationship(astParam1->getVariableName(), finalListOne);
	} else if (astParam2->updateAble()) {
		myQM->updateRelationship(astParam2->getVariableName(), finalListTwo);
	}

	failed = (finalListOne.size() == 0 && finalListTwo.size() == 0 && resultList.size() == 0);

}