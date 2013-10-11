#pragma once

#include <cppunit\extensions\HelperMacros.h>

#include <vector>

#include "AST.h"

class TestAST: public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE(TestAST);

	CPPUNIT_TEST(testGetStatementNode);
	CPPUNIT_TEST(testGetStatementType);

	CPPUNIT_TEST(testGetCalledProcedure);
	
	CPPUNIT_TEST(testGetStatementNodes);
	CPPUNIT_TEST(testGetStatementNumbers);
	CPPUNIT_TEST(testGetContainerStatementNumbers);
	
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();
	
	void testGetStatementNode();
	void testGetStatementType();
	
	void testGetCalledProcedure();

	void testGetStatementNodes();
	void testGetStatementNumbers();
	void testGetContainerStatementNumbers();

private:
	AST* ast;

	void generateAST();
};