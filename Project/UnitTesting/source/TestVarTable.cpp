#include <cppunit\config\SourcePrefix.h>

#include "TestVarTable.h"

void TestVarTable::setUp()
{}

void TestVarTable::tearDown()
{}

CPPUNIT_TEST_SUITE_REGISTRATION(TestVarTable);

void TestVarTable::testAddVariable()
{
	CPPUNIT_ASSERT_EQUAL(0, varTable.addVariable("a"));
	CPPUNIT_ASSERT_EQUAL(0, varTable.addVariable("a"));
}

void TestVarTable::testGetIndex()
{
	generateVariables();

	CPPUNIT_ASSERT_EQUAL(0, varTable.getIndex("i"));
	CPPUNIT_ASSERT_EQUAL(2, varTable.getIndex("k"));
	CPPUNIT_ASSERT_EQUAL(5, varTable.getIndex("z"));

	CPPUNIT_ASSERT_EQUAL(-1, varTable.getIndex("c"));
}

void TestVarTable::testGetName()
{
	generateVariables();

	CPPUNIT_ASSERT("i" == varTable.getName(0));
	CPPUNIT_ASSERT("k" == varTable.getName(2));
	CPPUNIT_ASSERT("z" == varTable.getName(5));
	
	CPPUNIT_ASSERT_THROW(varTable.getName(-1), std::out_of_range);
	CPPUNIT_ASSERT_THROW(varTable.getName(6), std::out_of_range);
}

void TestVarTable::testGetSize()
{
	generateVariables();

	CPPUNIT_ASSERT_EQUAL(6, varTable.getSize());
}

void TestVarTable::generateVariables()
{
	varTable.addVariable("i");
	varTable.addVariable("j");
	varTable.addVariable("k");
	varTable.addVariable("x");
	varTable.addVariable("y");
	varTable.addVariable("z");
}