#pragma once
#include "ASTParameter.h"
#include "PKB.h"
#include <vector>
class ASTParameterValue {

public:	
	ASTParameterValue(ASTParameter param);	
	
	ASTParameterValue();
	 ASTParameter& getASTParameter();

	void reset() ;
	const  vector<string>& getValueList() ; 
	const  vector<int>& getValueListInteger() ; 

	FastSearchString getValueListMap() ; 
	FastSearchInteger getValueListIntegerMap() ; 

	void initialize(PKB * pkb);

	void setValueList(const vector<string> & valueList);
	void setValueListInteger(const vector<int> &vectorInteger); 

	bool hasNotInitialized();
private:
	ASTParameter parameter;
	vector<string> valueList;
	vector<int> valueListInteger;
	PARAMETERSTATUS status ;
	

};