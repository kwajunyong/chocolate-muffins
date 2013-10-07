#include "IfPattern.h"
#include "QueryManager.h"
IfPattern::IfPattern(QueryManager* qm, PKB *pkb) : QueryClass(QT_MODIFIES, qm, pkb){


}
void IfPattern::run() {

	ASTExpressionBuilder* builder = pkbManager->getASTExpressionBuilder();
	ASTMatcher* matcher = pkbManager->getASTMatcher();

		
	vector<ASTNode*> nodes = pkbManager->getAST()->getStatementNodes(IF);

	ASTNode* node;

	ASTParameter *astParam1 = parameterList.at(0);
	ASTParameter *astParam2 = parameterList.at(1);

	bool matched = false;
	vector<int> first = myQM->getValueListInteger(astParam1->getVariableName());

	map<int, int> firstList; // allow fast searching
	map<int, int>::iterator iterFound;

	CommonUtility::convertToMap(first, firstList);

	vector<string> result;
	int number;

	for (int i=0; i<nodes.size(); i++) {
		matched = false;

		node = nodes[i]->getChild();				// Get first child

		if (astParam2->getParameterType() != VT_UNDERSCORE)
			matched = matcher->matchTree(node, builder->build(astParam2->getVariableName()));

		if (matched) {
			number = nodes[i]->getStatementNumber();
			iterFound = firstList.find(number );

			if (iterFound != firstList.end())
				result.push_back(CommonUtility::NumberToString(number));			
		}
	}
	

	failed = result.size() == 0;

	myQM->updateRelationship(astParam1->getVariableName(), result);

}

