#pragma once

#include <cppunit\extensions\HelperMacros.h>

#include <vector>

#include "AST.h"

class TestAST: public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE(TestAST);
	
	CPPUNIT_TEST(testTraverse);
	
	CPPUNIT_TEST(testGetStatementNode);
	CPPUNIT_TEST(testGetStatementType);
	
	CPPUNIT_TEST(testGetStatementNodes);
	CPPUNIT_TEST(testGetStatementNumbers);
	
	CPPUNIT_TEST(testMatchTree);
	CPPUNIT_TEST(testMatchSubTree);
	
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();
	
	void testTraverse();

	void testGetStatementNode();
	void testGetStatementType();
	
	void testGetStatementNodes();
	void testGetStatementNumbers();
	
	void testMatchTree();
	void testMatchSubTree();

private:
	AST* ast;

	ASTNode* buildTree();
	ASTNode* buildTreeWithDiffValue();
	ASTNode* buildSubTree();
	ASTNode* buildSubTreeWithDiffValue();
	ASTNode* buildSubTreeWithDiffStruct();

	std::vector<std::string> assign1();
	std::vector<std::string> assign2();
	std::vector<std::string> assign3();
	std::vector<std::string> assign4();
	std::vector<std::string> assign5();
};