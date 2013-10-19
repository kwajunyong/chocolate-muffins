#pragma once

#include "PKB.h"
#include "AST.h"
#include "Modifies.h"
#include "Uses.h"
#include "Next.h"

#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <algorithm>

// testing
#include "Parser.h"
#include "DesignExtractor.h"

using namespace std;

class Affects
{
public:
	Affects(PKB* p);
	~Affects(void);

	bool isAffects(int assignment1, int assignment2);

	vector<int> getAffects(int assignment);
	vector<int> getAffected(int assignment);

private:
	PKB* pkb;
	AST* ast;
	Modifies* modifies;
	Uses* uses;
	Next* next;
	ProcTable* procTable;

	map<int, vector<int>> affects;
	map<int, vector<int>> affected;

	vector<int> visited;

	bool checkElse;
	bool compute(int start, int end, string var);
}