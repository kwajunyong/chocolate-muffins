#pragma once
#include "QueryClass.h"

/*
  How to use. Let's say you have 
    pattern a (_, _"x+1"_);

	QueryClass *exp = new ExpressionPattern(qm, pkb);

	exp->addParam("a", VT_ASSIGNMNET);
	exp->addParam("", VT_UNDERSCORE);
	exp->addParam("x+1", VT_EXPRESSION_UNDERSCORE);


	second example

	pattern c ("x", "1+x+1");

	
	QueryClass *exp = new ExpressionPattern(qm, pkb);

	exp->addParam("c", VT_ASSIGNMNET);
	exp->addParam("x", VT_CONSTANTSTRING);
	exp->addParam("1+x+1", VT_CONSTANTSTRING);

*/

class ExpressionPattern : public QueryClass {
public:
	ExpressionPattern(QueryManager* qm, PKB *pkb);
	 void run();
};