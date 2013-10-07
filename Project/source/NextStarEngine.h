#pragma once
#include "QueryClass.h"


class NextStarEngine : public QueryClass {
public:
	NextStarEngine(QueryManager* qm, PKB *pkb);

	  void run();
};