#pragma once

#include <cppunit\extensions\HelperMacros.h>

#include "Parser.h"
#include "DesignExtractor.h"

class TestDesignExtractor : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE(TestDesignExtractor);

	CPPUNIT_TEST(testExtract);

	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	void testExtract();

private:
	Parser parser;
	DesignExtractor extractor;
};