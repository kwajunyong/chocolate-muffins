#include <cppunit\CompilerOutputter.h>
#include <cppunit\extensions\TestFactoryRegistry.h>
#include <cppunit\ui\text\TestRunner.h>

#include <iostream>

#include "Parser.h"
#include "DesignExtractor.h"

int main()
{
	CPPUNIT_NS::Test* suite = CPPUNIT_NS::TestFactoryRegistry::getRegistry().makeTest();

	CppUnit::TextUi::TestRunner runner;
	runner.addTest(suite);
	bool wasSuccessful = runner.run();

	getchar();

	return (wasSuccessful) ? 0 : 1;

	//Parser parser;
	//DesignExtractor extractor;

	//PKB* pkb;

	//try {
	//	pkb = parser.parse("Test.txt");
	//	extractor.extract(pkb);
	//} catch (ParseException pe) {
	//	cout << pe.what();
	//	getchar();
	//	return 0;
	//}
}