#pragma once
#include "QueryClass.h"


class AffectEngine : public QueryClass {
public:
	AffectEngine(QueryManager* qm, PKB *pkb);

	  void run();
};