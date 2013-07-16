#include "ASTNode.h"

#include <iostream>

ASTNode::ASTNode(std::string name, ASTType type, int stmtNum)
{
	_name = name;
	_type = type;
	_stmtNum = stmtNum;

	_next = NULL;
	_previous = NULL;

	_parent = NULL;
	_child = NULL;
}

ASTNode::~ASTNode(void)
{}

std::string ASTNode::getName()
{
	return _name;
}

ASTType ASTNode::getType()
{
	return _type;
}

int ASTNode::getStatementNumber()
{
	return _stmtNum;
}

ASTNode* ASTNode::getNext()
{
	return _next;
}

void ASTNode::setNext(ASTNode* next)
{
	_next = next;
}

ASTNode* ASTNode::getPrevious()
{
	return _previous;
}

void ASTNode::setPrevious(ASTNode* previous)
{
	_previous = previous;
}

ASTNode* ASTNode::getParent()
{
	return _parent;
}

void ASTNode::setParent(ASTNode* parent)
{
	_parent = parent;
}

ASTNode* ASTNode::getChild() 
{
	return _child;
}

void ASTNode::setChild(ASTNode* child) 
{
	_child = child;
}

std::string ASTNode::print()
{
	std::string text = _name + ":" + getTypeName(_type);

	if (_stmtNum > 0) {
		text.append(":" + std::to_string(long double(_stmtNum)));
	}

	return text;
}

std::string ASTNode::getTypeName(ASTType type)
{
	switch (_type)
	{
		case PROGRAM:
			return "program";
		case PROCEDURE:
			return "procedure";
		case STATEMENT_LIST:
			return "stmtLst";
		case ASSIGN:
			return "assign";
		case WHILE:
			return "while";
		case IF:
			return "if";
		case CALL:
			return "call";
		case VARIABLE:
			return "variable";
		case CONSTANT:
			return "constant";
		case PLUS:
			return "plus";
		case MINUS:
			return "minus";
		case TIMES:
			return "times";
		case DIVIDE:
			return "divide";
		default:
			return "error";
	}
}

bool ASTNode::equals(ASTNode* node)
{
	return _name == node->getName() && _type == node->getType();
}

void ASTNode::joinChild(ASTNode* child)
{
	setChild(child);
	child->setParent(this);
}

void ASTNode::joinNext(ASTNode* next)
{
	setNext(next);
	next->setPrevious(this);

	next->setParent(getParent());
}