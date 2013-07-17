#include <cppunit\config\SourcePrefix.h>

#include "TestModifies.h"

void TestModifies::setUp()
{
	modifies = buildModifies();
}

void TestModifies::tearDown()
{}

CPPUNIT_TEST_SUITE_REGISTRATION(TestModifies);

void TestModifies::testAddModifiesStmt()
{
	CPPUNIT_ASSERT_EQUAL(true, modifies->addModifiesStmt(1, "a"));

	CPPUNIT_ASSERT_EQUAL(false, modifies->addModifiesStmt(0, "a"));
	CPPUNIT_ASSERT_EQUAL(false, modifies->addModifiesStmt(5, "a"));

	CPPUNIT_ASSERT_EQUAL(false, modifies->addModifiesStmt(1, "e"));
}

void TestModifies::testAddModifiesProc()
{
	CPPUNIT_ASSERT_EQUAL(true, modifies->addModifiesProc("Alpha", "a"));

	CPPUNIT_ASSERT_EQUAL(false, modifies->addModifiesProc("Ninja", "a"));

	CPPUNIT_ASSERT_EQUAL(false, modifies->addModifiesProc("Alpha", "e"));
}

void TestModifies::testIsModifiesStmt()
{
	generateModifies();

	CPPUNIT_ASSERT_EQUAL(true, modifies->isModifiesStmt(1, "a"));
	CPPUNIT_ASSERT_EQUAL(false, modifies->isModifiesStmt(1, "d"));

	CPPUNIT_ASSERT_EQUAL(false, modifies->isModifiesStmt(0, "a"));
	CPPUNIT_ASSERT_EQUAL(false, modifies->isModifiesStmt(5, "a"));
	CPPUNIT_ASSERT_EQUAL(false, modifies->isModifiesStmt(1, "e"));
}

void TestModifies::testIsModifiesProc()
{
	generateModifies();

	CPPUNIT_ASSERT_EQUAL(true, modifies->isModifiesProc("Alpha", "a"));
	CPPUNIT_ASSERT_EQUAL(false, modifies->isModifiesProc("Alpha", "d"));

	CPPUNIT_ASSERT_EQUAL(false, modifies->isModifiesProc("Ninja", "a"));
	CPPUNIT_ASSERT_EQUAL(false, modifies->isModifiesProc("Alpha", "e"));
}

void TestModifies::testGetModifiedVar()
{
	generateModifies();

	std::vector<std::string> expected;

	std::string temp[] = {"a", "b", "c"};
	expected.assign(temp, temp + 3);
	CPPUNIT_ASSERT(expected == modifies->getModifiedVar("Alpha"));
	CPPUNIT_ASSERT(expected == modifies->getModifiedVar(1));

	expected.clear();
	CPPUNIT_ASSERT(expected == modifies->getModifiedVar("Delta"));
	CPPUNIT_ASSERT(expected == modifies->getModifiedVar("Ninja"));
	CPPUNIT_ASSERT(expected == modifies->getModifiedVar(4));
	CPPUNIT_ASSERT(expected == modifies->getModifiedVar(0));
	CPPUNIT_ASSERT(expected == modifies->getModifiedVar(5));
}

void TestModifies::testGetModifiesStmt()
{
	generateModifies();

	std::vector<int> expected;

	int temp[] = {1, 2, 3};
	expected.assign(temp, temp + 3);
	CPPUNIT_ASSERT(expected == modifies->getModifiesStmt("a"));

	expected.clear();
	CPPUNIT_ASSERT(expected == modifies->getModifiesStmt("d"));
	CPPUNIT_ASSERT(expected == modifies->getModifiesStmt("e"));
}

void TestModifies::testGetModifiesProc()
{
	generateModifies();

	std::vector<std::string> expected;

	std::string temp[] = {"Alpha", "Bravo", "Charlie"};
	expected.assign(temp, temp + 3);
	CPPUNIT_ASSERT(expected == modifies->getModifiesProc("a"));

	expected.clear();
	CPPUNIT_ASSERT(expected == modifies->getModifiesProc("d"));
	CPPUNIT_ASSERT(expected == modifies->getModifiesProc("e"));
}

VarTable* TestModifies::buildVarTable()
{
	VarTable* varTable = new VarTable();

	varTable->addVariable("a");
	varTable->addVariable("b");
	varTable->addVariable("c");
	varTable->addVariable("d");

	return varTable;
}

ProcTable* TestModifies::buildProcTable()
{
	ProcTable* procTable = new ProcTable();

	procTable->addProcedure("Alpha");
	procTable->addProcedure("Bravo");
	procTable->addProcedure("Charlie");
	procTable->addProcedure("Delta");

	return procTable;
}

Modifies* TestModifies::buildModifies()
{
	return new Modifies(4, buildVarTable(), buildProcTable());
}

void TestModifies::generateModifies()
{
	modifies->addModifiesStmt(1, "a");
	modifies->addModifiesStmt(1, "b");
	modifies->addModifiesStmt(1, "c");

	modifies->addModifiesStmt(2, "a");
	modifies->addModifiesStmt(2, "b");

	modifies->addModifiesStmt(3, "a");

	modifies->addModifiesProc("Alpha", "a");
	modifies->addModifiesProc("Alpha", "b");
	modifies->addModifiesProc("Alpha", "c");

	modifies->addModifiesProc("Bravo", "a");
	modifies->addModifiesProc("Bravo", "b");

	modifies->addModifiesProc("Charlie", "a");
}