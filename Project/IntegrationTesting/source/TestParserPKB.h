#pragma once

#include <cppunit\extensions\HelperMacros.h>

#include "Parser.h"

class TestParserPKB : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE(TestParserPKB);

	CPPUNIT_TEST(testAST);
	CPPUNIT_TEST(testVarTable);
	CPPUNIT_TEST(testProcTable);
	CPPUNIT_TEST(testConstTable);
	CPPUNIT_TEST(testStmtNum);

	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	void testAST();
	void testVarTable();
	void testProcTable();
	void testConstTable();
	void testStmtNum();

private:
	Parser parser;

	AST* ast;
	ASTTraverser* traverser;
	VarTable* varTable;
	ProcTable* procTable;
	ConstTable* constTable;
	int numOfStmt;

	std::vector<std::string> expectedAST();
};