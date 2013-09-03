#include "UsesEngine.h"
#include "QueryManager.h"

UsesEngine::UsesEngine(QueryManager* qm, PKB *pkb) : QueryClass(QT_USES, qm, pkb){


}
void UsesEngine::run() {
	// pre check is here

	// if it's procedure and variable combination
	ASTParameter *astParam1 = parameterList.at(0);
	ASTParameter *astParam2 = parameterList.at(1);	

	// Procedure VS Variable 

	vector<string> second;
	if (astParam2->getParameterType() == VT_CONSTANTSTRING) 
	{
		second.push_back(astParam2->getVariableName());
	} else {
		second = myQM->getValueList(astParam2->getVariableName());
	}

	if (astParam1->getParameterType() == VT_CONSTANTSTRING || astParam1->getParameterType() == VT_PROCEDURE) {	
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
			vector<string> procedureListResult = pkbManager->getUses()->getUsesProc(*iter);


			exist = false;
			for (iterProcedureResult = procedureListResult.begin(); iterProcedureResult  != procedureListResult.end(); iterProcedureResult++) {
				for (iterProcedure = procedureList.begin(); iterProcedure  != procedureList.end(); iterProcedure++) {
					if ((*iterProcedure).compare(*iterProcedureResult) == 0) {
						exist = true;

						if (finalProcedureList.size() == procedureList.size())  // if the procedure has been moved 
							break;
						finalProcedureList[*iterProcedureResult] = 1;
					}
				}

				if (exist) { 
					finalVariableList[*iter] = 1;
				}
			}
		}

		if (astParam1->getParameterType() == VT_PROCEDURE) {
			vector<string> finalList; 
			convertVector(finalProcedureList, finalList);

			myQM->updateVector(astParam1->getVariableName(), finalList);

		} 
		if (astParam2->getParameterType() == VT_VARIABLELIST) {
			vector<string> finalList; 
			convertVector(finalVariableList, finalList);

			myQM->updateVector(astParam2->getVariableName(), finalList);
		}

		failed = (finalProcedureList.size() == 0 && finalVariableList.size() == 0);




	} else { // Statement Vs Variable 

		vector<int> statementList = myQM->getValueListInteger (astParam1->getVariableName());

		map<int, int> finalStatementList;
		map<string, int> finalVariableList; 

		vector<int>::const_iterator iter;
		vector<string>::const_iterator iterVariableResult;
		vector<string>::const_iterator iterVariable;

		// will use map instead of vector in the late release 
		// if procedureList more than variable list 
		// then use procedure to match against variable
		// and vice versa. 

		// later release
		// will mvoe 
		bool exist = false;


		for (iter = statementList.begin();  iter != statementList.end(); iter++) { // for every statement find the modified value

			vector<string> variableList = pkbManager->getUses()->getUsedVar(*iter);


			exist = false;
			for (iterVariableResult = variableList.begin(); iterVariableResult  != variableList.end(); iterVariableResult++) { // for each variable returned check against the variable list
				for (iterVariable = second.begin(); iterVariable  != second.end(); iterVariable++) {
					if ((*iterVariable).compare(*iterVariableResult) == 0) {
						exist = true;

						if (finalVariableList.size() == second.size())  // if  the list contained every single variable already 
							break;
						finalVariableList[*iterVariable] = 1;
					}
				}

				if (exist) { 
					finalStatementList[*iter] = 1;
				}
			}
		}

		if (astParam1->getParameterType() != VT_UNDERSCORE && astParam1->getParameterType() != VT_CONSTANTINTEGER) {
			vector<int> finalList; 
			convertVector(finalStatementList, finalList);
			myQM->updateVectorInteger (astParam1->getVariableName(), finalList);

		} 
		if (astParam2->getParameterType() == VT_VARIABLELIST) { // change to updatable function later one. 
			vector<string> finalList; 
			convertVector(finalVariableList, finalList);
			myQM->updateVector(astParam2->getVariableName(), finalList);
		}

		failed = (finalStatementList.size() == 0 && finalVariableList.size() == 0);


	}
}