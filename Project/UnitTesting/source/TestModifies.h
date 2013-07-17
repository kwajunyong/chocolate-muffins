#pragma once

#include <cppunit\extensions\HelperMacros.h>

#include <vector>

#include "Modifies.h"

class TestModifies : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE(TestModifies);

	CPPUNIT_TEST(testAddModifiesStmt);
	CPPUNIT_TEST(testAddModifiesProc);

	CPPUNIT_TEST(testIsModifiesStmt);
	CPPUNIT_TEST(testIsModifiesProc);

	CPPUNIT_TEST(testGetModifiedVar);

	CPPUNIT_TEST(testGetModifiesStmt);
	CPPUNIT_TEST(testGetModifiesProc);

	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	void testAddModifiesStmt();
	void testAddModifiesProc();

	void testIsModifiesStmt();
	void testIsModifiesProc();

	void testGetModifiedVar();

	void testGetModifiesStmt();
	void testGetModifiesProc();

private:
	Modifies* modifies;

	VarTable* buildVarTable();
	ProcTable* buildProcTable();
	Modifies* buildModifies();

	void generateModifies();
};