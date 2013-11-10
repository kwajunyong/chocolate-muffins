#include "TestWrapper.h"

// implementation code of WrapperFactory - do NOT modify the next 5 lines
AbstractWrapper* WrapperFactory::wrapper = 0;
AbstractWrapper* WrapperFactory::createWrapper() {
	if (wrapper == 0) wrapper = new TestWrapper;
	return wrapper;
}
// Do not modify the following line
volatile bool TestWrapper::GlobalStop = false;

// a default constructor
TestWrapper::TestWrapper() {
	// create any objects here as instance variables of this class
	// as well as any initialization required for your spa program
}

// method for parsing the SIMPLE source
void TestWrapper::parse(std::string filename) {
	Parser parser;
	DesignExtractor extractor;

	try {
		pkb = parser.parse(filename);
		extractor.extract(pkb);
		qm = new QueryManager(pkb);
		qv = new QueryValidator(qm, pkb);
		QueryScore::initialize();
		qm->setDebug(false); // << TURN ON THE VARIABLE PRINTING MESSAG
		//pkb ->	extract();
	} catch (ParseException pe) {
		cout << pe.what();
		getchar();
	}
}

// method to evaluating a query
void TestWrapper::evaluate(std::string query, std::list<std::string>& results){

	if (qv->processQuery(query)) {
		qm->execute();
	} else {
		qm->setFail(true);
	}
	results = qm->outputResult();
	qm->resetEverything();

		

	//cin >> a;

}
