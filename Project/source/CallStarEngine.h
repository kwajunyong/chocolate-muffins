#pragma once
#include "QueryClass.h"


class CallStarEngine : public QueryClass {
public:
	CallStarEngine (QueryManager* qm, PKB *pkb);

	  void run();
};