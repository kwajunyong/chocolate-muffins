#include "ExpressionPattern.h"
#include "QueryManager.h"
ExpressionPattern::ExpressionPattern(QueryManager* qm, PKB *pkb) : QueryClass(QT_EXPRESSIONPATTERN, qm, pkb){


}
void ExpressionPattern::run() {

	ASTExpressionBuilder* builder = pkbManager->getASTExpressionBuilder();
	ASTMatcher* matcher = pkbManager->getASTMatcher();



	vector<ASTNode*> nodes = pkbManager->getAST()->getStatementNodes(ASSIGN);

	ASTNode* node;

	ASTParameter *astParam1 = parameterList.at(0);
	ASTParameter *astParam2 = parameterList.at(1);
	ASTParameter *astParam3 = parameterList.at(2);

	bool matched = false;
	FastSearchInteger firstList = myQM->getValueListIntegerMap(astParam1->getVariableName());
	FastSearchInteger::iterator iterFound;




	FastSearchString result;
	int number;

	for (int i=0; i<nodes.size(); i++) {
		matched = true;

		number = nodes[i]->getStatementNumber();
		iterFound = firstList.find(number);
		if (iterFound == firstList.end()) {
			matched =false;
		}

		if (matched) {
			node = nodes[i]->getChild();				// Get first child

			if (astParam2->getParameterType() != VT_UNDERSCORE)
				matched = matcher->matchTree(node, builder->build(astParam2->getVariableName()));
		}


		if (matched) {
			node = nodes[i]->getChild()->getNext();		// Get second child

			if (astParam3->getParameterType() == VT_EXPRESSION_UNDERSCORE)
				matched = matcher->matchSubTree(node, builder->build(astParam3->getVariableName()));
			else if (astParam3->getParameterType() != VT_UNDERSCORE)			
				matched = matcher->matchTree(node, builder->build(astParam3->getVariableName()));
		}

		if (matched) {
			result[CommonUtility::NumberToString(number)]  =true;			
		}
	}


	failed = result.size() == 0;

	myQM->updateRelationship(astParam1->getVariableName(), result);

}

