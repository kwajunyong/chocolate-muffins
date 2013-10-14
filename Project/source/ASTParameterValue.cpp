#include "ASTParameterValue.h"
#include "ASTType.h"

ASTParameterValue::ASTParameterValue(ASTParameter param) {
		parameter = param;		
		status = PARAMETERSTATUS::UNINITIALIZED;
	}	

bool ASTParameterValue::hasNotInitialized() {
	return status ==  PARAMETERSTATUS::UNINITIALIZED;
}


ASTParameterValue::ASTParameterValue() { // default constructor
}

void ASTParameterValue::setValueList(const vector<string> & valuels) {
	valueList = valuels;
}

void ASTParameterValue::setValueListInteger(const vector<int> &vectorI) {
	valueListInteger = vectorI;
} 

const  vector<string>& ASTParameterValue::getValueList()  {
	if (status == PARAMETERSTATUS::UNINITIALIZED) 
		throw exception("Not initialized yet");
	return valueList;
}

FastSearchString ASTParameterValue::getValueListMap  ()  {
	FastSearchString fsi;
	const vector<string> &result = getValueList();

	vector<string>::const_iterator iter;

	for (iter =  result.begin(); iter != result.end(); iter++) {
		fsi[*iter] = true;
	}
	return fsi;
}

FastSearchInteger ASTParameterValue::getValueListIntegerMap  ()  {
	FastSearchInteger fsi;
	const vector<int> &result = getValueListInteger();

	vector<int>::const_iterator iter;

	for (iter =  result.begin(); iter != result.end(); iter++) {
		fsi[*iter] = true;
	}
	return fsi;
}

const  vector<int>& ASTParameterValue::getValueListInteger ()  {
	if (status == PARAMETERSTATUS::UNINITIALIZED) 
		throw exception("Not initialized yet");
	return valueListInteger;
}

void ASTParameterValue::initialize(PKB *pkb) {

	if (parameter.getParameterType() == VARIABLETYPE::VT_ASSIGNMENT) {
		valueListInteger = pkb->getAST()->getStatementNumbers(ASTType::ASSIGN);		
	} else if (parameter.getParameterType() == VARIABLETYPE::VT_PROCEDURE) {
		valueList = pkb->getProcTable()->getAllNames();
	} else if (parameter.getParameterType() == VARIABLETYPE::VT_WHILE) {
		valueListInteger = pkb->getAST()->getStatementNumbers(ASTType::WHILE);		
	} else if (parameter.getParameterType() == VARIABLETYPE::VT_IF)  {
			valueListInteger = pkb->getAST()->getStatementNumbers(ASTType::IF);		
	} else if (parameter.getParameterType() == VARIABLETYPE::VT_STATEMENTLIST) {
		valueListInteger = pkb->getAST()->getStatementNumbers(ASTType::ALL); // get all statement number
	} else if (parameter.getParameterType() == VT_CALL) {
		valueListInteger = pkb->getAST()->getStatementNumbers(ASTType::CALL); // get all statement number
	} else if (parameter.getParameterType() == VT_VARIABLELIST) {
		valueList = pkb->getVarTable()->getAllNames();
	} else if (parameter.getParameterType() == VARIABLETYPE::VT_PROG_LINE) {
		valueListInteger = pkb->getAST()->getStatementNumbers(ASTType::ALL); // get all statement number
	
	}else {
		throw new exception("Unable to load parameter type");
	}

	status = PARAMETERSTATUS::LOADED;

}

void ASTParameterValue::reset() {
	status = PARAMETERSTATUS::UNINITIALIZED;
	valueList.clear();
	valueListInteger.clear();
}

 ASTParameter& ASTParameterValue::getASTParameter() {
  return parameter ;
}