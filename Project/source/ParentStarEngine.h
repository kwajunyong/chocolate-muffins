#pragma once
#include "QueryClass.h"


class ParentStarEngine : public QueryClass {
public:
	ParentStarEngine(QueryManager* qm, PKB *pkb);

	  void run();
};