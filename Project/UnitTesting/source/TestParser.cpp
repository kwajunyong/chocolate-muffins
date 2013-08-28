#include <cppunit\config\SourcePrefix.h>

#include "TestParser.h"

void TestParser::setUp()
{
	PKB* pkb;

	try {
		pkb = parser.parse("..\\source\\Test.txt");
	} catch (ParseException pe) {
		std::cout <<pe.what() << endl;
	}

	ast = pkb->getAST();
	traverser = pkb->getASTTraverser();
	varTable = pkb->getVarTable();
	procTable = pkb->getProcTable();
	numOfStmt = pkb->getNumOfStmt();
}

void TestParser::tearDown()
{}

CPPUNIT_TEST_SUITE_REGISTRATION(TestParser);

void TestParser::testAST()
{
	std::vector<std::string> expected = expectedAST();
	std::vector<std::string> actual = traverser->traverse(ast->getRootNode());

	for (int i = 0; i<expected.size(); i++) {
		CPPUNIT_ASSERT_EQUAL(expected[i], actual[i]);
	}
}

void TestParser::testVarTable()
{
	std::vector<std::string> expected;

	std::string temp[] = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n"};
	expected.assign(temp, temp + 14);
	CPPUNIT_ASSERT(expected == varTable->getAllNames());
}

void TestParser::testProcTable()
{
	std::vector<std::string> expected;

	std::string temp[] = {"First", "Second", "Third", "Fourth", "Fifth"};
	expected.assign(temp, temp + 5);
	CPPUNIT_ASSERT(expected == procTable->getAllNames());
}

void TestParser::testStmtNum()
{
	CPPUNIT_ASSERT_EQUAL(19, numOfStmt);
}

std::vector<std::string> TestParser::expectedAST()
{
	std::vector<std::string> expected;

	expected.push_back("Simple:program");
	expected.push_back("  First:procedure");
	expected.push_back("    :stmtLst");
	expected.push_back("      :while:1");
	expected.push_back("        a:variable");
	expected.push_back("        :stmtLst");
	expected.push_back("          :while:2");
	expected.push_back("            b:variable");
	expected.push_back("            :stmtLst");
	expected.push_back("              :if:3");
	expected.push_back("                c:variable");
	expected.push_back("                :stmtLst");
	expected.push_back("                  :assign:4");
	expected.push_back("                    d:variable");
	expected.push_back("                    e:variable");
	expected.push_back("                :stmtLst");
	expected.push_back("                  Fourth:call:5");
	expected.push_back("                  Fifth:call:6");
	expected.push_back("  Second:procedure");
	expected.push_back("    :stmtLst");
	expected.push_back("      First:call:7");
	expected.push_back("  Third:procedure");
	expected.push_back("    :stmtLst");
	expected.push_back("      :if:8");
	expected.push_back("        f:variable");
	expected.push_back("        :stmtLst");
	expected.push_back("          :assign:9");
	expected.push_back("            g:variable");
	expected.push_back("            h:variable");
	expected.push_back("        :stmtLst");
	expected.push_back("          :assign:10");
	expected.push_back("            g:variable");
	expected.push_back("            h:variable");
	expected.push_back("      First:call:11");
	expected.push_back("  Fourth:procedure");
	expected.push_back("    :stmtLst");
	expected.push_back("      :while:12");
	expected.push_back("        i:variable");
	expected.push_back("        :stmtLst");
	expected.push_back("          :assign:13");
	expected.push_back("            j:variable");
	expected.push_back("            k:variable");
	expected.push_back("      :assign:14");
	expected.push_back("        j:variable");
	expected.push_back("        k:variable");
	expected.push_back("  Fifth:procedure");
	expected.push_back("    :stmtLst");
	expected.push_back("      :assign:15");
	expected.push_back("        l:variable");
	expected.push_back("        m:variable");
	expected.push_back("      :assign:16");
	expected.push_back("        l:variable");
	expected.push_back("        :plus");
	expected.push_back("          m:variable");
	expected.push_back("          n:variable");
	expected.push_back("      :assign:17");
	expected.push_back("        l:variable");
	expected.push_back("        :minus");
	expected.push_back("          :plus");
	expected.push_back("            m:variable");
	expected.push_back("            n:variable");
	expected.push_back("          1:constant");
	expected.push_back("      :assign:18");
	expected.push_back("        l:variable");
	expected.push_back("        :plus");
	expected.push_back("          m:variable");
	expected.push_back("          :times");
	expected.push_back("            n:variable");
	expected.push_back("            1:constant");
	expected.push_back("      :assign:19");
	expected.push_back("        l:variable");
	expected.push_back("        :times");
	expected.push_back("          :plus");
	expected.push_back("            m:variable");
	expected.push_back("            n:variable");
	expected.push_back("          1:constant");	
	
	return expected;
}