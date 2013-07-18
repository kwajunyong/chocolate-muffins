#pragma once

#include <cppunit\extensions\HelperMacros.h>

#include "VarTable.h"

class TestVarTable : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE(TestVarTable);

	CPPUNIT_TEST(testAddVariable);
	CPPUNIT_TEST(testGetIndex);
	CPPUNIT_TEST(testGetName);
	CPPUNIT_TEST(testGetAllNames);
	CPPUNIT_TEST(testGetSize);

	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	void testAddVariable();
	void testGetIndex();
	void testGetName();
	void testGetAllNames();
	void testGetSize();

private:
	VarTable varTable;

	void generateVariables();
};
