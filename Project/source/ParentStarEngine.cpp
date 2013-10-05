#include "ParentStarEngine.h"
#include "QueryManager.h"

ParentStarEngine::ParentStarEngine(QueryManager* qm, PKB *pkb) : QueryClass(QT_PARENTS_S, qm, pkb){


}
void ParentStarEngine::run() {

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

	
	if (astParam2->getParameterType() == VT_CONSTANTINTEGER || astParam2->getParameterType() == VT_CONSTANTSTRING) { // temp hack to take care the bug
		second.push_back(atoi(astParam2->getVariableName().c_str()));
	} else {
		second = myQM->getValueListInteger(astParam2->getVariableName());
	}


	map<int, int> finalListOne;
	map<int, int> finalListTwo; 

	vector<int>::const_iterator iter;
	vector<int>::const_iterator iterChildList;
	vector<int>::const_iterator iterSecond;

	// will use map instead of vector in the late release 
	// if procedureList more than variable list 
	// then use procedure to match against variable
	// and vice versa. 

	// later release
	// will mvoe 
	bool exist = false;


	for (iter = first.begin();  iter != first.end(); iter++) { // for every statement find the modified value

		vector<int> childList = pkbManager->getParent()->getChild(*iter, true);

		exist = false;
		for (iterChildList = childList.begin(); iterChildList  != childList.end(); iterChildList++) { // for each variable returned check against the variable list
			for (iterSecond = second.begin(); iterSecond  != second.end(); iterSecond++) {
				if (*iterChildList == *iterSecond) {
					exist = true;

					if (finalListTwo.size() == second.size())  // if  the list contained every single variable already 
						break;
					finalListTwo[*iterChildList] = 1;
				}
			}

			if (exist) { 
				finalListOne[*iter] = 1;
			}
		}
	}

	if (astParam1->updateAble()) {
		vector<int> finalList; 
		CommonUtility::convertVector(finalListOne, finalList);
		myQM->updateVectorInteger (astParam1->getVariableName(), finalList);

	} 
	
	if (astParam2->updateAble()) { 
		vector<int> finalList; 
		CommonUtility::convertVector(finalListTwo, finalList);
		myQM->updateVectorInteger(astParam2->getVariableName(), finalList);
	}

	failed = (finalListOne.size() == 0 && finalListTwo.size() == 0);




}

