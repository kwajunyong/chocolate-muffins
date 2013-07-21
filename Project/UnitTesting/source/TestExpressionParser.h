#pragma once

#include <cppunit\extensions\HelperMacros.h>

#include <vector>

#include "ExpressionParser.h"
#include "AST.h"

class TestExpressionParser : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE(TestExpressionParser);

	CPPUNIT_TEST(testParse);

	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	void testParse();

private:
	AST ast;

	std::vector<std::string> expectedOne();
	std::vector<std::string> expectedTwo();
	std::vector<std::string> expectedThree();
	std::vector<std::string> expectedFour();
	std::vector<std::string> expectedFive();
};