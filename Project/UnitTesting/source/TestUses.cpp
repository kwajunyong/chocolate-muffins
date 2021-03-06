#include <cppunit\config\SourcePrefix.h>

#include "TestUses.h"

void TestUses::setUp()
{
	uses = buildUses();
}

void TestUses::tearDown()
{}

CPPUNIT_TEST_SUITE_REGISTRATION(TestUses);

void TestUses::testAddUsesStmt()
{
	CPPUNIT_ASSERT_EQUAL(true, uses->addUsesStmt(1, "a"));
	CPPUNIT_ASSERT_EQUAL(false, uses->addUsesStmt(1, "a"));

	CPPUNIT_ASSERT_EQUAL(false, uses->addUsesStmt(0, "a"));
	CPPUNIT_ASSERT_EQUAL(false, uses->addUsesStmt(5, "a"));
}

void TestUses::testAddUsesProc()
{
	CPPUNIT_ASSERT_EQUAL(true, uses->addUsesProc("Alpha", "a"));
	CPPUNIT_ASSERT_EQUAL(false, uses->addUsesProc("Alpha", "a"));
}

void TestUses::testIsUsesStmt()
{
	generateUses();

	CPPUNIT_ASSERT_EQUAL(true, uses->isUsesStmt(1, "a"));
	CPPUNIT_ASSERT_EQUAL(false, uses->isUsesStmt(1, "d"));

	CPPUNIT_ASSERT_EQUAL(false, uses->isUsesStmt(0, "a"));
	CPPUNIT_ASSERT_EQUAL(false, uses->isUsesStmt(5, "a"));
	CPPUNIT_ASSERT_EQUAL(false, uses->isUsesStmt(1, "e"));
}

void TestUses::testIsUsesProc()
{
	generateUses();

	CPPUNIT_ASSERT_EQUAL(true, uses->isUsesProc("Alpha", "a"));
	CPPUNIT_ASSERT_EQUAL(false, uses->isUsesProc("Alpha", "d"));

	CPPUNIT_ASSERT_EQUAL(false, uses->isUsesProc("Delta", "a"));
	CPPUNIT_ASSERT_EQUAL(false, uses->isUsesProc("Alpha", "e"));
}

void TestUses::testGetUsedVar()
{
	generateUses();

	std::vector<std::string> expected;
	std::vector<std::string> actual;

	std::string temp[] = {"a", "b", "c"};
	
	expected.assign(temp, temp + 2);
	actual = uses->getUsedVar("Alpha");
	std::sort(actual.begin(), actual.end());
	CPPUNIT_ASSERT(expected == actual);
	
	expected.assign(temp, temp + 3);
	actual = uses->getUsedVar(1);
	std::sort(actual.begin(), actual.end());
	CPPUNIT_ASSERT(expected == actual);

	expected.clear();
	CPPUNIT_ASSERT(expected == uses->getUsedVar("Charlie"));
	CPPUNIT_ASSERT(expected == uses->getUsedVar("Delta"));
	CPPUNIT_ASSERT(expected == uses->getUsedVar(4));
	CPPUNIT_ASSERT(expected == uses->getUsedVar(0));
	CPPUNIT_ASSERT(expected == uses->getUsedVar(5));
}

void TestUses::testGetUsesStmt()
{
	generateUses();

	std::vector<int> expected;
	std::vector<int> actual;
	
	int temp[] = {1, 2, 3};
	expected.assign(temp, temp + 3);
	actual = uses->getUsesStmt("a");
	std::sort(actual.begin(), actual.end());
	CPPUNIT_ASSERT(expected == actual);

	expected.clear();
	CPPUNIT_ASSERT(expected == uses->getUsesStmt("d"));
	CPPUNIT_ASSERT(expected == uses->getUsesStmt("e"));
}

void TestUses::testGetUsesProc()
{
	generateUses();

	std::vector<std::string> expected;
	std::vector<std::string> actual;

	std::string temp[] = {"Alpha", "Bravo"};
	expected.assign(temp, temp + 2);
	actual = uses->getUsesProc("a");
	std::sort(actual.begin(), actual.end());
	CPPUNIT_ASSERT(expected == actual);

	expected.clear();
	CPPUNIT_ASSERT(expected == uses->getUsesProc("d"));
	CPPUNIT_ASSERT(expected == uses->getUsesProc("e"));
}

Uses* TestUses::buildUses()
{
	return new Uses(4);
}

void TestUses::generateUses()
{
	uses->addUsesStmt(1, "a");
	uses->addUsesStmt(1, "b");
	uses->addUsesStmt(1, "c");

	uses->addUsesStmt(2, "a");
	uses->addUsesStmt(2, "b");

	uses->addUsesStmt(3, "a");

	uses->addUsesProc("Alpha", "a");
	uses->addUsesProc("Alpha", "b");

	uses->addUsesProc("Bravo", "a");
}