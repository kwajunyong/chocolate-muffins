#pragma once
#include "QueryClass.h"

/*
  How to use. Let's say you have 
    pattern whilewhile ("x", _);

	QueryClass *exp = new ExpressionPattern(qm, pkb);

	exp->addParam("whilewhile", VT_WHILE);
	exp->addParam("x", VT_CONSTANTSTRING);	

	although I don't take in underscore. But you have to check also for completeness

*/

class WhilePattern : public QueryClass {
public:
	WhilePattern(QueryManager* qm, PKB *pkb);
	 void run();
};