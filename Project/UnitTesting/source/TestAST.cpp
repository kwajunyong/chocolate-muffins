#include <cppunit\config\SourcePrefix.h>

#include "TestAST.h"
#include "AST.h"

void TestAST::setUp()
{
	ast = new AST();

	generateAST();
}

void TestAST::tearDown()
{}

CPPUNIT_TEST_SUITE_REGISTRATION(TestAST);

void TestAST::testGetStatementNode()
{
	ASTNode* node = ast->getStatementNode(1);
	CPPUNIT_ASSERT(":assign:1" == node->print());

	node = ast->getStatementNode(2);
	CPPUNIT_ASSERT(":call:2" == node->print());

	node = ast->getStatementNode(3);
	CPPUNIT_ASSERT(":while:3" == node->print());

	node = ast->getStatementNode(4);
	CPPUNIT_ASSERT(":if:4" == node->print());

	node = ast->getStatementNode(9);
	CPPUNIT_ASSERT(node == NULL);
}

void TestAST::testGetStatementType()
{
	ASTType type = ast->getStatementType(1);
	CPPUNIT_ASSERT_EQUAL(ASSIGN, type);

	type = ast->getStatementType(2);
	CPPUNIT_ASSERT_EQUAL(CALL, type);

	type = ast->getStatementType(3);
	CPPUNIT_ASSERT_EQUAL(WHILE, type);

	type = ast->getStatementType(4);
	CPPUNIT_ASSERT_EQUAL(IF, type);

	type = ast->getStatementType(9);
	CPPUNIT_ASSERT_EQUAL(NONE, type);
}

void TestAST::testGetStatementNodes()
{
	std::vector<std::string> expected;
	std::vector<std::string> actual;

	expected.clear();
	expected.push_back(":assign:1");
	expected.push_back(":assign:8");

	actual.clear();
	std::vector<ASTNode*> nodes = ast->getStatementNodes(ASSIGN);
	
	for (int i=0; i<nodes.size(); i++) {
		actual.push_back(nodes[i]->print());
	}

	CPPUNIT_ASSERT(expected == actual);

	expected.empty();
	expected.push_back(":call:2");
	expected.push_back(":call:7");

	actual.empty();
	nodes = ast->getStatementNodes(CALL);
	
	for (int i=0; i<nodes.size(); i++) {
		actual.push_back(nodes[i]->print());
	}

	CPPUNIT_ASSERT(expected == actual);

	expected.empty();
	expected.push_back(":while:3");
	expected.push_back(":while:6");

	actual.empty();
	nodes = ast->getStatementNodes(WHILE);
	
	for (int i=0; i<nodes.size(); i++) {
		actual.push_back(nodes[i]->print());
	}

	CPPUNIT_ASSERT(expected == actual);

	expected.empty();
	expected.push_back(":if:4");
	expected.push_back(":if:5");

	actual.empty();
	nodes = ast->getStatementNodes(IF);
	
	for (int i=0; i<nodes.size(); i++) {
		actual.push_back(nodes[i]->print());
	}

	CPPUNIT_ASSERT(expected == actual);

	expected.empty();
	expected.push_back(":assign:1");
	expected.push_back(":call:2");
	expected.push_back(":while:3");
	expected.push_back(":if:4");
	expected.push_back(":if:5");
	expected.push_back(":while:6");
	expected.push_back(":call:7");
	expected.push_back(":assign:8");
	
	actual.empty();
	nodes = ast->getStatementNodes(ALL);
	
	for (int i=0; i<nodes.size(); i++) {
		actual.push_back(nodes[i]->print());
	}

	CPPUNIT_ASSERT(expected == actual);

	expected.empty();
	
	actual.empty();
	nodes = ast->getStatementNodes(NONE);
	
	for (int i=0; i<nodes.size(); i++) {
		actual.push_back(nodes[i]->print());
	}

	CPPUNIT_ASSERT(expected == actual);
}

void TestAST::testGetStatementNumbers()
{
	std::vector<int> expected;
	std::vector<int> actual;

	expected.clear();
	expected.push_back(1);
	expected.push_back(8);
	actual = ast->getStatementNumbers(ASSIGN);
	CPPUNIT_ASSERT(expected == actual);

	expected.clear();
	expected.push_back(2);
	expected.push_back(7);
	actual = ast->getStatementNumbers(CALL);
	CPPUNIT_ASSERT(expected == actual);

	expected.clear();
	expected.push_back(3);
	expected.push_back(6);
	actual = ast->getStatementNumbers(WHILE);
	CPPUNIT_ASSERT(expected == actual);

	expected.clear();
	expected.push_back(4);
	expected.push_back(5);
	actual = ast->getStatementNumbers(IF);
	CPPUNIT_ASSERT(expected == actual);

	expected.clear();
	int temp[] = {1, 2, 3, 4, 5, 6, 7, 8};
	expected.assign(temp, temp + 8);
	actual = ast->getStatementNumbers(ALL);
	CPPUNIT_ASSERT(expected == actual);

	expected.clear();
	actual = ast->getStatementNumbers(NONE);
	CPPUNIT_ASSERT(expected == actual);
}

void TestAST::testGetContainerStatementNumbers()
{
	std::vector<int> expected;
	std::vector<int> actual;

	expected.clear();
	expected.push_back(3);
	expected.push_back(6);
	actual = ast->getStatementNumbers(WHILE, "a");
	CPPUNIT_ASSERT(expected == actual);

	expected.clear();
	actual = ast->getStatementNumbers(WHILE, "b");
	CPPUNIT_ASSERT(expected == actual);

	expected.clear();
	expected.push_back(4);
	expected.push_back(5);
	actual = ast->getStatementNumbers(IF, "b");
	CPPUNIT_ASSERT(expected == actual);

	expected.clear();
	actual = ast->getStatementNumbers(IF, "a");
	CPPUNIT_ASSERT(expected == actual);

	expected.clear();
	actual = ast->getStatementNumbers(ASSIGN, "a");
	CPPUNIT_ASSERT(expected == actual);
}

void TestAST::generateAST()
{
	ASTNode* node;

	ast->storeStatementNode(new ASTNode("", ASSIGN, 1));
	
	ast->storeStatementNode(new ASTNode("", CALL, 2));

	node = new ASTNode("", WHILE, 3);
	node->joinChild(new ASTNode("a", VARIABLE, 0));
	ast->storeStatementNode(node);
	
	node = new ASTNode("", IF, 4);
	node->joinChild(new ASTNode("b", VARIABLE, 0));
	ast->storeStatementNode(node);

	node = new ASTNode("", IF, 5);
	node->joinChild(new ASTNode("b", VARIABLE, 0));
	ast->storeStatementNode(node);

	node = new ASTNode("", WHILE, 6);
	node->joinChild(new ASTNode("a", VARIABLE, 0));
	ast->storeStatementNode(node);

	ast->storeStatementNode(new ASTNode("", CALL, 7));

	ast->storeStatementNode(new ASTNode("", ASSIGN, 8));
}