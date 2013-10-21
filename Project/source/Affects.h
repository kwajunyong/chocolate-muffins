#pragma once

#include "AST.h"
#include "Modifies.h"
#include "Uses.h"
#include "Next.h"
#include "ProcTable.h"

#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <algorithm>

// testing
//#include "Parser.h"
//#include "DesignExtractor.h"

using namespace std;

class Affects
{
public:
	Affects(AST* ast, Modifies* modifies, Uses* uses, Next* next, ProcTable* procTable, int stmtNum);
	~Affects(void);

	bool isAffects(int assignment1, int assignment2);
	bool isAffectsStar(int assignment1, int assignment2);

	vector<int> getAffects(int assignment);
	vector<int> getAffected(int assignment);

	vector<int> getAffectsStar(int assignment);
	vector<int> getAffectedStar(int assignment);

private:
	AST* ast;
	Modifies* modifies;
	Uses* uses;
	Next* next;
	ProcTable* procTable;

	int numOfStmt;

	map<int, vector<int>> affects;
	map<int, vector<int>> affected;

	vector<int> visited;

	//bool compute(int start, int end, string var);
	bool compute(int assignment1, int assignment2);

	vector<int> computeAffects(int assignment);
	vector<int> computeAffected(int assignment);
};