#include "IfPattern.h"
#include "QueryManager.h"
IfPattern::IfPattern(QueryManager* qm, PKB *pkb) : QueryClass(QT_IFPATTERN, qm, pkb){


}
void IfPattern::run() {

	ASTExpressionBuilder* builder = pkbManager->getASTExpressionBuilder();
	ASTMatcher* matcher = pkbManager->getASTMatcher();


	vector<ASTNode*> nodes = pkbManager->getAST()->getStatementNodes(IF);

	ASTNode* node;

	ASTParameter *astParam1 = parameterList.at(0);
	ASTParameter *astParam2 = parameterList.at(1);

	bool matched = false;

	FastSearchInteger firstList = myQM->getValueListIntegerMap(astParam1->getVariableName());
	FastSearchInteger::iterator iterFound;



	FastSearchString result;
	int number;

	for (int i=0; i<nodes.size(); i++) {
		matched = false;
		number = nodes[i]->getStatementNumber();
		iterFound = firstList.find(number );

		if (iterFound != firstList.end()){
			node = nodes[i]->getChild();				// Get first child

			if (astParam2->getParameterType() != VT_UNDERSCORE)
				matched = matcher->matchTree(node, builder->build(astParam2->getVariableName()));

			if (matched) 
				result[CommonUtility::NumberToString(number)] =true;			
			
		}
	}

	failed = result.size() == 0;

	myQM->updateRelationship(astParam1->getVariableName(), result);

}

