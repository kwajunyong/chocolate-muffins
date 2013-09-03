#include "NextEngine.h"
#include "QueryManager.h"

NextEngine::NextEngine(QueryManager* qm, PKB *pkb) : QueryClass(QT_MODIFIES, qm, pkb){


}
void NextEngine::run() {

	// pre check is here

	// if it's procedure and variable combination
	ASTParameter *astParam1 = parameterList.at(0);
	ASTParameter *astParam2 = parameterList.at(1);	


	//vector<int> second;
	//vector<int> first;

	//if (astParam2->getParameterType() == VT_CONSTANTINTEGER) 
	//	second.push_back(astParam2->getVariableName());
	//} else {
	//	second = myQM->getValueListInteger(astParam1->getVariableName());
	//}

	//if (astParam1->getParameterType() == VT_CONSTANTINTEGER) 
	//	first.push_back(astParam2->getVariableName());
	//} else {
	//	first = myQM->getValueListInteger(astParam1->getVariableName());
	//}





	//vector<int> statementList = myQM->getValueListInteger (astParam1->getVariableName());

	//map<int, int> finalStatementList;
	//map<string, int> finalVariableList; 

	//vector<int>::const_iterator iter;
	//vector<string>::const_iterator iterVariableResult;
	//vector<string>::const_iterator iterVariable;

	//// will use map instead of vector in the late release 
	//// if procedureList more than variable list 
	//// then use procedure to match against variable
	//// and vice versa. 

	//// later release
	//// will mvoe 
	//bool exist = false;


	//for (iter = statementList.begin();  iter != statementList.end(); iter++) { // for every statement find the modified value

	//	vector<string> variableList = pkbManager->getModifies()->getModifiedVar(*iter);


	//	exist = false;
	//	for (iterVariableResult = variableList.begin(); iterVariableResult  != variableList.end(); iterVariableResult++) { // for each variable returned check against the variable list
	//		for (iterVariable = second.begin(); iterVariable  != second.end(); iterVariable++) {
	//			if ((*iterVariable).compare(*iterVariableResult) == 0) {
	//				exist = true;

	//				if (finalVariableList.size() == second.size())  // if  the list contained every single variable already 
	//					break;
	//				finalVariableList[*iterVariable] = 1;
	//			}
	//		}

	//		if (exist) { 
	//			finalStatementList[*iter] = 1;
	//		}
	//	}
	//}

	//if (astParam1->getParameterType() != VT_UNDERSCORE || astParam1->getParameterType() != VT_CONSTANTINTEGER) {
	//	vector<int> finalList; 
	//	convertVector(finalStatementList, finalList);
	//	myQM->updateVectorInteger (astParam1->getVariableName(), finalList);

	//} else if (astParam2->getParameterType() != VT_CONSTANTSTRING) { // change to updatable function later one. 
	//	vector<string> finalList; 
	//	convertVector(finalVariableList, finalList);
	//	myQM->updateVector(astParam2->getVariableName(), finalList);
	//}

	//failed = (finalStatementList.size() == 0 && finalVariableList.size() == 0);




}

