#pragma once

#include "Definition.h"

#include <vector>
#include <string>

class ASTNode
{
public:
	ASTNode(std::string name, ASTType type, int stmtNum);
	~ASTNode(void);

	std::string getName();
	ASTType getType();
	int getStatementNumber();

	ASTNode* getNext();
	void setNext(ASTNode* next);

	ASTNode* getPrevious();
	void setPrevious(ASTNode* previous);

	ASTNode* getParent();
	void setParent(ASTNode* parent);

	ASTNode* getChild();
	void setChild(ASTNode* child);

	std::string print();
	bool equals(ASTNode* node);

private:
	std::string _name;
	ASTType _type;
	int _stmtNum;

	ASTNode* _next;
	ASTNode* _previous;

	ASTNode* _parent;
	ASTNode* _child;

	std::string getTypeName(ASTType type);
};