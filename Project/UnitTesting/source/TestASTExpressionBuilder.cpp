#include <cppunit\config\SourcePrefix.h>

#include "TestASTExpressionBuilder.h"

void TestASTExpressionBuilder::setUp()
{}

void TestASTExpressionBuilder::tearDown()
{}

CPPUNIT_TEST_SUITE_REGISTRATION(TestASTExpressionBuilder);

void TestASTExpressionBuilder::testBuild()
{
	ASTNode* node;

	ASTNode* node1 = exprBuilder.build("m");
	CPPUNIT_ASSERT(expectedOne() == traverser.traverse(node1));

	ASTNode* node2 = exprBuilder.build("m + n");
	CPPUNIT_ASSERT(expectedTwo() == traverser.traverse(node2));

	node = exprBuilder.build("m + n - 1");
	CPPUNIT_ASSERT(expectedThree() == traverser.traverse(node));

	node = exprBuilder.build("m + n * 1");
	CPPUNIT_ASSERT(expectedFour() == traverser.traverse(node));

	node = exprBuilder.build("(m + n) * 1");
	CPPUNIT_ASSERT(expectedFive() == traverser.traverse(node));
}

std::vector<std::string> TestASTExpressionBuilder::expectedOne()
{
	std::vector<std::string> expected;

	expected.push_back("m:variable");

	return expected;
}

std::vector<std::string> TestASTExpressionBuilder::expectedTwo()
{
	std::vector<std::string> expected;

	expected.push_back(":plus");
	expected.push_back("  m:variable");
	expected.push_back("  n:variable");
	
	return expected;
}

std::vector<std::string> TestASTExpressionBuilder::expectedThree()
{
	std::vector<std::string> expected;

	expected.push_back(":minus");
	expected.push_back("  :plus");
	expected.push_back("    m:variable");
	expected.push_back("    n:variable");
	expected.push_back("  1:constant");
	

	return expected;
}

std::vector<std::string> TestASTExpressionBuilder::expectedFour()
{
	std::vector<std::string> expected;

	expected.push_back(":plus");
	expected.push_back("  m:variable");
	expected.push_back("  :times");
	expected.push_back("    n:variable");
	expected.push_back("    1:constant");	

	return expected;
}

std::vector<std::string> TestASTExpressionBuilder::expectedFive()
{
	std::vector<std::string> expected;

	expected.push_back(":times");
	expected.push_back("  :plus");
	expected.push_back("    m:variable");
	expected.push_back("    n:variable");
	expected.push_back("  1:constant");

	return expected;
}