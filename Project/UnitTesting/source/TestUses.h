#pragma once

#include <cppunit\extensions\HelperMacros.h>

#include <vector>
#include <algorithm>

#include "Uses.h"

class TestUses : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE(TestUses);

	CPPUNIT_TEST(testAddUsesStmt);
	CPPUNIT_TEST(testAddUsesProc);

	CPPUNIT_TEST(testIsUsesStmt);
	CPPUNIT_TEST(testIsUsesProc);

	CPPUNIT_TEST(testGetUsedVar);

	CPPUNIT_TEST(testGetUsesStmt);
	CPPUNIT_TEST(testGetUsesProc);

	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	void testAddUsesStmt();
	void testAddUsesProc();

	void testIsUsesStmt();
	void testIsUsesProc();

	void testGetUsedVar();

	void testGetUsesStmt();
	void testGetUsesProc();

private:
	Uses* uses;

	Uses* buildUses();

	void generateUses();
};