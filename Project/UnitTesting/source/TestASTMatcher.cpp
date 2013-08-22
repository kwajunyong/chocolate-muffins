#include <cppunit\config\SourcePrefix.h>

#include "TestASTMatcher.h"

void TestASTMatcher::setUp()
{
	testNode = buildTree();
}

void TestASTMatcher::tearDown()
{}

CPPUNIT_TEST_SUITE_REGISTRATION(TestASTMatcher);

void TestASTMatcher::testMatchTree()
{
	CPPUNIT_ASSERT_EQUAL(true, matcher.matchTree(NULL, NULL));
	CPPUNIT_ASSERT_EQUAL(false, matcher.matchTree(testNode, NULL));
	CPPUNIT_ASSERT_EQUAL(false, matcher.matchTree(NULL, testNode));
	
	ASTNode* node = buildTree();
	CPPUNIT_ASSERT_EQUAL(true, matcher.matchTree(testNode, node));
	
	node = buildTreeWithDiffValue();
	CPPUNIT_ASSERT_EQUAL(false, matcher.matchTree(testNode, node));
	
	node = buildSubTree();
	CPPUNIT_ASSERT_EQUAL(false, matcher.matchTree(testNode, node));
}

void TestASTMatcher::testMatchSubTree()
{	
	CPPUNIT_ASSERT_EQUAL(true, matcher.matchSubTree(NULL, NULL));
	CPPUNIT_ASSERT_EQUAL(true, matcher.matchSubTree(testNode, NULL));
	CPPUNIT_ASSERT_EQUAL(false, matcher.matchSubTree(NULL, testNode));

	ASTNode* node = buildTree();
	CPPUNIT_ASSERT_EQUAL(true, matcher.matchSubTree(testNode, node));

	node = buildSubTree();
	CPPUNIT_ASSERT_EQUAL(true, matcher.matchSubTree(testNode, node));

	node = buildSubTreeWithDiffValue();
	CPPUNIT_ASSERT_EQUAL(false, matcher.matchSubTree(testNode, node));

	node = buildSubTreeWithDiffStruct();
	CPPUNIT_ASSERT_EQUAL(false, matcher.matchSubTree(testNode, node));
}

ASTNode* TestASTMatcher::buildTree()
{
	ASTNode* assignNode = new ASTNode("", ASSIGN, 1);
	ASTNode* plusNode = new ASTNode("", PLUS, 0);
	ASTNode* minusNode = new ASTNode("", MINUS, 0);
	ASTNode* varNodeA = new ASTNode("a", VARIABLE, 0);
	ASTNode* varNodeB = new ASTNode("b", VARIABLE, 0);
	ASTNode* varNodeC = new ASTNode("c", VARIABLE, 0);
	ASTNode* constantNode = new ASTNode("1", CONSTANT, 0);

	assignNode->joinChild(varNodeA);
	varNodeA->joinNext(minusNode);
	minusNode->joinChild(plusNode);
	plusNode->joinChild(varNodeB);
	varNodeB->joinNext(varNodeC);
	plusNode->joinNext(constantNode);

	return assignNode;
}

ASTNode* TestASTMatcher::buildTreeWithDiffValue()
{
	ASTNode* assignNode = new ASTNode("", ASSIGN, 1);
	ASTNode* timesNode = new ASTNode("", TIMES, 0);
	ASTNode* divideNode = new ASTNode("", DIVIDE, 0);
	ASTNode* varNodeA = new ASTNode("a", VARIABLE, 0);
	ASTNode* varNodeB = new ASTNode("b", VARIABLE, 0);
	ASTNode* varNodeC = new ASTNode("c", VARIABLE, 0);
	ASTNode* constantNode = new ASTNode("1", CONSTANT, 0);

	assignNode->joinChild(varNodeA);
	varNodeA->joinNext(divideNode);
	divideNode->joinChild(timesNode);
	timesNode->joinChild(varNodeB);
	varNodeB->joinNext(varNodeC);
	timesNode->joinNext(constantNode);

	return assignNode;
}

ASTNode* TestASTMatcher::buildSubTree()
{
	ASTNode* plusNode = new ASTNode("", PLUS, 0);
	ASTNode* minusNode = new ASTNode("", MINUS, 0);
	ASTNode* varNodeB = new ASTNode("b", VARIABLE, 0);
	ASTNode* varNodeC = new ASTNode("c", VARIABLE, 0);
	ASTNode* constantNode = new ASTNode("1", CONSTANT, 0);

	minusNode->joinChild(plusNode);
	plusNode->joinChild(varNodeB);
	varNodeB->joinNext(varNodeC);
	plusNode->joinNext(constantNode);

	return minusNode;
}

ASTNode* TestASTMatcher::buildSubTreeWithDiffValue()
{
	ASTNode* timesNode = new ASTNode("", TIMES, 0);
	ASTNode* divideNode = new ASTNode("", DIVIDE, 0);
	ASTNode* varNodeB = new ASTNode("b", VARIABLE, 0);
	ASTNode* varNodeC = new ASTNode("c", VARIABLE, 0);
	ASTNode* constantNode = new ASTNode("1", CONSTANT, 0);

	divideNode->joinChild(timesNode);
	timesNode->joinChild(varNodeB);
	varNodeB->joinNext(varNodeC);
	timesNode->joinNext(constantNode);

	return timesNode;
}

ASTNode* TestASTMatcher::buildSubTreeWithDiffStruct()
{
	ASTNode* plusNode = new ASTNode("", PLUS, 0);
	ASTNode* minusNode = new ASTNode("", MINUS, 0);
	ASTNode* varNodeB = new ASTNode("b", VARIABLE, 0);
	ASTNode* varNodeC = new ASTNode("c", VARIABLE, 0);
	ASTNode* constantNode = new ASTNode("1", CONSTANT, 0);

	plusNode->joinChild(varNodeB);
	varNodeB->joinNext(minusNode);
	minusNode->joinChild(varNodeC);
	varNodeC->joinNext(constantNode);

	return plusNode;
}