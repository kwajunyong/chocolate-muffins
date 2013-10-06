#include "ExpressionPattern.h"
#include "QueryManager.h"
#include "BinaryRelationEngine.h"
ExpressionPattern::ExpressionPattern(QueryManager* qm, PKB *pkb) : QueryClass(QT_MODIFIES, qm, pkb){


}
void ExpressionPattern::run() {
		QueryClass *exp =new BinaryRelationEngine(NULL, NULL);


		exp->addParam("a", VT_CALL, "a");

 
		

}

