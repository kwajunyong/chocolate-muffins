#include <cppunit\config\SourcePrefix.h>

#include "TestDesignExtractor.h"

void TestDesignExtractor::setUp()
{
	PKB* pkb;

	try {
		pkb = parser.parse("Test.txt");
		extractor.extract(pkb);
	} catch (ParseException pe) {
		std::cout <<pe.what() << endl;
	}

	ast = pkb->getAST();
	varTable = pkb->getVarTable();
	procTable = pkb->getProcTable();
	follows = pkb->getFollows();
	parent = pkb->getParent();
	modifies = pkb->getModifies();
	uses = pkb->getUses();
	calls = pkb->getCalls();
	numOfStmt = pkb->getNumOfStmt();
}

void TestDesignExtractor::tearDown()
{}

CPPUNIT_TEST_SUITE_REGISTRATION(TestDesignExtractor);

void TestDesignExtractor::testStmtNodes()
{
	std::vector<std::string> expected = expectedStmt();

	std::vector<std::string> actual;
	std::vector<ASTNode*> stmtNodes = ast->getStatementNodes(ALL);

	for (int i = 0; i < stmtNodes.size(); i++) {
		actual.push_back(stmtNodes[i]->print());
	}

	CPPUNIT_ASSERT(expected == actual);

	std::vector<int> expectedStmt;
	std::vector<int> actualStmt;

	int tempAssign[] = {4, 9, 10, 13, 14, 15, 16, 17, 18, 19};
	expectedStmt.assign(tempAssign, tempAssign + 10);

	actualStmt = ast->getStatementNumbers(ASSIGN);

	CPPUNIT_ASSERT(expectedStmt == actualStmt);

	int tempWhile[] = {1, 2, 12};
	expectedStmt.assign(tempWhile, tempWhile + 3);

	actualStmt = ast->getStatementNumbers(WHILE);

	CPPUNIT_ASSERT(expectedStmt == actualStmt);

	int tempIf[] = {3, 8};
	expectedStmt.assign(tempIf, tempIf + 2);

	actualStmt = ast->getStatementNumbers(IF);

	CPPUNIT_ASSERT(expectedStmt == actualStmt);

	int tempCall[] = {5, 6, 7, 11};
	expectedStmt.assign(tempCall, tempCall + 4);

	actualStmt = ast->getStatementNumbers(CALL);

	CPPUNIT_ASSERT(expectedStmt == actualStmt);
}

void TestDesignExtractor::testFollows()
{
	Follows expected = expectedFollows();

	for (int i=1; i<=numOfStmt; i++) {
		CPPUNIT_ASSERT(expected.getFollows(i, false) == follows->getFollows(i, false));
	}
}

void TestDesignExtractor::testParent()
{
	Parent expected = expectedParent();

	for (int i=1; i<=numOfStmt; i++) {
		CPPUNIT_ASSERT(expected.getParent(i, false) == parent->getParent(i, false));
	}
}

void TestDesignExtractor::testModifies()
{
	Modifies expected = expectedModifies();

	std::vector<std::string> variables = varTable->getAllNames();

	for (int i = 0; i < variables.size(); i++) {
		CPPUNIT_ASSERT(expected.getModifiesStmt(variables[i]) == modifies->getModifiesStmt(variables[i]));
		CPPUNIT_ASSERT(expected.getModifiesProc(variables[i]) == modifies->getModifiesProc(variables[i]));
	}
}

void TestDesignExtractor::testUses()
{
	Uses expected = expectedUses();

	std::vector<std::string> variables = varTable->getAllNames();

	for (int i = 0; i < variables.size(); i++) {
		CPPUNIT_ASSERT(expected.getUsesStmt(variables[i]) == uses->getUsesStmt(variables[i]));
		CPPUNIT_ASSERT(expected.getUsesProc(variables[i]) == uses->getUsesProc(variables[i]));
	}
}

void TestDesignExtractor::testCalls()
{
	Calls expected = expectedCalls();

	std::vector<std::string> procedures = procTable->getAllNames();

	for (int i = 0; i < procedures.size(); i++) {
		CPPUNIT_ASSERT(expected.getCalls(procedures[i], false) == calls->getCalls(procedures[i], false));
	}
}

std::vector<std::string> TestDesignExtractor::expectedStmt()
{
	std::vector<std::string> expected;

	expected.push_back(":while:1");
	expected.push_back(":while:2");
	expected.push_back(":if:3");
	expected.push_back(":assign:4");
	expected.push_back("Fourth:call:5");
	expected.push_back("Fifth:call:6");
	expected.push_back("First:call:7");
	expected.push_back(":if:8");
	expected.push_back(":assign:9");
	expected.push_back(":assign:10");
	expected.push_back("First:call:11");
	expected.push_back(":while:12");
	expected.push_back(":assign:13");
	expected.push_back(":assign:14");
	expected.push_back(":assign:15");
	expected.push_back(":assign:16");
	expected.push_back(":assign:17");
	expected.push_back(":assign:18");
	expected.push_back(":assign:19");

	return expected;
}

Follows TestDesignExtractor::expectedFollows()
{
	Follows expected;

	expected.addFollows(5, 6);
	expected.addFollows(8, 11);
	expected.addFollows(12, 14);
	expected.addFollows(15, 16);
	expected.addFollows(16, 17);
	expected.addFollows(17, 18);
	expected.addFollows(18, 19);
	
	return expected;
}

Parent TestDesignExtractor::expectedParent()
{
	Parent expected;

	expected.addParent(1, 2);
	expected.addParent(2, 3);
	expected.addParent(3, 4);
	expected.addParent(3, 5);
	expected.addParent(3, 6);
	expected.addParent(8, 9);
	expected.addParent(8, 10);
	expected.addParent(12, 13);
	
	return expected;
}

Modifies TestDesignExtractor::expectedModifies()
{
	Modifies expected(numOfStmt, varTable, procTable);

	expected.addModifiesStmt(1, "d");
	expected.addModifiesStmt(2, "d");
	expected.addModifiesStmt(3, "d");
	expected.addModifiesStmt(4, "d");
	expected.addModifiesStmt(8, "g");
	expected.addModifiesStmt(9, "g");
	expected.addModifiesStmt(10, "g");
	expected.addModifiesStmt(12, "j");
	expected.addModifiesStmt(13, "j");
	expected.addModifiesStmt(14, "j");
	expected.addModifiesStmt(15, "l");
	expected.addModifiesStmt(16, "l");
	expected.addModifiesStmt(17, "l");
	expected.addModifiesStmt(18, "l");
	expected.addModifiesStmt(19, "l");

	expected.addModifiesProc("First", "d");
	expected.addModifiesProc("Third", "g");
	expected.addModifiesProc("Fourth", "j");
	expected.addModifiesProc("Fifth", "l");

	// Calls
	expected.addModifiesProc("First", "j");
	expected.addModifiesProc("First", "l");
	expected.addModifiesProc("Second", "d");
	expected.addModifiesProc("Second", "j");
	expected.addModifiesProc("Second", "l");
	expected.addModifiesProc("Third", "d");
	expected.addModifiesProc("Third", "j");
	expected.addModifiesProc("Third", "l");

	expected.addModifiesStmt(1, "j");
	expected.addModifiesStmt(2, "j");
	expected.addModifiesStmt(3, "j");
	expected.addModifiesStmt(5, "j");
	expected.addModifiesStmt(1, "l");
	expected.addModifiesStmt(2, "l");
	expected.addModifiesStmt(3, "l");
	expected.addModifiesStmt(6, "l");
	expected.addModifiesStmt(7, "d");
	expected.addModifiesStmt(7, "j");
	expected.addModifiesStmt(7, "l");
	expected.addModifiesStmt(11, "d");
	expected.addModifiesStmt(11, "j");
	expected.addModifiesStmt(11, "l");

	return expected;
}
	
Uses TestDesignExtractor::expectedUses()
{
	Uses expected(numOfStmt, varTable, procTable);

	expected.addUsesStmt(1, "a");
	expected.addUsesStmt(1, "b");
	expected.addUsesStmt(2, "b");
	expected.addUsesStmt(1, "c");
	expected.addUsesStmt(2, "c");
	expected.addUsesStmt(3, "c");
	expected.addUsesStmt(1, "e");
	expected.addUsesStmt(2, "e");
	expected.addUsesStmt(3, "e");
	expected.addUsesStmt(4, "e");
	expected.addUsesStmt(8, "f");
	expected.addUsesStmt(8, "h");
	expected.addUsesStmt(9, "h");
	expected.addUsesStmt(10, "h");
	expected.addUsesStmt(12, "i");
	expected.addUsesStmt(12, "k");
	expected.addUsesStmt(13, "k");
	expected.addUsesStmt(14, "k");	
	expected.addUsesStmt(15, "m");
	expected.addUsesStmt(16, "m");
	expected.addUsesStmt(16, "n");
	expected.addUsesStmt(17, "m");
	expected.addUsesStmt(17, "n");
	expected.addUsesStmt(18, "m");
	expected.addUsesStmt(18, "n");
	expected.addUsesStmt(19, "m");
	expected.addUsesStmt(19, "n");

	expected.addUsesProc("First", "a");
	expected.addUsesProc("First", "b");
	expected.addUsesProc("First", "c");
	expected.addUsesProc("First", "e");
	expected.addUsesProc("Third", "f");
	expected.addUsesProc("Third", "h");
	expected.addUsesProc("Fourth", "i");
	expected.addUsesProc("Fourth", "k");
	expected.addUsesProc("Fifth", "m");
	expected.addUsesProc("Fifth", "n");
	
	// Calls
	expected.addUsesProc("First", "i");
	expected.addUsesProc("First", "k");
	expected.addUsesProc("First", "m");
	expected.addUsesProc("First", "n");
	expected.addUsesProc("Second", "a");
	expected.addUsesProc("Second", "b");
	expected.addUsesProc("Second", "c");
	expected.addUsesProc("Second", "e");
	expected.addUsesProc("Second", "i");
	expected.addUsesProc("Second", "k");
	expected.addUsesProc("Second", "m");
	expected.addUsesProc("Second", "n");
	expected.addUsesProc("Third", "a");
	expected.addUsesProc("Third", "b");
	expected.addUsesProc("Third", "c");
	expected.addUsesProc("Third", "e");
	expected.addUsesProc("Third", "i");
	expected.addUsesProc("Third", "k");
	expected.addUsesProc("Third", "m");
	expected.addUsesProc("Third", "n");

	expected.addUsesStmt(1, "i");
	expected.addUsesStmt(2, "i");
	expected.addUsesStmt(3, "i");
	expected.addUsesStmt(5, "i");
	expected.addUsesStmt(1, "k");
	expected.addUsesStmt(2, "k");
	expected.addUsesStmt(3, "k");
	expected.addUsesStmt(5, "k");
	expected.addUsesStmt(1, "m");
	expected.addUsesStmt(2, "m");
	expected.addUsesStmt(3, "m");
	expected.addUsesStmt(6, "m");
	expected.addUsesStmt(1, "n");
	expected.addUsesStmt(2, "n");
	expected.addUsesStmt(3, "n");
	expected.addUsesStmt(6, "n");
	expected.addUsesStmt(7, "a");
	expected.addUsesStmt(7, "b");
	expected.addUsesStmt(7, "c");
	expected.addUsesStmt(7, "e");
	expected.addUsesStmt(7, "i");
	expected.addUsesStmt(7, "k");
	expected.addUsesStmt(7, "m");
	expected.addUsesStmt(7, "n");
	expected.addUsesStmt(11, "a");
	expected.addUsesStmt(11, "b");
	expected.addUsesStmt(11, "c");
	expected.addUsesStmt(11, "e");
	expected.addUsesStmt(11, "i");
	expected.addUsesStmt(11, "k");
	expected.addUsesStmt(11, "m");
	expected.addUsesStmt(11, "n");

	return expected;
}

Calls TestDesignExtractor::expectedCalls()
{
	Calls expected;

	expected.addCalls("First", "Fourth");
	expected.addCalls("First", "Fifth");
	expected.addCalls("Second", "First");
	expected.addCalls("Third", "First");

	return expected;
}