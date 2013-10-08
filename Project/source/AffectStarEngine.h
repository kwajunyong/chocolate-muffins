#pragma once
#include "QueryClass.h"


class AffectStarEngine : public QueryClass {
public:
	AffectStarEngine(QueryManager* qm, PKB *pkb);

	  void run();
};