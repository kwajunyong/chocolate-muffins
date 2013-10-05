#pragma once
#include "QueryClass.h"

/*
  How to use. Let's say you have 
    pattern ififa ("x", _);

	QueryClass *exp = new ExpressionPattern(qm, pkb);

	exp->addParam("ififa ", VT_WHILE);
	exp->addParam("x", VT_CONSTANTSTRING);	

	although I don't take in underscore. But you have to check also for completeness

*/

class IfPattern : public QueryClass {
public:
	IfPattern (QueryManager* qm, PKB *pkb);
	 void run();
};