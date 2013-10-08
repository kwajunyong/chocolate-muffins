#pragma once
#include "QueryClass.h"


class ModifiesEngine : public QueryClass {
public:
	ModifiesEngine(QueryManager* qm, PKB *pkb);

	 void run();
	 void handleProcedureVariable();
	 void handleStatementListVariable();

};