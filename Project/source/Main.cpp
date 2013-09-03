#include <iostream>

#include "Parser.h"
#include "DesignExtractor.h"
#include "QueryManager.h"
#include "QueryValidator.h"
#include "QueryTree.h"
#include "ModifiesEngine.h"
#include "FollowsEngine.h"
#include "FollowsStarEngine.h"
#include "UsesEngine.h"

#include <map>

int main()
{
	Parser parser;
	DesignExtractor extractor;

	PKB* pkb;

	try {
		pkb = parser.parse("C:\\Users\\hendri\\Desktop\\Team06\\Team06\\Tests06\\simpleTestCase1.txt");
		extractor.extract(pkb);
	} catch (ParseException pe) {
		cout << pe.what();
		getchar();
		return 0;
	}

	QueryManager* qm = new QueryManager(pkb)	;
	//qm->addExpression(VT_STATEMENTLIST, "s");
	//qm->addResultExpression("s");


	QueryClass* qc = new UsesEngine(qm, pkb);

	//qc->addParam("s", VT_STATEMENTLIST);
	//
	//qc->addParam("5", VT_CONSTANTINTEGER);


	//qm->addQueryClass(qc);

	//qm->execute();


	QueryValidator qv(qm, pkb);

	

	qv.processInputQuery("stmt s;Select s such that Uses(s, \"oo\")");
	qm->execute();
	list<string> result = qm->outputResult();
	qm->resetEverything();


	qv.processInputQuery("while w; variable v;Select v such that Modifies(w, v)");
	qm->execute();
	list<string> result1 = qm->outputResult();
	qm->resetEverything();


	int a; 
	cin >> a;

	}