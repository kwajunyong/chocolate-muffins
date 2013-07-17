#pragma once

#include <cppunit\extensions\HelperMacros.h>
#include "Parent.h"

class TestParent : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE(TestParent);

	CPPUNIT_TEST(testAddParent);

	CPPUNIT_TEST(testIsParent);
	CPPUNIT_TEST(testIsTransitiveParent);

	CPPUNIT_TEST(testGetChild);
	CPPUNIT_TEST(testGetTransitiveChild);
	
	CPPUNIT_TEST(testGetParent);
	CPPUNIT_TEST(testGetTransitiveParent);

	CPPUNIT_TEST_SUITE_END();
public:
	void setUp();
	void tearDown();

	void testAddParent();

	void testIsParent();
	void testIsTransitiveParent();

	void testGetChild();
	void testGetTransitiveChild();

	void testGetParent();
	void testGetTransitiveParent();

private:
	Parent parent;

	void generateParent();
};

