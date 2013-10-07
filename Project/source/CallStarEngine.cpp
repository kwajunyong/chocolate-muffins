#include "CallStarEngine.h"
#include "QueryManager.h"
#include "CommonUtility.h"

CallStarEngine::CallStarEngine(QueryManager* qm, PKB *pkb) : QueryClass(QT_USES, qm, pkb){


}
void CallStarEngine::run() {
	// pre check is here

	// if it's procedure and variable combination
	ASTParameter *astParam1 = parameterList.at(0);
	ASTParameter *astParam2 = parameterList.at(1);	

	if (astParam2->getParameterType() == VT_UNDERSCORE && astParam1->getParameterType() == VT_UNDERSCORE)  {
		// check uses
		return; 
	}

	vector<string> second;
	if (astParam2->getParameterType() == VT_CONSTANTSTRING) 
	{
		second.push_back(astParam2->getVariableName());
	} else if (astParam2->getParameterType() == VT_UNDERSCORE) {
		second = myQM->getAllVariable();
	}
	else {
		second = myQM->getValueList(astParam2->getVariableName());
	}

	bool keepRelation = keepRelationship();
	vector<pair<string, string>> relationship;
	// Procedure VS Variable 

	vector<string> procedureList;

	if (astParam1->getParameterType() == VT_PROCEDURE) {
		procedureList = myQM->getValueList(astParam1->getVariableName());
	} else if (astParam1->getParameterType() == VT_CONSTANTSTRING) {
		procedureList.push_back(astParam1->getVariableName());
	}



	map<string, int> finalProcedureList;
	map<string, int> finalVariableList; 

	vector<string>::const_iterator iter;
	vector<string>::const_iterator iterProcedureResult;
	vector<string>::const_iterator iterProcedure;

	// will use map instead of vector in the late release 
	// if procedureList more than variable list 
	// then use procedure to match against variable
	// and vice versa. 

	// later release
	// will mvoe 
	bool exist = false;


	for (iter = second.begin();  iter != second.end(); iter++) {

		vector<string> procedureListResult = pkbManager->getCalls()->getCalled(*iter, true);

		exist = false;
		for (iterProcedureResult = procedureListResult.begin(); iterProcedureResult  != procedureListResult.end(); iterProcedureResult++) {
			for (iterProcedure = procedureList.begin(); iterProcedure  != procedureList.end(); iterProcedure++) {
				if ((*iterProcedure).compare(*iterProcedureResult) == 0) {
					exist = true;

					if (!astParam1->updateAble()) // no point keeping something that doesn't need to be updated
						break;

					if (keepRelation) 
						relationship.push_back(pair<string, string>((*iterProcedure), (*iter)));

					finalProcedureList[*iterProcedureResult] = 1;
				}
			}

			if (exist && astParam2->updateAble()) 
				finalVariableList[*iter] = 1;

		}
	}

	if (!keepRelation && astParam1->updateAble()) {
		vector<string> finalList; 
		CommonUtility::convertVector(finalProcedureList, finalList);

		myQM->updateRelationship(astParam1->getVariableName(), finalList);
	} 	else if (!keepRelation && astParam2->updateAble()) {
		vector<string> finalList; 
		CommonUtility::convertVector(finalVariableList, finalList);

		myQM->updateRelationship(astParam2->getVariableName(), finalList);
	} else if (keepRelation) {
		myQM->updateRelationship(astParam1->getVariableName(), astParam2->getVariableName(), relationship);

	}


	failed = (finalProcedureList.size() == 0 && finalVariableList.size() == 0);



}