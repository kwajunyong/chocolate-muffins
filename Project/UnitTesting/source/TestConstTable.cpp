#include <cppunit\config\SourcePrefix.h>

#include "TestConstTable.h"

void TestConstTable::setUp()
{}

void TestConstTable::tearDown()
{}

CPPUNIT_TEST_SUITE_REGISTRATION(TestConstTable);

void TestConstTable::testAddConstant()
{
	CPPUNIT_ASSERT_EQUAL(true, constTable.addConstant(21));
	CPPUNIT_ASSERT_EQUAL(false, constTable.addConstant(21));
}

void TestConstTable::testGetIndex()
{
	generateConstants();

	CPPUNIT_ASSERT_EQUAL(0, constTable.getIndex(1));
	CPPUNIT_ASSERT_EQUAL(2, constTable.getIndex(3));
	CPPUNIT_ASSERT_EQUAL(5, constTable.getIndex(13));

	CPPUNIT_ASSERT_EQUAL(-1, constTable.getIndex(21));
}

void TestConstTable::testGetValue()
{
	generateConstants();

	CPPUNIT_ASSERT_EQUAL(1, constTable.getValue(0));
	CPPUNIT_ASSERT_EQUAL(3, constTable.getValue(2));
	CPPUNIT_ASSERT_EQUAL(13, constTable.getValue(5));
	
	CPPUNIT_ASSERT_THROW(constTable.getValue(-1), std::out_of_range);
	CPPUNIT_ASSERT_THROW(constTable.getValue(6), std::out_of_range);
}

void TestConstTable::testGetAllValues()
{
	generateConstants();

	std::vector<int> expected;

	int temp[] = {1, 2, 3, 5, 8, 13};
	expected.assign(temp, temp + 6);
	CPPUNIT_ASSERT(expected == constTable.getAllValues());
}

void TestConstTable::testGetSize()
{
	generateConstants();

	CPPUNIT_ASSERT_EQUAL(6, constTable.getSize());
}

void TestConstTable::generateConstants()
{
	constTable.addConstant(1);
	constTable.addConstant(2);
	constTable.addConstant(3);
	constTable.addConstant(5);
	constTable.addConstant(8);
	constTable.addConstant(13);
}