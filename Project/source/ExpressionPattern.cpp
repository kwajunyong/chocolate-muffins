#include "ExpressionPattern.h"
#include "QueryManager.h"

ExpressionPattern::ExpressionPattern(QueryManager* qm, PKB *pkb) : QueryClass(QT_MODIFIES, qm, pkb){


}
void ExpressionPattern::run() {
		QueryClass *exp ;

	exp->addParam("a", VT_ASSIGNMENT);
	exp->addParam("", VT_UNDERSCORE);
	exp->addParam("x+1", VT_EXPRESSION_UNDERSCORE);
	// pre check is here

	// if it's procedure and variable combination
	ASTParameter *astParam1 = parameterList.at(0);
	ASTParameter *astParam2 = parameterList.at(1);	


}

