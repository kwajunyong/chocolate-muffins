#pragma once
#include "QueryClass.h"


class NextEngine : public QueryClass {
public:
	NextEngine(QueryManager* qm, PKB *pkb);

	  void run();
};