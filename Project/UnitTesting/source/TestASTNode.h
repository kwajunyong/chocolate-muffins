#pragma once

#include <cppunit\extensions\HelperMacros.h>

class TestASTNode: public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE(TestASTNode);
	CPPUNIT_TEST(testConstructor);
	CPPUNIT_TEST(testPrint);
	CPPUNIT_TEST(testEqual);
	CPPUNIT_TEST(testJoinChild);
	CPPUNIT_TEST(testJoinNext);
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	void testConstructor();
	void testPrint();
	void testEqual();
	void testJoinChild();
	void testJoinNext();
};

