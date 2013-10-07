#pragma once
#include "QueryClass.h"


class CallEngine : public QueryClass {
public:
	CallEngine (QueryManager* qm, PKB *pkb);

	  void run();
};