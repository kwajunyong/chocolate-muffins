#include "FollowsEngine.h"
#include "QueryManager.h"
#include "CommonUtility.h"
FollowsEngine::FollowsEngine(QueryManager* qm, PKB *pkb) : QueryClass(QT_FOLLOWS, qm, pkb){


}
void FollowsEngine::run() {


	// if it's procedure and variable combination
	ASTParameter *astParam1 = parameterList.at(0);
	ASTParameter *astParam2 = parameterList.at(1);	

	FastSearchInteger second;
	FastSearchInteger  first;

	// there is no need to check if both is underscore
	if (astParam1->getParameterType() == VT_UNDERSCORE && astParam2->getParameterType() == VT_UNDERSCORE) {
		/*if (pkbManager->getFollows()->IsThereFollow) 
		failed = false;
		else
		failed true;*/

		return;
	}


	if (astParam1->getParameterType() == VT_UNDERSCORE) 
		CommonUtility::convertToMap(myQM->getAllStatementList(), first);
	else
		loadVariable(0, first);

	if (astParam2->getParameterType() == VT_UNDERSCORE) 
		CommonUtility::convertToMap(myQM->getAllStatementList(), second);
	else
		loadVariable(1, second);



	FastSearchString finalListOne;
	FastSearchString finalListTwo; 

	FastSearchInteger::const_iterator iter;
	vector<int>::const_iterator iterFollowerList;
	FastSearchInteger::const_iterator iterSecond;

	bool exist;
	bool keepRelationship = astParam1->updateAble() && astParam2->updateAble() ;

	vector<pair<string, string>> resultList;

	if (first.size() < second.size()) {

		for (iter = first.begin();  iter != first.end(); iter++) { // for every statement find the modified value
			vector<int> &followerList = pkbManager->getFollows()->getFollowedBy(iter->first, false);
			exist = false;

			for (iterFollowerList = followerList.begin(); iterFollowerList  != followerList.end(); iterFollowerList++) { // for each variable returned check against the variable list
				iterSecond = second.find(*iterFollowerList);
				if (iterSecond != second.end()) {
					exist = true;

					if (keepRelationship)
						resultList.push_back(pair<string, string>(CommonUtility::NumberToString(iter->first), CommonUtility::NumberToString(iterSecond->first)));					
					else if (astParam2->updateAble()) 
						finalListTwo[CommonUtility::NumberToString(iterSecond->first)] = true;
					else if (!astParam1->updateAble()) 
						return; // both are not updatable. 
					


				}
			}
			if (exist && !keepRelationship && astParam1->updateAble()) 
				finalListOne[CommonUtility::NumberToString(iter->first)] = 1;

			
		}
	} else {
		for (iterSecond = second.begin();  iterSecond != second.end(); iterSecond++) { // for every statement find the modified value
			vector<int> &followerList = pkbManager->getFollows()->getFollows(iterSecond->first, false);
			exist = false;

			for (iterFollowerList = followerList.begin(); iterFollowerList  != followerList.end(); iterFollowerList++) { // for each variable returned check against the variable list
				iter = first.find(*iterFollowerList);
				if (iter != first.end()) {
					exist = true;

					if (keepRelationship)
						resultList.push_back(pair<string, string>(CommonUtility::NumberToString(iter->first), CommonUtility::NumberToString(iterSecond->first)));					
					else if (astParam1->updateAble()) 
						finalListOne[CommonUtility::NumberToString(iter->first)] = true;
					else if (!astParam2->updateAble()) 
						return; // both are not updatable. 
				}
			}
			if (exist && !keepRelationship && astParam2->updateAble()) 
				finalListTwo[CommonUtility::NumberToString(iterSecond->first)] = 1;
	}

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