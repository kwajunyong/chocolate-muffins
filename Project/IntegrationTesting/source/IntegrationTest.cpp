#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include <iostream>
#include "ListManager.h"
using namespace std;

int main(int argc, char* argv[])
{

	// hendri uses to test listmanager
	   ListManager lm; 

	   vector<string>  va; 
	   va.push_back("1");	   
	   va.push_back("3");	   
	   va.push_back("2");
	   va.push_back("5");
	   va.push_back("4");
	   va.push_back("8");
	   lm.updateList("a", va);


	   vector<string>  vb; 
	   vb.push_back("a");	   
	   vb.push_back("b");	   
	   vb.push_back("e");
	   vb.push_back("g");
	   vb.push_back("h");
	   vb.push_back("x");


	   lm.updateList("b", vb);


	   vector<pair<string, string>> ABRelationship;
	   pair<string, string> pair1("1", "a");
	   pair<string, string> pair2("1", "b");
	   pair<string, string> pair3("1", "c");
	   pair<string, string> pair4("2", "a");
	   pair<string, string> pair5("2", "x");
	   pair<string, string> pair6("2", "j");

	   ABRelationship.push_back(pair1);
	   ABRelationship.push_back(pair2);
	   ABRelationship.push_back(pair3);
	   ABRelationship.push_back(pair4);
	   ABRelationship.push_back(pair5);
	   ABRelationship.push_back(pair6);

	   lm.updateList("x", "y", ABRelationship);


	   vector<pair<string, string>> abRelationship;
	   pair<string, string> apair1("1", "sam");
	   pair<string, string> apair2("1", "linda");
	   pair<string, string> apair3("2", "susi");
	   pair<string, string> apair4("2", "yanto");
	   pair<string, string> apair5("3", "lisa");
	   pair<string, string> apair6("3", "melinda");

	   abRelationship.push_back(apair1);
	   abRelationship.push_back(apair2);
	   abRelationship.push_back(apair3);
	   abRelationship.push_back(apair4);
	   abRelationship.push_back(apair5);
	   abRelationship.push_back(apair6);

	   lm.updateList("x", "c", abRelationship);

	   vector<string>  varefined; 
	   varefined.push_back("1");
	   varefined.push_back("2");
	   varefined.push_back("4");
	   varefined.push_back("10");


	   lm.updateList("a", varefined);

	   int a;
	   cin  >> a;
	/*
	  
	
	// Get the top level suite from the registry
	CPPUNIT_NS::Test *suite = CPPUNIT_NS::TestFactoryRegistry::getRegistry().makeTest();
	CppUnit::TextUi::TestRunner runner;

	//parse the SIMPLE soource code into the parser
	//Parse();

	//Call of DesignExtractor
	//Extract();

	runner.addTest(suite);
	bool wasSucessful = runner.run();

	getchar();

	return wasSucessful ? 0 : 1; */
}