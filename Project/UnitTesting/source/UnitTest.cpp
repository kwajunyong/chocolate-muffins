#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>

#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
	// Get the top level suite from the registry
	CppUnit::TestSuite *unitSuite = new CppUnit::TestSuite( "All unit test" );
	
	unitSuite->addTest(CppUnit::TestFactoryRegistry::getRegistry("TestASTNode").makeTest());	
	unitSuite->addTest(CppUnit::TestFactoryRegistry::getRegistry("TestAST").makeTest());
	unitSuite->addTest(CppUnit::TestFactoryRegistry::getRegistry("TestVarTable").makeTest());
	unitSuite->addTest(CppUnit::TestFactoryRegistry::getRegistry("TestProcTable").makeTest());
	unitSuite->addTest(CppUnit::TestFactoryRegistry::getRegistry("TestFollows").makeTest());
	unitSuite->addTest(CppUnit::TestFactoryRegistry::getRegistry("TestParent").makeTest());
	unitSuite->addTest(CppUnit::TestFactoryRegistry::getRegistry("TestModifies").makeTest());
	unitSuite->addTest(CppUnit::TestFactoryRegistry::getRegistry("TestUses").makeTest());
	unitSuite->addTest(CppUnit::TestFactoryRegistry::getRegistry("TestParser").makeTest());
	unitSuite->addTest(CppUnit::TestFactoryRegistry::getRegistry("TestDesignExtractor").makeTest());
	
	CppUnit::TestFactoryRegistry::getRegistry().addTestToSuite(unitSuite);
	
	CppUnit::TextUi::TestRunner runner;
	runner.addTest(unitSuite);
	
	bool wasSucessful = runner.run();

	getchar();

	return wasSucessful ? 0 : 1;
}