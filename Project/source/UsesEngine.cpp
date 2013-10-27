#include "UsesEngine.h"
#include "QueryManager.h"
#include "CommonUtility.h"

UsesEngine::UsesEngine(QueryManager* qm, PKB *pkb) : QueryClass(QT_USES, qm, pkb){


}
void UsesEngine::run() {

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



	if ((astParam1->getParameterType() == VT_CONSTANTSTRING && astParam1->getVariableName().compare("_") != 0) || astParam1->getParameterType() == VT_PROCEDURE) {
		handleProcedureVariable();
	} else 
		handleStatementListVariable();
}

void UsesEngine::handleProcedureVariable() {
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

	bool exist = false;


	for (iter = second.begin();  iter != second.end(); iter++) {
		vector<string> &procedureListResult = pkbManager->getUses()->getUsesProc (*iter);

		exist = false;
		for (iterProcedureResult = procedureListResult.begin(); iterProcedureResult  != procedureListResult.end(); iterProcedureResult++) {
			if (procedureList.find(*iterProcedureResult) != procedureList.end()) {  // found
				exist = true;

				if (keepRelationship)
					relationship.push_back(pair<string, string>(*iterProcedureResult,*iter));
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
					if (!astParam1->updateAble()) 
						return; // we have got what we come for. 

					break;	

				}

			}

		}
		if (exist && !keepRelationship && astParam2->updateAble()) 
			finalVariableList[*iter] = true;
	}


	if (keepRelationship) {
		myQM->updateRelationship(astParam1->getVariableName(), astParam2->getVariableName(), relationship);
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
	failed = (finalProcedureList.size() == 0 && finalVariableList.size() == 0&& relationship.size() == 0);



}

void UsesEngine::handleStatementListVariable() {
	vector<pair<string, string>> relationship;

	ASTParameter *astParam1 = parameterList.at(0);
	ASTParameter *astParam2 = parameterList.at(1);	

	FastSearchString variableList;
	if (astParam2->getParameterType() == VT_CONSTANTSTRING) 	
		variableList[astParam2->getVariableName()] = true;
	else if (astParam2->getParameterType() == VT_UNDERSCORE) 
		CommonUtility::convertToMap(myQM->getAllVariable(), variableList);
	else 
		variableList= myQM->getValueListMap (astParam2->getVariableName());


	FastSearchInteger statementList;

	if (astParam1->getParameterType() == VT_CONSTANTINTEGER) 
		statementList[atoi(astParam1->getVariableName().c_str())] = true;
	else if (astParam1->getParameterType() == VT_UNDERSCORE || astParam1->getVariableName().compare("_") == 0) { // HACK
		CommonUtility::convertToMap(myQM->getAllStatementList(), statementList);
	} else
		statementList = myQM->getValueListIntegerMap (astParam1->getVariableName());

	FastSearchString finalStatementList;
	FastSearchString  finalVariableList; 


	bool exist = false;
	bool keepRelationship = this->keepRelationship();

	if (statementList.size() >  variableList.size()) {
		FastSearchString::const_iterator iter;	
		vector<int>::const_iterator iterStatementList;
		FastSearchInteger::const_iterator iterStatementFast;

		//using variable check against statementlist

		for (iter = variableList .begin();  iter != variableList.end(); iter++) { // for every statement find the modified value
			vector<int> statementListResult = pkbManager->getUses()->getUsesStmt (iter->first);				

			exist = false		;
			for (iterStatementList= statementListResult.begin(); iterStatementList != statementListResult.end(); iterStatementList++) { // for each variable returned check against the variable list
				// try to find 
				iterStatementFast = statementList.find(*iterStatementList);
				if (iterStatementFast != statementList.end()) {
					exist = true;

					if (keepRelationship)
						relationship.push_back(pair<string, string>(CommonUtility::NumberToString(*iterStatementList),iter->first));
					else if (astParam1->updateAble()) 
						finalStatementList[CommonUtility::NumberToString(*iterStatementList)] = true;
					else { 
						if (!astParam2->updateAble()) 
							return; // we have got what we come for. 					
						break;
					}
				}
			}
		}

		if (exist && !keepRelationship && astParam2->updateAble()) 
			finalVariableList[iter->first] = true;

	} else  {
		FastSearchInteger::const_iterator iter;	
		vector<string>::const_iterator iterVariableResult;
		FastSearchString::const_iterator iterVariable;

		for (iter = statementList.begin();  iter != statementList.end(); iter++) { // for every statement find the modified value
			vector<string> variableResult = pkbManager->getUses()->getUsedVar(iter->first);				
			exist = false;
			for (iterVariableResult = variableResult.begin(); iterVariableResult  != variableResult.end(); iterVariableResult++) { // for each variable returned check against the variable list
				iterVariable = variableList.find(*iterVariableResult);
				if (iterVariable != variableList.end()) {
					exist = true; // at least one result found for a given statement
					if (keepRelationship)
						relationship.push_back(pair<string, string>(CommonUtility::NumberToString(iter->first),*iterVariableResult));
					else if (astParam2->updateAble()) 
						finalVariableList[*iterVariableResult] = true;
					else { 
						if (!astParam1->updateAble()) 
							return; // we have got what we come for. 					
						break;
					}
				}
			}
			if (exist && !keepRelationship && astParam1->updateAble()) 
				finalStatementList[CommonUtility::NumberToString(iter->first)] = true;
		}



	}
	if (keepRelationship) {
		myQM->updateRelationship(astParam1->getVariableName(), astParam2->getVariableName(), relationship);

	}else 	if (astParam1->updateAble()) {
		vector<string> finalList; 
		CommonUtility::convertVector(finalStatementList , finalList);		
		myQM->updateRelationship(astParam1->getVariableName(), finalList);

	} else 	if (astParam2->updateAble()) {
		vector<string> finalList; 
		CommonUtility::convertVector(finalVariableList, finalList);
		myQM->updateRelationship(astParam2->getVariableName(), finalList);		
	}

	// both constant already handled above
	failed = (finalStatementList.size() == 0 && finalVariableList.size() == 0 && relationship.size() == 0);

}



// check which side is smaller. if you have a small list on the left side
// compare the left side with the bigger right side. 
// cos the right side if checking with AST, might incur a lot of run time. 

/*
// will use map instead of vector in the late release 
// if procedureList more than variable list 
// then use procedure to match against variable
// and vice versa. 


}*/


