#include <cppunit\config\SourcePrefix.h>

#include "TestParserPKB.h"

void TestParserPKB::setUp()
{
	PKB* pkb;

	try {
		pkb = parser.parse("..\\source\\Simple\\Integration.txt");
	} catch (ParseException pe) {
		std::cout <<pe.what() << endl;
	}

	ast = pkb->getAST();
	traverser = pkb->getASTTraverser();
	varTable = pkb->getVarTable();
	procTable = pkb->getProcTable();
	numOfStmt = pkb->getNumOfStmt();
}

void TestParserPKB::tearDown()
{}

CPPUNIT_TEST_SUITE_REGISTRATION(TestParserPKB);

void TestParserPKB::testAST()
{
	std::vector<std::string> expected = expectedAST();
	std::vector<std::string> actual = traverser->traverse(ast->getRootNode());

	CPPUNIT_ASSERT(expected == actual);
}

void TestParserPKB::testVarTable()
{
	std::vector<std::string> expected;

	std::string temp[] = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "p", "q", "r", "s", "o"};
	expected.assign(temp, temp + 19);
	
	CPPUNIT_ASSERT(expected == varTable->getAllNames());
}

void TestParserPKB::testProcTable()
{
	std::vector<std::string> expected;

	std::string temp[] = {"First", "Second", "Third", "Fourth", "Fifth", "Sixth"};
	expected.assign(temp, temp + 6);

	CPPUNIT_ASSERT(expected == procTable->getAllNames());
}

void TestParserPKB::testStmtNum()
{
	CPPUNIT_ASSERT_EQUAL(35, numOfStmt);
}

std::vector<std::string> TestParserPKB::expectedAST()
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
	expected.push_back("      :assign:20");
	expected.push_back("        l:variable");
	expected.push_back("        :times");
	expected.push_back("          :plus");
	expected.push_back("            m:variable");
	expected.push_back("            n:variable");
	expected.push_back("          1:constant");
	expected.push_back("  Sixth:procedure");
	expected.push_back("    :stmtLst");
	expected.push_back("      :if:21");
	expected.push_back("        p:variable");
	expected.push_back("        :stmtLst");
	expected.push_back("          :if:22");
	expected.push_back("            q:variable");
	expected.push_back("            :stmtLst");
	expected.push_back("              :assign:23");
	expected.push_back("                r:variable");
	expected.push_back("                s:variable");
	expected.push_back("            :stmtLst");
	expected.push_back("              :assign:24");
	expected.push_back("                s:variable");
	expected.push_back("                r:variable");
	expected.push_back("        :stmtLst");
	expected.push_back("          :if:25");
	expected.push_back("            q:variable");
	expected.push_back("            :stmtLst");
	expected.push_back("              :assign:26");
	expected.push_back("                r:variable");
	expected.push_back("                s:variable");
	expected.push_back("            :stmtLst");
	expected.push_back("              :assign:27");
	expected.push_back("                r:variable");
	expected.push_back("                s:variable");
	expected.push_back("      :while:28");
	expected.push_back("        o:variable");
	expected.push_back("        :stmtLst");
	expected.push_back("          :if:29");
	expected.push_back("            p:variable");
	expected.push_back("            :stmtLst");
	expected.push_back("              :if:30");
	expected.push_back("                q:variable");
	expected.push_back("                :stmtLst");
	expected.push_back("                  :assign:31");
	expected.push_back("                    r:variable");
	expected.push_back("                    s:variable");
	expected.push_back("                :stmtLst");
	expected.push_back("                  :assign:32");
	expected.push_back("                    r:variable");
	expected.push_back("                    s:variable");
	expected.push_back("            :stmtLst");
	expected.push_back("              :if:33");
	expected.push_back("                q:variable");
	expected.push_back("                :stmtLst");
	expected.push_back("                  :assign:34");
	expected.push_back("                    r:variable");
	expected.push_back("                    s:variable");
	expected.push_back("                :stmtLst");
	expected.push_back("                  :assign:35");
	expected.push_back("                    r:variable");
	expected.push_back("                    s:variable");

	return expected;
}