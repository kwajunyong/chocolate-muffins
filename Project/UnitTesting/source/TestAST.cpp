#include <cppunit\config\SourcePrefix.h>

#include "TestAST.h"
#include "AST.h"

void TestAST::setUp()
{
	ast = new AST();

	ASTNode* rootNode = buildTree();

	ast->setRootNode(rootNode);
}

void TestAST::tearDown()
{}

CPPUNIT_TEST_SUITE_REGISTRATION(TestAST);

void TestAST::testGetStatementNode()
{
	ASTNode* node = ast->getStatementNode(1);
	CPPUNIT_ASSERT(":assign:1" == node->print());

	node = ast->getStatementNode(2);
	CPPUNIT_ASSERT(node == NULL);
}

void TestAST::testGetStatementType()
{
	ASTType type = ast->getStatementType(1);
	CPPUNIT_ASSERT_EQUAL(ASSIGN, type);

	type = ast->getStatementType(2);
	CPPUNIT_ASSERT_EQUAL(NONE, type);
}

void TestAST::testGetStatementNodes()
{
	std::vector<std::string> expect;
	expect.push_back(":assign:1");

	std::vector<std::string> actual;
	std::vector<ASTNode*> nodes = ast->getStatementNodes(ASSIGN);
	
	for (int i=0; i<nodes.size(); i++) {
		actual.push_back(nodes[i]->print());
	}

	CPPUNIT_ASSERT(expect == actual);

	expect.empty();

	actual.empty();
	nodes = ast->getStatementNodes(WHILE);
	
	for (int i=0; i<nodes.size(); i++) {
		actual.push_back(nodes[i]->print());
	}

	CPPUNIT_ASSERT(expect == actual);
}

void TestAST::testGetStatementNumbers()
{
	std::vector<int> expect;
	expect.push_back(1);

	std::vector<int> actual = ast->getStatementNumbers(ASSIGN);

	CPPUNIT_ASSERT(expect == actual);

	expect.clear();

	actual = ast->getStatementNumbers(WHILE);
	
	CPPUNIT_ASSERT(expect == actual);
}

ASTNode* TestAST::buildTree()
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

	ast->addStatementNodeToList(assignNode);

	return assignNode;
}