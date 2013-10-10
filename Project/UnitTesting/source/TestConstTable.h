#pragma once

#include <cppunit\extensions\HelperMacros.h>

#include "ConstTable.h"

class TestConstTable : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE(TestConstTable);

	CPPUNIT_TEST(testAddConstant);
	CPPUNIT_TEST(testGetIndex);
	CPPUNIT_TEST(testGetValue);
	CPPUNIT_TEST(testGetAllValues);
	CPPUNIT_TEST(testGetSize);

	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	void testAddConstant();
	void testGetIndex();
	void testGetValue();
	void testGetAllValues();
	void testGetSize();

private:
	ConstTable constTable;

	void generateConstants();
};
