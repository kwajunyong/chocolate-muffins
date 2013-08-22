#pragma once

#include <cppunit\extensions\HelperMacros.h>

#include <vector>

#include "ASTMatcher.h"

class TestASTMatcher: public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE(TestASTMatcher);
	
	CPPUNIT_TEST(testMatchTree);
	CPPUNIT_TEST(testMatchSubTree);
	
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();
	
	void testMatchTree();
	void testMatchSubTree();

private:
	ASTMatcher matcher;
	ASTNode* testNode;

	ASTNode* buildTree();
	ASTNode* buildTreeWithDiffValue();
	ASTNode* buildSubTree();
	ASTNode* buildSubTreeWithDiffValue();
	ASTNode* buildSubTreeWithDiffStruct();
};