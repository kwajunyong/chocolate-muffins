#pragma once

#include <cppunit\extensions\HelperMacros.h>

#include "ProcTable.h"

class TestProcTable : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE(TestProcTable);

	CPPUNIT_TEST(testAddProcedure);
	CPPUNIT_TEST(testGetIndex);
	CPPUNIT_TEST(testGetName);
	CPPUNIT_TEST(testGetAllNames);
	CPPUNIT_TEST(testGetSize);

	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	void testAddProcedure();
	void testGetIndex();
	void testGetName();
	void testGetProcedure();
	void testGetAllNames();
	void testGetSize();

private:
	ProcTable procTable;

	void generateProcedures();
};