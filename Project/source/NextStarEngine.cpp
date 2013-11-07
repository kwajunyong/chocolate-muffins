#include "NextStarEngine.h"
#include "QueryManager.h"
#include <fstream>

NextStarEngine::NextStarEngine(QueryManager* qm, PKB *pkb) : QueryClass(QT_NEXTSTAR, qm, pkb){


}

bool NextStarEngine::sameVariable() {
	// no need to check underscore 

	return parameterList.at(0)->getVariableName().compare(parameterList.at(1)->getVariableName()) == 0 
		&&  parameterList.at(0)->getParameterType() == parameterList.at(1)->getParameterType()  
		&& parameterList.at(0)->getParameterType() != VT_CONSTANTINTEGER;

}
void NextStarEngine::run() {

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







	FastSearchString finalListOne;
	FastSearchString finalListTwo; 
	FastSearchInteger::iterator iter;
	vector<int>::const_iterator iterParentList;
	FastSearchInteger::iterator iterSecond;



	bool exist;
	bool keepRelationship = astParam1->updateAble() && astParam2->updateAble() ;

	vector<pair<string, string>> resultList;


	if (astParam1->getParameterType() == VT_UNDERSCORE) {
		CommonUtility::convertToMap(myQM->getAllStatementList(), first);
	}else{
		loadVariable(0, first);
	}

	// BOTH SAME VARIABLE ============================================================================
	if (sameVariable()) {
		for (iter = first.begin();  iter != first.end(); iter++) { 
			if (pkbManager->getNext()->isNext(iter->first, iter->first, true)) 
				finalListOne[CommonUtility::NumberToString(iter->first)] = true;

		}
		keepRelationship = false; // prevent unwanted update
	} else { // BOTH SAME VARIABLE END==================================================================


		if (astParam2->getParameterType() == VT_UNDERSCORE) 
			CommonUtility::convertToMap(myQM->getAllStatementList(), second);
		else 
			loadVariable(1, second);




		if (first.size() < second.size()) {

			for (iter = first.begin();  iter != first.end(); iter++) { // for every statement find the modified value

				vector<int> &childList = pkbManager->getNext()->getNext(iter->first, true);
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
		} else  {
			for (iterSecond = second.begin();  iterSecond != second.end(); iterSecond++) { // for every statement find the modified value

				vector<int> &childList = pkbManager->getNext()->getPrevious(iterSecond->first, true);
				exist = false;

				for (iterParentList = childList.begin(); iterParentList  != childList.end(); iterParentList++) { // for each variable returned check against the variable list
					iter = first.find(*iterParentList);

					if (iter != first.end()) {
						exist = true;

						if (keepRelationship)
							resultList.push_back(pair<string, string>(CommonUtility::NumberToString(iter->first), CommonUtility::NumberToString(iterSecond->first)));					
						else if (astParam1->updateAble()) 
							finalListOne[CommonUtility::NumberToString(iter->first)] = true;
						else if (!astParam1->updateAble()) {
							return; // both are not updatable. 
						}								
					}
				}

				if (exist && !keepRelationship && astParam2->updateAble()) 
					finalListTwo[CommonUtility::NumberToString(iterSecond->first)] = true;

			}
		}

	}  // NOT SAME VARIABLE

	updateVariable(resultList, finalListOne, finalListTwo, keepRelationship);


	failed = (finalListOne.size() == 0 && finalListTwo.size() == 0 && resultList.size() == 0);

}





