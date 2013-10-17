#include <cppunit\config\SourcePrefix.h>

#include "TestProcTable.h"

void TestProcTable::setUp()
{}

void TestProcTable::tearDown()
{}

CPPUNIT_TEST_SUITE_REGISTRATION(TestProcTable);

void TestProcTable::testAddProcedure()
{
	CPPUNIT_ASSERT_EQUAL(true, procTable.addProcedure("a", 1, 2));
	CPPUNIT_ASSERT_EQUAL(false, procTable.addProcedure("a", 1, 2));
	CPPUNIT_ASSERT_EQUAL(false, procTable.addProcedure("a", 3, 4));
}

void TestProcTable::testGetIndex()
{
	generateProcedures();

	CPPUNIT_ASSERT_EQUAL(0, procTable.getIndex("Alpha"));
	CPPUNIT_ASSERT_EQUAL(1, procTable.getIndex("Bravo"));
	CPPUNIT_ASSERT_EQUAL(2, procTable.getIndex("Charlie"));
	CPPUNIT_ASSERT_EQUAL(3, procTable.getIndex("Delta"));

	CPPUNIT_ASSERT_EQUAL(-1, procTable.getIndex("Ninja"));
}

void TestProcTable::testGetName()
{
	generateProcedures();

	CPPUNIT_ASSERT("Alpha" == procTable.getName(0));
	CPPUNIT_ASSERT("Bravo" == procTable.getName(1));
	CPPUNIT_ASSERT("Charlie" == procTable.getName(2));
	CPPUNIT_ASSERT("Delta" == procTable.getName(3));
	
	CPPUNIT_ASSERT_THROW(procTable.getName(-1), std::out_of_range);
	CPPUNIT_ASSERT_THROW(procTable.getName(4), std::out_of_range);
}

void TestProcTable::testGetProcedure()
{
	generateProcedures();

	CPPUNIT_ASSERT("Alpha" == procTable.getProcedure(1));
	CPPUNIT_ASSERT("Bravo" == procTable.getProcedure(3));
	CPPUNIT_ASSERT("Charlie" == procTable.getProcedure(5));
	CPPUNIT_ASSERT("Delta" == procTable.getProcedure(9));
	
	CPPUNIT_ASSERT_THROW(procTable.getProcedure(0), std::out_of_range);
	CPPUNIT_ASSERT_THROW(procTable.getProcedure(11), std::out_of_range);
}

void TestProcTable::testGetAllNames()
{
	generateProcedures();

	std::vector<std::string> expected;

	std::string temp[] = {"Alpha", "Bravo", "Charlie", "Delta"};
	expected.assign(temp, temp + 4);
	CPPUNIT_ASSERT(expected == procTable.getAllNames());
}

void TestProcTable::testGetSize()
{
	generateProcedures();

	CPPUNIT_ASSERT_EQUAL(4, procTable.getSize());
}

void TestProcTable::generateProcedures()
{
	procTable.addProcedure("Alpha", 1, 1);
	procTable.addProcedure("Bravo", 2, 3);
	procTable.addProcedure("Charlie", 4, 6);
	procTable.addProcedure("Delta", 7, 10);
}