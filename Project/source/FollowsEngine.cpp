#include "FollowsEngine.h"
#include "QueryManager.h"
#include "CommonUtility.h"
FollowsEngine::FollowsEngine(QueryManager* qm, PKB *pkb) : QueryClass(QT_FOLLOWS, qm, pkb){


}
void FollowsEngine::run() {

	// pre check is here

	// if it's procedure and variable combination
	ASTParameter *astParam1 = parameterList.at(0);
	ASTParameter *astParam2 = parameterList.at(1);	

	vector<int> second;
	vector<int> first;

	if (astParam1->getParameterType() == VT_CONSTANTINTEGER) {
		first.push_back(atoi(astParam2->getVariableName().c_str()));
	} else {
		first = myQM->getValueListInteger(astParam1->getVariableName());
	}

	
	if (astParam2->getParameterType() == VT_CONSTANTINTEGER) {
		second.push_back(atoi(astParam2->getVariableName().c_str()));
	} else {
		second = myQM->getValueListInteger(astParam2->getVariableName());
	}


	map<int, int> finalListOne;
	map<int, int> finalListTwo; 

	vector<int>::const_iterator iter;
	vector<int>::const_iterator iterFollowerList;
	vector<int>::const_iterator iterSecond;

	bool exist;
	bool keepRelationship = astParam1->updateAble() && astParam2->updateAble() ;

	vector<pair<string, string>> resultList;

	for (iter = first.begin();  iter != first.end(); iter++) { // for every statement find the modified value

		vector<int> &followerList = pkbManager->getFollows()->getFollowedBy((*iter), false);
		exist = false;

		for (iterFollowerList = followerList.begin(); iterFollowerList  != followerList.end(); iterFollowerList++) { // for each variable returned check against the variable list
			for (iterSecond = second.begin(); iterSecond  != second.end(); iterSecond++) {
				if (*iterFollowerList == *iterSecond) {
					exist = true;
					
					if (keepRelationship)
						resultList.push_back(pair<string, string>(NumberToString(*iter), NumberToString(*iterSecond)));					
					finalListTwo[*iterFollowerList] = 1;
					break;
				}
			}
			if (exist) 
				finalListOne[*iter] = 1;
			
		}
	}

	
	if (astParam1->updateAble()) {
		vector<int> finalList; 
		convertVector(finalListOne, finalList);
		myQM->updateVectorInteger (astParam1->getVariableName(), finalList);

	} 
	
	if (astParam2->updateAble()) { 
		vector<int> finalList; 
		convertVector(finalListTwo, finalList);
		myQM->updateVectorInteger(astParam2->getVariableName(), finalList);
		
	}

	if (keepRelationship) {
		myQM->updateRelationship(astParam1->getVariableName(), astParam2->getVariableName(), resultList);
	} else if (astParam1->updateAble()) {
		vector<string> finalList; 
		convertVector(finalListOne, finalList);
		myQM->updateRelationship(astParam1->getVariableName(), finalList);
	} else if (astParam2->updateAble()) {
		vector<string> finalList; 
		convertVector(finalListOne, finalList);
		myQM->updateRelationship(astParam2->getVariableName(), finalList);
	}
	

	failed = (finalListOne.size() == 0 && finalListTwo.size() == 0);
}

