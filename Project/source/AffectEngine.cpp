#include "AffectEngine.h"
#include "QueryManager.h"

AffectEngine::AffectEngine(QueryManager* qm, PKB *pkb) : QueryClass(QT_MODIFIES, qm, pkb){


}
void AffectEngine::run() {

	// if it's procedure and variable combination
	ASTParameter *astParam1 = parameterList.at(0);
	ASTParameter *astParam2 = parameterList.at(1);	

	vector<int> second;
	vector<int> first;

	// there is no need to check if both is underscore
	if (astParam1->getParameterType() == VT_UNDERSCORE && astParam2->getParameterType() == VT_UNDERSCORE) {
		/*if (pkbManager->getFollows()->IsThereFollow) 
		failed = false;
		else
		failed true;*/

		return;
	}


	if (astParam1->getParameterType() == VT_CONSTANTINTEGER) {
		if (pkbManager->getAST()->getStatementType(atoi(astParam1->getVariableName().c_str())) != ASTType::ASSIGN) {
			failed =true;
		}

		first.push_back(atoi(astParam2->getVariableName().c_str()));

	} else if (astParam2->getParameterType() == VT_UNDERSCORE) {
		first = myQM->getAllList(ASTType::ASSIGN);
	}else{
		first = myQM->getValueListInteger(astParam1->getVariableName());
	}

	if (astParam1->getParameterType() == VT_CONSTANTINTEGER) {		
		if (pkbManager->getAST()->getStatementType(atoi(astParam1->getVariableName().c_str())) != ASTType::ASSIGN) {
			failed =true;
		}
		second.push_back(atoi(astParam2->getVariableName().c_str()));
	} else if (astParam2->getParameterType() == VT_UNDERSCORE) {
		second= myQM->getAllList(ASTType::ASSIGN);
	}else{
		second= myQM->getValueListInteger(astParam1->getVariableName());
	}


	map<int, int> finalListOne;
	map<int, int> finalListTwo; 

	vector<int>::const_iterator iter;
	vector<int>::const_iterator iterNextList;
	vector<int>::const_iterator iterSecond;

	bool exist;
	bool keepRelationship = astParam1->updateAble() && astParam2->updateAble() ;

	vector<pair<string, string>> resultList;

	for (iter = first.begin();  iter != first.end(); iter++) { // for every statement find the modified value

		vector<int> followerList;
		//pkbManager->getAffect()->getNext((*iter), false);
		exist = false;

		for (iterNextList = followerList.begin(); iterNextList  != followerList.end(); iterNextList++) { // for each variable returned check against the variable list
			for (iterSecond = second.begin(); iterSecond  != second.end(); iterSecond++) {
				if (*iterNextList == *iterSecond) {
					exist = true;

					if (keepRelationship)
						resultList.push_back(pair<string, string>(CommonUtility::NumberToString(*iter), CommonUtility::NumberToString(*iterSecond)));					
					if (astParam2->updateAble() )
						finalListTwo[*iterNextList] = 1;
					else
						break;
				}
			}
			if (exist && !keepRelationship && astParam1->updateAble()) 
				finalListOne[*iter] = 1;

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

	if (keepRelationship) {
		myQM->updateRelationship(astParam1->getVariableName(), astParam2->getVariableName(), resultList);
	} else if (astParam1->updateAble()) {
		vector<string> finalList; 
		CommonUtility::convertVector(finalListOne, finalList);
		myQM->updateRelationship(astParam1->getVariableName(), finalList);
	} else if (astParam2->updateAble()) {
		vector<string> finalList; 
		CommonUtility::convertVector(finalListOne, finalList);
		myQM->updateRelationship(astParam2->getVariableName(), finalList);
	}


	failed = (finalListOne.size() == 0 && finalListTwo.size() == 0);
}





