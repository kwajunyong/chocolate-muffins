#include <cppunit\config\SourcePrefix.h>

#include "TestASTTraverser.h"

void TestASTTraverser::setUp()
{}

void TestASTTraverser::tearDown()
{}

CPPUNIT_TEST_SUITE_REGISTRATION(TestASTTraverser);

void TestASTTraverser::testTraverse()
{
	std::vector<std::string> expect;
	expect.push_back(":assign:1");
	expect.push_back("  a:variable");
	expect.push_back("  :minus");
	expect.push_back("    :plus");
	expect.push_back("      b:variable");
	expect.push_back("      c:variable");
	expect.push_back("    1:constant");
	
	ASTNode* actualNode = buildTree();

	CPPUNIT_ASSERT(expect == traverser.traverse(actualNode));
}

ASTNode* TestASTTraverser::buildTree()
{
	ASTNode* assignNode = new ASTNode("", ASSIGN, 1);
	ASTNode* plusNode = new ASTNode("", PLUS, 0);
	ASTNode* minusNode = new ASTNode("", MINUS, 0);
	ASTNode* varNodeA = new ASTNode("a", VARIABLE, 0);
	ASTNode* varNodeB = new ASTNode("b", VARIABLE, 0);
	ASTNode* varNodeC = new ASTNode("c", VARIABLE, 0);
	ASTNode* constantNode = new ASTNode("1", CONSTANT, 0);

	assignNode->joinChild(varNodeA);
	varNodeA->joinNext(minusNode);
	minusNode->joinChild(plusNode);
	plusNode->joinChild(varNodeB);
	varNodeB->joinNext(varNodeC);
	plusNode->joinNext(constantNode);

	return assignNode;
}