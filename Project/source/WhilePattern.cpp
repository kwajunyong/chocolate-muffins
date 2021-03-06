#include "WhilePattern.h"
#include "QueryManager.h"
WhilePattern::WhilePattern(QueryManager* qm, PKB *pkb) : QueryClass(QT_WHILEPATTERN, qm, pkb){


}
void WhilePattern::run() {

	ASTParameter *astParam1 = parameterList.at(0);
	ASTParameter *astParam2 = parameterList.at(1);

	if (astParam2->getParameterType() == VT_UNDERSCORE) // all under score skipped
		return;

	ASTExpressionBuilder* builder = pkbManager->getASTExpressionBuilder();
	ASTMatcher* matcher = pkbManager->getASTMatcher();


	vector<ASTNode*> nodes = pkbManager->getAST()->getStatementNodes(WHILE);

	ASTNode* node;


	bool matched = false;

	FastSearchInteger firstList = myQM->getValueListIntegerMap(astParam1->getVariableName());
	FastSearchInteger::iterator iterFound;




	FastSearchString result;
	int number;

	for (int i=0; i<nodes.size(); i++) {
		matched = false;

		number = nodes[i]->getStatementNumber();
		iterFound = firstList.find(number );

		if (iterFound != firstList.end()) {
			node = nodes[i]->getChild();				// Get first child

			matched = matcher->matchTree(node, builder->build(astParam2->getVariableName()));

			if (matched) {
				result[CommonUtility::NumberToString(number)] = true;		
			}
		}
	}


	failed = result.size() == 0;

	myQM->updateRelationship(astParam1->getVariableName(), result);

}

