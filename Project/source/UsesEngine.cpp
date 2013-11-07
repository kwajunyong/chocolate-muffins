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



	if (astParam1->getParameterType() == VT_CONSTANTSTRING  || astParam1->getParameterType() == VT_PROCEDURE) {
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
	FastSearchString second;

	if (astParam2->getParameterType() == VT_UNDERSCORE) 
		CommonUtility::convertToMap(myQM->getAllVariable(), second);
	else 
		loadVariable(1, second);

	if (astParam1->getParameterType() == VT_UNDERSCORE) 
		procedureList = myQM->getAllProcedureList();
	else {
		loadVariable(0, procedureList);
	}


	FastSearchString finalProcedureList;
	FastSearchString finalVariableList; 

	FastSearchString::const_iterator iter;

	bool exist = false;


	if (second.size() < procedureList.size()) {

		vector<string>::const_iterator iterProcedureResult;

		for (iter = second.begin();  iter != second.end(); iter++) {
			vector<string> &procedureListResult = pkbManager->getUses()->getUsesProc(iter->first);

			exist = false;
			for (iterProcedureResult = procedureListResult.begin(); iterProcedureResult  != procedureListResult.end(); iterProcedureResult++) {
				if (procedureList.find(*iterProcedureResult) != procedureList.end()) {  // found
					exist = true;

					if (keepRelationship)
						relationship.push_back(pair<string, string>(*iterProcedureResult, iter->first));
					else if (astParam1->updateAble()) {
						finalProcedureList[*iterProcedureResult] = true;
					} else { // if the first one is not updateable, just need to care for second one 
						if (!astParam2->updateAble()) 
							return; // we have got what we come for. 

						break;	

					}

				}			
			}
			if (exist && !keepRelationship && astParam2->updateAble()) 
				finalVariableList[iter->first] = true;

		}
	} else {
		vector<string>::iterator iterVarResult;

		for (iter = procedureList.begin();  iter != procedureList.end(); iter++) {
			vector<string> &varListResult = pkbManager->getUses()->getUsedVar(iter->first);

			exist = false;
			for (iterVarResult = varListResult.begin(); iterVarResult  != varListResult.end(); iterVarResult++) {
				if (second.find(*iterVarResult) != second.end()) {  // found
					exist = true;

					if (keepRelationship)
						relationship.push_back(pair<string, string>(iter->first, *iterVarResult));
					else if (astParam2->updateAble()) {
						finalVariableList[*iterVarResult] = true;

					} else { // if the first one is not updateable, just need to care for second one 
						if (!astParam1->updateAble()) 
							return; // we have got what we come for. 

						// if param2 is not updatable, super unlikely after the optimization
						break;	

					}

				}			
			}
			if (exist && !keepRelationship && astParam1->updateAble()) 
				finalProcedureList[iter->first] = true;

		}
	}


	updateVariable(relationship, finalProcedureList, finalVariableList, keepRelationship);

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
	else if (astParam2->getParameterType() == VT_UNDERSCORE ) 
		CommonUtility::convertToMap(myQM->getAllVariable(), variableList);
	else 
		variableList= myQM->getValueListMap (astParam2->getVariableName());


	FastSearchInteger statementList;

	if (astParam1->getParameterType() == VT_CONSTANTINTEGER) 
		statementList[atoi(astParam1->getVariableName().c_str())] = true;
	else if (astParam1->getParameterType() == VT_UNDERSCORE) { // temporary hack. REMOVE away after youli fixes his error
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
			vector<int> statementListResult = pkbManager->getUses()->getUsesStmt(iter->first);				

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


			if (exist && !keepRelationship && astParam2->updateAble()) 
				finalVariableList[iter->first] = true;
		}
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

	updateVariable(relationship, finalStatementList, finalVariableList, keepRelationship);


	// both constant already handled above
	failed = (finalStatementList.size() == 0 && finalVariableList.size() == 0 && relationship.size() == 0);



}

