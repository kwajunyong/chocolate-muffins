#include <cppunit\config\SourcePrefix.h>

#include "TestFollows.h"

void TestFollows::setUp()
{}

void TestFollows::tearDown()
{}

CPPUNIT_TEST_SUITE_REGISTRATION(TestFollows);

void TestFollows::testAddFollows()
{	
	CPPUNIT_ASSERT_EQUAL(true, follows.addFollows(1,2));

	CPPUNIT_ASSERT_EQUAL(false, follows.addFollows(1,2));
}

void TestFollows::testIsFollows()
{	
	generateFollows();

	CPPUNIT_ASSERT_EQUAL(true, follows.isFollows(1, 2, false));
	
	CPPUNIT_ASSERT_EQUAL(false, follows.isFollows(1, 3, false));

	CPPUNIT_ASSERT_EQUAL(false, follows.isFollows(4, 5, false));
}

void TestFollows::testIsTransitiveFollows()
{	
	generateFollows();

	CPPUNIT_ASSERT_EQUAL(true, follows.isFollows(1, 2, true));
	
	CPPUNIT_ASSERT_EQUAL(true, follows.isFollows(1, 3, true));

	CPPUNIT_ASSERT_EQUAL(false, follows.isFollows(4, 5, true));
}

void TestFollows::testGetFollowedBy()
{
	generateFollows();

	std::vector<int> expected;

	expected.push_back(2);
	CPPUNIT_ASSERT(follows.getFollowedBy(1, false) == expected);

	expected.clear();
	CPPUNIT_ASSERT(follows.getFollowedBy(5, false) == expected);
}

void TestFollows::testGetTransitiveFollowedBy()
{
	generateFollows();

	std::vector<int> expected;

	int temp[] = {2, 3, 4};
	expected.assign(temp, temp + 3);
	CPPUNIT_ASSERT(follows.getFollowedBy(1, true) == expected);

	expected.clear();
	CPPUNIT_ASSERT(follows.getFollowedBy(5, true) == expected);
}

void TestFollows::testGetFollows()
{
	generateFollows();

	std::vector<int> expected;

	expected.push_back(3);
	CPPUNIT_ASSERT(follows.getFollows(4, false) == expected);

	expected.clear();
	CPPUNIT_ASSERT(follows.getFollows(5, false) == expected);
}

void TestFollows::testGetTransitiveFollows()
{
	generateFollows();

	std::vector<int> expected;

	int temp[] = {3, 2, 1};
	expected.assign(temp, temp + 3);
	CPPUNIT_ASSERT(follows.getFollows(4, true) == expected);

	expected.clear();
	CPPUNIT_ASSERT(follows.getFollows(5, true) == expected);
}

void TestFollows::generateFollows()
{
	follows.addFollows(1,2);
	follows.addFollows(2,3);
	follows.addFollows(3,4);
	follows.addFollows(6,7);
	follows.addFollows(8,9);
}