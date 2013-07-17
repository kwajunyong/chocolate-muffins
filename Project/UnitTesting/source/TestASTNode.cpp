#include <cppunit\config\SourcePrefix.h>

#include "TestASTNode.h"
#include "ASTNode.h"

void TestASTNode::setUp()
{}

void TestASTNode::tearDown()
{}

CPPUNIT_TEST_SUITE_REGISTRATION(TestASTNode);

void TestASTNode::testConstructor()
{
	ASTNode* node = new ASTNode("value", PROGRAM, 1);

	CPPUNIT_ASSERT("value" == node->getName());
	CPPUNIT_ASSERT_EQUAL(PROGRAM, node->getType());
	CPPUNIT_ASSERT_EQUAL(1, node->getStatementNumber());
}

void TestASTNode::testPrint()
{
	ASTNode* node;

	node = new ASTNode("haha", PROCEDURE, 0);
	CPPUNIT_ASSERT("haha:procedure");

	node = new ASTNode("hehe", ASSIGN, 1);
	CPPUNIT_ASSERT("hehe:assign:2");

	node = new ASTNode("", STATEMENT_LIST, 0);
	CPPUNIT_ASSERT(":stmtLst");
}

void TestASTNode::testEqual()
{
	ASTNode* node = new ASTNode("a", ASSIGN, 1);

	ASTNode* node1 = new ASTNode("a", ASSIGN, 1);
	CPPUNIT_ASSERT_EQUAL(true, node->equals(node1));
	
	ASTNode* node2 = new ASTNode("a", ASSIGN, 2);
	CPPUNIT_ASSERT_EQUAL(true, node->equals(node2));

	ASTNode* node3 = new ASTNode("a", WHILE, 1);
	CPPUNIT_ASSERT_EQUAL(false, node->equals(node3));
	
	ASTNode* node4 = new ASTNode("b", ASSIGN, 1);
	CPPUNIT_ASSERT_EQUAL(false, node->equals(node4));
}

void TestASTNode::testJoinChild()
{
	ASTNode* node1 = new ASTNode("", STATEMENT_LIST, 0);
	ASTNode* node2 = new ASTNode("", ASSIGN, 1);

	node1->joinChild(node2);

	CPPUNIT_ASSERT(node1->getChild()->print() == node2->print());
	CPPUNIT_ASSERT(node2->getParent()->print() == node1->print());
}

void TestASTNode::testJoinNext()
{
	ASTNode* node1 = new ASTNode("", PLUS, 0);
	ASTNode* node2 = new ASTNode("a", VARIABLE, 0);
	ASTNode* node3 = new ASTNode("1", CONSTANT, 0);

	node1->joinChild(node2);
	node2->joinNext(node3);

	CPPUNIT_ASSERT(node2->getNext()->print() == node3->print());
	CPPUNIT_ASSERT(node3->getPrevious()->print() == node2->print());
	CPPUNIT_ASSERT(node3->getParent()->print() == node1->print());
	
	node2 = new ASTNode("a", VARIABLE, 0);
	node3 = new ASTNode("1", CONSTANT, 0);

	node2->joinNext(node3);

	CPPUNIT_ASSERT(node2->getNext()->print() == node3->print());
	CPPUNIT_ASSERT(node3->getPrevious()->print() == node2->print());
	CPPUNIT_ASSERT(node3->getParent() == NULL);
}