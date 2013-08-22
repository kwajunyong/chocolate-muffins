#pragma once

#include <cppunit\extensions\HelperMacros.h>

#include <vector>

#include "ASTExpressionBuilder.h"
#include "ASTTraverser.h"

class TestASTExpressionBuilder : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE(TestASTExpressionBuilder);

	CPPUNIT_TEST(testBuild);

	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	void testBuild();

private:
	ASTExpressionBuilder exprBuilder;
	ASTTraverser traverser;

	std::vector<std::string> expectedOne();
	std::vector<std::string> expectedTwo();
	std::vector<std::string> expectedThree();
	std::vector<std::string> expectedFour();
	std::vector<std::string> expectedFive();
};