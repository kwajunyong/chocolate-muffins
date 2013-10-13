#include <cppunit\config\SourcePrefix.h>

#include "TestCalls.h"

CPPUNIT_TEST_SUITE_REGISTRATION(TestCalls);

void TestCalls::testAddCalls()
{
	CPPUNIT_ASSERT_EQUAL(true, c.addCalls("Alpha", "Bravo", 1));
}

void TestCalls::testIsCalls()
{
	c.addCalls("Alpha", "Bravo", 1);
	c.addCalls("Bravo", "Charlie", 2);
	c.addCalls("Delta", "Echo", 3);

	CPPUNIT_ASSERT_EQUAL(true, c.isCalls("Alpha", "Bravo", false));
	CPPUNIT_ASSERT_EQUAL(false, c.isCalls("Alpha", "Charlie", false));
	CPPUNIT_ASSERT_EQUAL(false, c.isCalls("Alpha", "Foxtrot", false));

	CPPUNIT_ASSERT_EQUAL(true, c.isCalls("Alpha", "Bravo", true));
	CPPUNIT_ASSERT_EQUAL(true, c.isCalls("Alpha", "Charlie", true));
	CPPUNIT_ASSERT_EQUAL(false, c.isCalls("Alpha", "Echo", true));
}

void TestCalls::testGetCalls()
{
	vector<string> calls;
	vector<string> transitiveCalls;

	c.addCalls("Alpha", "Bravo", 1);
	c.addCalls("Bravo", "Charlie", 2);
	c.addCalls("Delta", "Echo", 3);
	c.addCalls("Delta", "Charlie", 4);

	CPPUNIT_ASSERT(c.getCalls("Charlie", false) == calls);

	calls.push_back("Bravo");
	CPPUNIT_ASSERT(c.getCalls("Alpha", false) == calls);

	CPPUNIT_ASSERT(c.getCalls("Charlie", true) == transitiveCalls);

	transitiveCalls.push_back("Bravo");
	transitiveCalls.push_back("Charlie");
	CPPUNIT_ASSERT(c.getCalls("Alpha", true) == transitiveCalls);
}

void TestCalls::testGetCalled()
{
	vector<string> called;
	vector<string> transitiveCalled;

	c.addCalls("Alpha", "Bravo", 1);
	c.addCalls("Bravo", "Charlie", 2);
	c.addCalls("Delta", "Echo", 3);
	c.addCalls("Delta", "Charlie", 4);

	CPPUNIT_ASSERT(c.getCalled("Alpha", false) == called);

	called.push_back("Bravo");
	called.push_back("Delta");
	CPPUNIT_ASSERT(c.getCalled("Charlie", false) == called);

	CPPUNIT_ASSERT(c.getCalled("Charlie", true) == transitiveCalled);

	transitiveCalled.push_back("Bravo");
	transitiveCalled.push_back("Delta");
	transitiveCalled.push_back("Alpha");
	CPPUNIT_ASSERT(c.getCalled("Charlie", true) == transitiveCalled);
}

void TestCalls::testGetCallsStmt()
{
	vector<int> callsStmt;

	c.addCalls("Alpha", "Bravo", 1);
	c.addCalls("Bravo", "Charlie", 2);
	c.addCalls("Delta", "Echo", 3);
	c.addCalls("Delta", "Charlie", 4);

	CPPUNIT_ASSERT(c.getCallsStmt("Alpha") == callsStmt);
	CPPUNIT_ASSERT(c.getCallsStmt("Delta") == callsStmt);

	callsStmt.push_back(1);
	CPPUNIT_ASSERT(c.getCallsStmt("Bravo") == callsStmt);

	callsStmt.clear();
	callsStmt.push_back(2);
	callsStmt.push_back(4);
	CPPUNIT_ASSERT(c.getCallsStmt("Charlie") == callsStmt);
}