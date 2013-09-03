#include <cppunit\config\SourcePrefix.h>

#include "TestExpressionParser.h"

void TestExpressionParser::setUp()
{}

void TestExpressionParser::tearDown()
{}

CPPUNIT_TEST_SUITE_REGISTRATION(TestExpressionParser);

void TestExpressionParser::testParse()
{
	ASTNode* node;

	/*ASTNode* node1 = ast.buildExpressionNode("m");
	CPPUNIT_ASSERT(expectedOne() == ast.traverse(node1));

	ASTNode* node2 = ast.buildExpressionNode("m + n");
	CPPUNIT_ASSERT(expectedTwo() == ast.traverse(node2));

	node = ast.buildExpressionNode("m + n - 1");
	CPPUNIT_ASSERT(expectedThree() == ast.traverse(node));

	node = ast.buildExpressionNode("m + n * 1");
	CPPUNIT_ASSERT(expectedFour() == ast.traverse(node));

	node = ast.buildExpressionNode("(m + n) * 1");
	CPPUNIT_ASSERT(expectedFive() == ast.traverse(node));*/
}

std::vector<std::string> TestExpressionParser::expectedOne()
{
	std::vector<std::string> expected;

	expected.push_back("m:variable");

	return expected;
}

std::vector<std::string> TestExpressionParser::expectedTwo()
{
	std::vector<std::string> expected;

	expected.push_back(":plus");
	expected.push_back("  m:variable");
	expected.push_back("  n:variable");
	
	return expected;
}

std::vector<std::string> TestExpressionParser::expectedThree()
{
	std::vector<std::string> expected;

	expected.push_back(":minus");
	expected.push_back("  :plus");
	expected.push_back("    m:variable");
	expected.push_back("    n:variable");
	expected.push_back("  1:constant");
	

	return expected;
}

std::vector<std::string> TestExpressionParser::expectedFour()
{
	std::vector<std::string> expected;

	expected.push_back(":plus");
	expected.push_back("  m:variable");
	expected.push_back("  :times");
	expected.push_back("    n:variable");
	expected.push_back("    1:constant");	

	return expected;
}

std::vector<std::string> TestExpressionParser::expectedFive()
{
	std::vector<std::string> expected;

	expected.push_back(":times");
	expected.push_back("  :plus");
	expected.push_back("    m:variable");
	expected.push_back("    n:variable");
	expected.push_back("  1:constant");

	return expected;
}