#include "FollowsStarEngine.h"
#include "QueryManager.h"

FollowsStarEngine::FollowsStarEngine(QueryManager* qm, PKB *pkb) : QueryClass(QT_FOLLOWS_S, qm, pkb){


}
void FollowsStarEngine::run() {

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

	// will use map instead of vector in the late release 
	// if procedureList more than variable list 
	// then use procedure to match against variable
	// and vice versa. 

	// later release
	// will mvoe 
	bool exist = false;


	for (iter = first.begin();  iter != first.end(); iter++) { // for every statement find the modified value

		vector<int> followerList = pkbManager->getFollows()->getFollowedBy((*iter), true);

		exist = false;
		for (iterFollowerList = followerList.begin(); iterFollowerList  != followerList.end(); iterFollowerList++) { // for each variable returned check against the variable list
			for (iterSecond = second.begin(); iterSecond  != second.end(); iterSecond++) {
				if (*iterFollowerList == *iterSecond) {
					exist = true;

					if (finalListTwo.size() == second.size())  // if  the list contained every single variable already 
						break;
					finalListTwo[*iterFollowerList] = 1;
				}
			}

			if (exist) { 
				finalListOne[*iter] = 1;
			}
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

	failed = (finalListOne.size() == 0 && finalListTwo.size() == 0);




}

