#pragma once
#include "QueryClass.h"


class ParentEngine : public QueryClass {
public:
	ParentEngine(QueryManager* qm, PKB *pkb);

	  void run();
};