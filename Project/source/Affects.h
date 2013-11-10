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
//#include "PKB.h"

using namespace std;

class Affects
{
public:
	Affects(AST* ast, Modifies* modifies, Uses* uses, Next* next, ProcTable* procTable, int stmtNum);
	~Affects(void);

	bool isAffects(int assignment1, int assignment2);
	bool isAffectsStar(int assignment1, int assignment2);
	bool exists();

	vector<int> getAffects(int assignment);
	vector<int> getAffected(int assignment);

	vector<int> getAffectsStar(int assignment);
	vector<int> getAffectedStar(int assignment);

	void clearCache();

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
	vector<int> seen;
	vector<bool> results;
	vector<int> temp;

	vector<vector<int>> cache;
	vector<vector<int>> cached;
	vector<pair<int, int>> pairs;
	vector<pair<int, int>> paired;

	pair<int, int> fix;

	bool compute(int assignment1, int assignment2);
	bool getPaths(int start, int end, string var);

	void computeAffects(int assignment);
	void computeAffected(int assignment);
};