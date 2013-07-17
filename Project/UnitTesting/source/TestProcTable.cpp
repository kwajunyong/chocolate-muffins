#include <cppunit\config\SourcePrefix.h>

#include "TestProcTable.h"

void TestProcTable::setUp()
{}

void TestProcTable::tearDown()
{}

CPPUNIT_TEST_SUITE_REGISTRATION(TestProcTable);

void TestProcTable::testAddProcedure()
{
	CPPUNIT_ASSERT_EQUAL(0, procTable.addProcedure("a"));
	CPPUNIT_ASSERT_EQUAL(0, procTable.addProcedure("a"));
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

void TestProcTable::testGetSize()
{
	generateProcedures();

	CPPUNIT_ASSERT_EQUAL(4, procTable.getSize());
}

void TestProcTable::generateProcedures()
{
	procTable.addProcedure("Alpha");
	procTable.addProcedure("Bravo");
	procTable.addProcedure("Charlie");
	procTable.addProcedure("Delta");
}