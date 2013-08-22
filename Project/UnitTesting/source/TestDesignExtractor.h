#pragma once

#include <cppunit\extensions\HelperMacros.h>

#include <vector>

#include "Parser.h"
#include "DesignExtractor.h"

class TestDesignExtractor : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE(TestDesignExtractor);

	CPPUNIT_TEST(testStmtNodes);
	CPPUNIT_TEST(testFollows);
	CPPUNIT_TEST(testParent);
	CPPUNIT_TEST(testModifies);
	CPPUNIT_TEST(testUses);
	CPPUNIT_TEST(testCalls);

	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	void testStmtNodes();
	void testFollows();
	void testParent();
	void testModifies();
	void testUses();
	void testCalls();
	void testStmtNum();

private:
	Parser parser;
	DesignExtractor extractor;

	AST* ast;
	VarTable* varTable;
	ProcTable* procTable;
	Follows* follows;
	Parent* parent;
	Modifies* modifies;
	Uses* uses;
	Calls* calls;
	int numOfStmt;

	std::vector<std::string> expectedStmt();
	Follows expectedFollows();
	Parent expectedParent();
	Modifies expectedModifies();
	Uses expectedUses();
	Calls expectedCalls();
};