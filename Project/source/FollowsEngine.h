#pragma once
#include "QueryClass.h"


class FollowsEngine : public QueryClass {
public:
	FollowsEngine(QueryManager* qm, PKB *pkb);

	  void run();
};