#pragma once

#include <cppunit\extensions\HelperMacros.h>
#include "Calls.h"

class TestCalls : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE(TestCalls);

	CPPUNIT_TEST_SUITE_END();
public:
	void testAddCalls();
	void testIsCalls();

	void testGetCalls();
	void testGetCalled();
	void testGetCallsStmt();
private:
	Calls c;
};