#pragma once

#include <cppunit\extensions\HelperMacros.h>
#include "Follows.h"

class TestFollows : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE(TestFollows);

	CPPUNIT_TEST(testAddFollows);

	CPPUNIT_TEST(testIsFollows);
	CPPUNIT_TEST(testIsTransitiveFollows);

	CPPUNIT_TEST(testGetFollowedBy);
	CPPUNIT_TEST(testGetTransitiveFollowedBy);

	CPPUNIT_TEST(testGetFollows);
	CPPUNIT_TEST(testGetTransitiveFollows);

	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	void testAddFollows();

	void testIsFollows();
	void testIsTransitiveFollows();

	void testGetFollowedBy();
	void testGetTransitiveFollowedBy();

	void testGetFollows();
	void testGetTransitiveFollows();

private:
	Follows follows;

	void generateFollows();
};