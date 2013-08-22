#pragma once

#include <cppunit\extensions\HelperMacros.h>

#include <vector>

#include "ASTTraverser.h"

class TestASTTraverser: public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE(TestASTTraverser);
	
	CPPUNIT_TEST(testTraverse);

	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();
	
	void testTraverse();

private:
	ASTTraverser traverser;

	ASTNode* buildTree();
};