#pragma once

#include <cppunit\extensions\HelperMacros.h>

#include <algorithm>

#include "Parser.h"
#include "DesignExtractor.h"

class TestDesignExtractorPKB : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE(TestDesignExtractorPKB);

	CPPUNIT_TEST(testStmtNodes);
	CPPUNIT_TEST(testFollows);
	CPPUNIT_TEST(testParent);
	CPPUNIT_TEST(testModifies);
	CPPUNIT_TEST(testUses);
	CPPUNIT_TEST(testCalls);
	CPPUNIT_TEST(testNext);

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
	void testNext();

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
	Next* next;
	int numOfStmt;

	std::vector<std::string> expectedStmtNodes();
	std::map<std::string, std::vector<int>> expectedWhileMap();
	std::map<std::string, std::vector<int>> expectedIfMap();
	Follows expectedFollows();
	Parent expectedParent();
	Modifies expectedModifies();
	Uses expectedUses();
	Calls expectedCalls();
	Next expectedNext();
};