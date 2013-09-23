#pragma once

#include <cppunit\extensions\HelperMacros.h>

#include "Parser.h"

class TestParser : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE(TestParser);

	CPPUNIT_TEST(testParse);

	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	void testParse();

private:
	Parser parser;
};