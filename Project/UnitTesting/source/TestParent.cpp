#include <cppunit\config\SourcePrefix.h>

#include "TestParent.h"

void TestParent::setUp()
{}

void TestParent::tearDown()
{}

CPPUNIT_TEST_SUITE_REGISTRATION(TestParent);

void TestParent::testAddParent()
{
	CPPUNIT_ASSERT_EQUAL(true, parent.addParent(1, 2));

	CPPUNIT_ASSERT_EQUAL(false, parent.addParent(1, 2));
}

void TestParent::testIsParent()
{
	generateParent();

	CPPUNIT_ASSERT_EQUAL(true, parent.isParent(1, 2, false));

	CPPUNIT_ASSERT_EQUAL(false, parent.isParent(1, 4, false));

	CPPUNIT_ASSERT_EQUAL(false, parent.isParent(6, 7, false));
}

void TestParent::testIsTransitiveParent()
{
	generateParent();

	CPPUNIT_ASSERT_EQUAL(true, parent.isParent(1, 2, true));

	CPPUNIT_ASSERT_EQUAL(true, parent.isParent(1, 4, true));

	CPPUNIT_ASSERT_EQUAL(false, parent.isParent(6, 7, true));
}

void TestParent::testGetChild()
{
	generateParent();

	vector<int> expected;

	int temp[] = {2, 6, 7};
	expected.assign(temp, temp + 3);
	CPPUNIT_ASSERT(parent.getChild(1, false) == expected);

	expected.clear();
	CPPUNIT_ASSERT(parent.getChild(8, false) == expected);
}

void TestParent::testGetTransitiveChild()
{
	generateParent();

	vector<int> expected;

	int temp[] = {2, 3, 4, 5, 6, 7};
	expected.assign(temp, temp + 6);
	CPPUNIT_ASSERT(parent.getChild(1, true) == expected);

	expected.clear();
	CPPUNIT_ASSERT(parent.getChild(8, true) == expected);
}

void TestParent::testGetParent()
{
	generateParent();

	vector<int> expected;

	int temp[] = {3};
	expected.assign(temp, temp + 1);
	CPPUNIT_ASSERT(parent.getParent(4, false) == expected);

	expected.clear();
	CPPUNIT_ASSERT(parent.getParent(8, false) == expected);
}

void TestParent::testGetTransitiveParent()
{
	generateParent();

	vector<int> expected;

	int temp[] = {3, 2, 1};
	expected.assign(temp, temp + 3);
	CPPUNIT_ASSERT(parent.getParent(4, true) == expected);

	expected.clear();
	CPPUNIT_ASSERT(parent.getParent(8, true) == expected);
}

void TestParent::generateParent()
{
	parent.addParent(1, 2);
	parent.addParent(2, 3);
	parent.addParent(3, 4);
	parent.addParent(2, 5);
	parent.addParent(1, 6);
	parent.addParent(1, 7);
}