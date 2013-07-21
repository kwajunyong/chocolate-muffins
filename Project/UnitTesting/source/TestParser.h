#pragma once

#include <cppunit\extensions\HelperMacros.h>

#include <vector>

#include "Parser.h"

class TestParser : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE(TestParser);

	CPPUNIT_TEST(testAST);
	CPPUNIT_TEST(testVarTable);
	CPPUNIT_TEST(testProcTable);
	CPPUNIT_TEST(testStmtNum);

	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	void testAST();
	void testVarTable();
	void testProcTable();
	void testStmtNum();

private:
	Parser parser;

	AST* ast;
	VarTable* varTable;
	ProcTable* procTable;
	int numOfStmt;

	std::vector<std::string> expectedAST();
};