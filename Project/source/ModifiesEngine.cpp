#include "ModifiesEngine.h"
#include "QueryManager.h"

ModifiesEngine::ModifiesEngine(QueryManager* qm, PKB *pkb) : QueryClass(QT_MODIFIES, qm, pkb){
}

void ModifiesEngine::run() {

	// if it's procedure and variable combination
	ASTParameter *astParam1 = parameterList.at(0);
	ASTParameter *astParam2 = parameterList.at(1);	

	// there is no need to check if both is underscore
	if (astParam1->getParameterType() == VT_UNDERSCORE && astParam2->getParameterType() == VT_UNDERSCORE) {
		/*if (pkbManager->getFollows()->IsThereFollow) 
		failed = false;
		else
		failed true;*/
		/*waiting for junyong*/
		return;
	}



	if (astParam1->getParameterType() == VT_CONSTANTSTRING || astParam1->getParameterType() == VT_PROCEDURE) {
		handleProcedureVariable();
	} else 
		handleStatementListVariable();
}

void ModifiesEngine::handleProcedureVariable() {
	// special case 1:
	// Modifies(procedure p , _);

	// declare necessary variable 
	bool keepRelationship = QueryClass::keepRelationship();
	vector<pair<string, string>> relationship;

	ASTParameter *astParam1 = parameterList.at(0);
	ASTParameter *astParam2 = parameterList.at(1);	

	FastSearchString procedureList;
	vector<string> second;

	if (astParam2->getParameterType() == VT_CONSTANTSTRING) 	
		second.push_back(astParam2->getVariableName());
	else if (astParam2->getParameterType() == VT_UNDERSCORE) 
		second = myQM->getAllVariable();	
	else 
		second = myQM->getValueList(astParam2->getVariableName());


	if (astParam1->getParameterType() == VT_PROCEDURE) {
		procedureList = myQM->getValueListMap(astParam1->getVariableName());
	} else if (astParam1->getParameterType() == VT_CONSTANTSTRING) {
		procedureList[astParam1->getVariableName()] = true;
	}


	FastSearchString finalProcedureList;
	FastSearchString finalVariableList; 

	vector<string>::const_iterator iter;
	vector<string>::const_iterator iterProcedureResult;
	vector<string>::const_iterator iterProcedure;

	bool exist = false;


	for (iter = second.begin();  iter != second.end(); iter++) {
		vector<string> &procedureListResult = pkbManager->getModifies()->getModifiesProc(*iter);

		exist = false;
		for (iterProcedureResult = procedureListResult.begin(); iterProcedureResult  != procedureListResult.end(); iterProcedureResult++) {
			if (procedureList.find(*iterProcedureResult) != procedureList.end()) {  // found
				exist = true;
				
				if (keepRelationship)
					relationship.push_back(pair<string, string>(*iterProcedure,*iter));
				else if (astParam1->updateAble()) {
					finalProcedureList[*iterProcedureResult] = true;
					if (!astParam2->updateAble()) {
						if (finalProcedureList.size() == procedureList.size()) {
							iter = second.end();
							break;
						}
					}
				}

				// if second is not updatable, we have done what we come for 
				if (!astParam2->updateAble())  {
					break;	
					if (!astParam1->updateAble()) {
						return; // we have got what we come for. 
					}
				}
				
			}
			if (exist && keepRelationship && astParam2->updateAble()) {
				finalVariableList[*iter] = true;
			}
		}
	

	if (keepRelationship) {

	}else 	if (astParam1->updateAble()) {
		vector<string> finalList; 
		CommonUtility::convertVector(finalProcedureList, finalList);		
		myQM->updateRelationship(astParam1->getVariableName(), finalList);
		
	} else 	if (astParam2->updateAble()) {
		vector<string> finalList; 
		CommonUtility::convertVector(finalVariableList, finalList);
		myQM->updateRelationship(astParam2->getVariableName(), finalList);		
	}

	// both constant already handled above
	failed = (finalProcedureList.size() == 0 && finalVariableList.size() == 0);


}
	}

void ModifiesEngine::handleStatementListVariable() {
	
	ASTParameter *astParam1 = parameterList.at(0);
	ASTParameter *astParam2 = parameterList.at(1);	

	FastSearchInteger statementList;

	if (astParam1->getParameterType() == VT_CONSTANTINTEGER) 
		statementList[atoi(astParam1->getVariableName().c_str())] = true;
	else if (astParam1->getParameterType() == VT_UNDERSCORE) {
		CommonUtility::convertToMap(myQM->getAllStatementList(), statementList);
	} else
		statementList = myQM->getValueListIntegerMap (astParam1->getVariableName());

	map<int, int> finalStatementList;
	map<string, int> finalVariableList; 

	vector<int>::const_iterator iter;	
	vector<string>::const_iterator iterVariable;

	// check which side is smaller. if you have a small list on the left side
	// compare the left side with the bigger right side. 
	// cos the right side if checking with AST, might incur a lot of run time. 

	/*
	// will use map instead of vector in the late release 
	// if procedureList more than variable list 
	// then use procedure to match against variable
	// and vice versa. 

	// later release
	// will mvoe 
	bool exist = false;


	for (iter = statementList.begin();  iter != statementList.end(); iter++) { // for every statement find the modified value

		vector<string> variableList = pkbManager->getModifies()->getModifiedVar(*iter);

		if (astParam2->getParameterType() == VT_UNDERSCORE) { // if the second variable is only underscore
			if (variableList.size() != 0)
				finalStatementList[*iter] = 1;
			continue;
		}			

		exist = false;
		for (iterVariableResult = variableList.begin(); iterVariableResult  != variableList.end(); iterVariableResult++) { // for each variable returned check against the variable list
			for (iterVariable = second.begin(); iterVariable  != second.end(); iterVariable++) {
				if ((*iterVariable).compare(*iterVariableResult) == 0) {
					exist = true;


					if (keepRelationship)
						relationship.push_back(pair<string, string>(CommonUtility::NumberToString(*iter),*iterVariableResult));


					finalVariableList[*iterVariable] = 1;
				}
			}

			if (exist) { 
				finalStatementList[*iter] = 1;
			}
		}
	}

	if (astParam1->updateAble()) {
		vector<int> finalList; 
		CommonUtility::convertVector(finalStatementList, finalList);
		myQM->updateVectorInteger (astParam1->getVariableName(), finalList);

		if (!keepRelationship) {
			vector<string> finalResultList;
			CommonUtility::convertVector(finalStatementList, finalList);
			myQM->updateRelationship(astParam1->getVariableName(), finalResultList);
		}

	} 
	if (astParam2->getParameterType() == VT_VARIABLELIST) { // change to updatable function later one. 
		vector<string> finalList; 
		CommonUtility::convertVector(finalVariableList, finalList);
		myQM->updateVector(astParam2->getVariableName(), finalList);
		if (!keepRelationship) {
			myQM->updateRelationship(astParam2->getVariableName(), finalList);
		}
	}

	failed = (finalStatementList.size() == 0 && finalVariableList.size() == 0);
}

if (keepRelationship) 
	myQM->updateRelationship(astParam1->getVariableName(), astParam2->getVariableName(), relationship);
	*/
}