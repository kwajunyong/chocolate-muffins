#include <cppunit\config\SourcePrefix.h>

#include "TestDesignExtractorPKB.h"

void TestDesignExtractorPKB::setUp()
{
	PKB* pkb;

	try {
		pkb = parser.parse("..\\source\\Simple\\Integration.txt");
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
	next = pkb->getNext();
	numOfStmt = pkb->getNumOfStmt();
}

void TestDesignExtractorPKB::tearDown()
{}

CPPUNIT_TEST_SUITE_REGISTRATION(TestDesignExtractorPKB);

void TestDesignExtractorPKB::testStmtNodes()
{
	std::vector<std::string> expectedNodes = expectedStmt();

	std::vector<ASTNode*> tempNodes = ast->getStatementNodes(ALL);

	std::vector<std::string> actualNodes;

	for (size_t i = 0; i < tempNodes.size(); i++) {
		actualNodes.push_back(tempNodes[i]->print());
	}

	CPPUNIT_ASSERT(expectedNodes == actualNodes);
	
	std::vector<int> expectedAll;
	
	for (size_t i = 1; i <= 35; i++) {
		expectedAll.push_back(i);
	}

	std::vector<int> actualAll = ast->getStatementNumbers(ALL);

	CPPUNIT_ASSERT(expectedAll == actualAll);

	int tempAssign[] = {4, 9, 10, 13, 14, 15, 16, 17, 18, 19, 20, 23, 24, 26, 27, 31, 32, 34, 35};
	std::vector<int> expectedAssign(tempAssign, tempAssign + 19);

	std::vector<int> actualAssign = ast->getStatementNumbers(ASSIGN);

	CPPUNIT_ASSERT(expectedAssign == actualAssign);

	int tempWhile[] = {1, 2, 12, 28};
	std::vector<int> expectedWhile(tempWhile, tempWhile + 4);

	std::vector<int> actualWhile = ast->getStatementNumbers(WHILE);

    CPPUNIT_ASSERT(expectedWhile == actualWhile);

	int tempIf[] = {3, 8, 21, 22, 25, 29, 30, 33};
	std::vector<int> expectedIf(tempIf, tempIf + 8);

	std::vector<int> actualIf = ast->getStatementNumbers(IF);

	CPPUNIT_ASSERT(expectedIf == actualIf);

	int tempCall[] = {5, 6, 7, 11};
	std::vector<int> expectedCall(tempCall, tempCall + 4);

	std::vector<int> actualCall = ast->getStatementNumbers(CALL);

	CPPUNIT_ASSERT(expectedCall == actualCall);
}

void TestDesignExtractorPKB::testFollows()
{
	Follows expected = expectedFollows();

	for (int i = 1; i <= numOfStmt; i++) {
		CPPUNIT_ASSERT(expected.getFollows(i, false) == follows->getFollows(i, false));
	}
}

void TestDesignExtractorPKB::testParent()
{
	Parent expected = expectedParent();

	for (int i = 1; i <= numOfStmt; i++) {
		CPPUNIT_ASSERT(expected.getParent(i, false) == parent->getParent(i, false));
	}
}

void TestDesignExtractorPKB::testModifies()
{
	Modifies expected = expectedModifies();

	std::vector<std::string> variables = varTable->getAllNames();

	for (size_t i = 0; i < variables.size(); i++) {
		CPPUNIT_ASSERT(expected.getModifiesStmt(variables[i]) == modifies->getModifiesStmt(variables[i]));
		CPPUNIT_ASSERT(expected.getModifiesProc(variables[i]) == modifies->getModifiesProc(variables[i]));
	}
}

void TestDesignExtractorPKB::testUses()
{
	Uses expected = expectedUses();

	std::vector<std::string> variables = varTable->getAllNames();

	for (size_t i = 0; i < variables.size(); i++) {
		CPPUNIT_ASSERT(expected.getUsesStmt(variables[i]) == uses->getUsesStmt(variables[i]));
		CPPUNIT_ASSERT(expected.getUsesProc(variables[i]) == uses->getUsesProc(variables[i]));
	}
}

void TestDesignExtractorPKB::testCalls()
{
	Calls expected = expectedCalls();

	std::vector<std::string> procedures = procTable->getAllNames();

	for (size_t i = 0; i < procedures.size(); i++) {
		CPPUNIT_ASSERT(expected.getCalls(procedures[i], false) == calls->getCalls(procedures[i], false));
	}
}

void TestDesignExtractorPKB::testNext()
{
	Next expected = expectedNext();

	for (int i = 1; i <= numOfStmt; i++) {
		CPPUNIT_ASSERT_MESSAGE(std::to_string(long double(i)), expected.getNext(i, false) == next->getNext(i, false));
	}
}

std::vector<std::string> TestDesignExtractorPKB::expectedStmt()
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
	expected.push_back(":assign:20");
	expected.push_back(":if:21");
	expected.push_back(":if:22");
	expected.push_back(":assign:23");
	expected.push_back(":assign:24");
	expected.push_back(":if:25");
	expected.push_back(":assign:26");
	expected.push_back(":assign:27");
	expected.push_back(":while:28");
	expected.push_back(":if:29");
	expected.push_back(":if:30");
	expected.push_back(":assign:31");
	expected.push_back(":assign:32");
	expected.push_back(":if:33");
	expected.push_back(":assign:34");
	expected.push_back(":assign:35");

	return expected;
}

Follows TestDesignExtractorPKB::expectedFollows()
{
	Follows expected;

	expected.addFollows(5, 6);
	expected.addFollows(8, 11);
	expected.addFollows(12, 14);
	expected.addFollows(15, 16);
	expected.addFollows(16, 17);
	expected.addFollows(17, 18);
	expected.addFollows(18, 19);
	expected.addFollows(19, 20);
	expected.addFollows(21, 28);

	return expected;
}

Parent TestDesignExtractorPKB::expectedParent()
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
	expected.addParent(21, 22);
	expected.addParent(22, 23);
	expected.addParent(22, 24);
	expected.addParent(21, 25);
	expected.addParent(25, 26);
	expected.addParent(25, 27);
	expected.addParent(28, 29);
	expected.addParent(29, 30);
	expected.addParent(30, 31);
	expected.addParent(30, 32);
	expected.addParent(29, 33);
	expected.addParent(33, 34);
	expected.addParent(33, 35);

	return expected;
}

Modifies TestDesignExtractorPKB::expectedModifies()
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
	expected.addModifiesStmt(20, "l");
	expected.addModifiesStmt(21, "r");
	expected.addModifiesStmt(22, "r");
	expected.addModifiesStmt(23, "r");
	expected.addModifiesStmt(21, "s");
	expected.addModifiesStmt(22, "s");
	expected.addModifiesStmt(24, "s");
	expected.addModifiesStmt(25, "r");
	expected.addModifiesStmt(26, "r");
	expected.addModifiesStmt(27, "r");
	expected.addModifiesStmt(28, "r");
	expected.addModifiesStmt(29, "r");
	expected.addModifiesStmt(30, "r");
	expected.addModifiesStmt(31, "r");
	expected.addModifiesStmt(32, "r");
	expected.addModifiesStmt(33, "r");
	expected.addModifiesStmt(34, "r");
	expected.addModifiesStmt(35, "r");

	expected.addModifiesProc("First", "d");
	expected.addModifiesProc("Third", "g");
	expected.addModifiesProc("Fourth", "j");
	expected.addModifiesProc("Fifth", "l");
	expected.addModifiesProc("Sixth", "r");
	expected.addModifiesProc("Sixth", "s");

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
	
Uses TestDesignExtractorPKB::expectedUses()
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
	expected.addUsesStmt(20, "m");
	expected.addUsesStmt(20, "n");
	expected.addUsesStmt(21, "p");
	expected.addUsesStmt(21, "q");
	expected.addUsesStmt(22, "q");
	expected.addUsesStmt(21, "s");
	expected.addUsesStmt(22, "s");
	expected.addUsesStmt(23, "s");
	expected.addUsesStmt(21, "r");
	expected.addUsesStmt(22, "r");
	expected.addUsesStmt(24, "r");
	expected.addUsesStmt(25, "q");
	expected.addUsesStmt(25, "s");
	expected.addUsesStmt(26, "s");
	expected.addUsesStmt(27, "s");
	expected.addUsesStmt(28, "o");
	expected.addUsesStmt(28, "p");
	expected.addUsesStmt(29, "p");
	expected.addUsesStmt(28, "q");
	expected.addUsesStmt(29, "q");
	expected.addUsesStmt(30, "q");
	expected.addUsesStmt(28, "s");
	expected.addUsesStmt(29, "s");
	expected.addUsesStmt(30, "s");
	expected.addUsesStmt(31, "s");
	expected.addUsesStmt(32, "s");
	expected.addUsesStmt(33, "q");
	expected.addUsesStmt(33, "s");
	expected.addUsesStmt(34, "s");
	expected.addUsesStmt(35, "s");

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
	expected.addUsesProc("Sixth", "o");
	expected.addUsesProc("Sixth", "p");
	expected.addUsesProc("Sixth", "q");
	expected.addUsesProc("Sixth", "r");
	expected.addUsesProc("Sixth", "s");
	
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

Calls TestDesignExtractorPKB::expectedCalls()
{
	Calls expected;

	expected.addCalls("First", "Fourth");
	expected.addCalls("First", "Fifth");
	expected.addCalls("Second", "First");
	expected.addCalls("Third", "First");

	return expected;
}

Next TestDesignExtractorPKB::expectedNext()
{
	Next expected;

	expected.addNext(1, 2);
	expected.addNext(2, 1);
	expected.addNext(2, 3);
	expected.addNext(3, 4);
	expected.addNext(3, 5);
	expected.addNext(4, 2);
	expected.addNext(5, 6);
	expected.addNext(6, 2);
	expected.addNext(8, 9);
	expected.addNext(8, 10);
	expected.addNext(9, 11);
	expected.addNext(10, 11);
	expected.addNext(12, 14);
	expected.addNext(12, 13);
	expected.addNext(13, 12);
	expected.addNext(15, 16);
	expected.addNext(16, 17);
	expected.addNext(17, 18);
	expected.addNext(18, 19);
	expected.addNext(19, 20);
	expected.addNext(21, 22);
	expected.addNext(21, 25);
	expected.addNext(22, 23);
	expected.addNext(22, 24);
	expected.addNext(23, 28);
	expected.addNext(24, 28);
	expected.addNext(25, 26);
	expected.addNext(25, 27);
	expected.addNext(26, 28);
	expected.addNext(27, 28);
	expected.addNext(28, 29);
	expected.addNext(29, 30);
	expected.addNext(29, 33);
	expected.addNext(30, 31);
	expected.addNext(30, 32);
	expected.addNext(31, 28);
	expected.addNext(32, 28);
	expected.addNext(33, 34);
	expected.addNext(33, 35);
	expected.addNext(34, 28);
	expected.addNext(35, 28);

	return expected;
}