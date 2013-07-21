#pragma once

#include <cppunit\extensions\HelperMacros.h>

#include <vector>

#include "Parser.h"
#include "DesignExtractor.h"

class TestDesignExtractor : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE(TestDesignExtractor);

	CPPUNIT_TEST(testFollows);
	CPPUNIT_TEST(testParent);
	CPPUNIT_TEST(testModifies);
	CPPUNIT_TEST(testUses);

	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	void testAST();
	void testVarTable();
	void testProcTable();
	void testFollows();
	void testParent();
	void testModifies();
	void testUses();
	void testStmtNum();

private:
	Parser parser;
	DesignExtractor extractor;

	VarTable* varTable;
	ProcTable* procTable;
	Follows* follows;
	Parent* parent;
	Modifies* modifies;
	Uses* uses;
	int numOfStmt;

	Follows expectedFollows();
	Parent expectedParent();
	Modifies expectedModifies();
	Uses expectedUses();
};