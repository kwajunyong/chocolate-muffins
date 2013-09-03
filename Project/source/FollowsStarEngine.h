#pragma once
#include "QueryClass.h"


class FollowsStarEngine : public QueryClass {
public:
	FollowsStarEngine(QueryManager* qm, PKB *pkb);

	  void run();
};