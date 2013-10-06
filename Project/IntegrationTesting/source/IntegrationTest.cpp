#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include <iostream>
#include "ListManager.h"
#include "QueryManager.h"
#include "Parser.h"
#include "DesignExtractor.h"
#include "PKB.h"
#include "QueryValidator.h"

using namespace std;

int main(int argc, char* argv[])
{
	Parser parser;
	DesignExtractor extractor;
	PKB *pkb;
	QueryManager *qm;
	QueryValidator *qv;

	try {
		pkb = parser.parse("C:\\Study\\CS3202\\simpleTestCase1.txt");
		extractor.extract(pkb);
		qm = new QueryManager(pkb);
		qv = new QueryValidator(qm, pkb);

	} catch (ParseException pe) {
		cout << pe.what();
		getchar();
	}
	//Sample 1
	//variable v;
//Select v such that modifies(2, v)
	/*qm->addExpression(VT_VARIABLELIST, "v");
	qm->addResultExpression("v");
	QueryClass *qc = new ModifiesEngine(qm, pkb);
	qc->addParam("2", VT_CONSTANTINTEGER);
	qc->addParam("v", VT_VARIABLELIST);

	qm->addQueryClass(qc);

	qm->execute();
	list<string> l = qm->outputResult();*/

	// Sample 3
//	while w; variable v;
//Select v such that Modifies(w, v)

	qm->addExpression(VT_VARIABLELIST, "v");
	qm->addExpression(VT_WHILE, "w");

	qm->addResultExpression("v");
	QueryClass *qc = new ModifiesEngine(qm, pkb);
	qc->addParam("w", VT_WHILE);
	qc->addParam("v", VT_VARIABLELIST);

	qm->addQueryClass(qc);

	qm->execute();
	list<string> l = qm->outputResult();
	return 0;
}