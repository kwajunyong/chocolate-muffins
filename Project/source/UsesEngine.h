#pragma once
#include "QueryClass.h"


class UsesEngine : public QueryClass {
public:
	UsesEngine(QueryManager* qm, PKB *pkb);

	  void run();
	  void handleProcedureVariable();
	  void handleStatementListVariable();
};