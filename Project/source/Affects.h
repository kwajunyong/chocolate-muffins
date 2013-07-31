#pragma once

#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <algorithm>

using namespace std;

class Affects
{
public:
	Affects(void);
	~Affects(void);

	bool addAffects(int statementNo1, int statementNo2);
	bool isAffects(int statementNo1, int statementNo2, bool transitive);

	vector<int> getAffects(int statementNo, bool transitive);
	vector<int> getAffected(int statementNo, bool transitive);

private:
	map<int, vector<int>> affects;
	map<int, vector<int>> affected;

	bool compute(int statementNo1, int statementNo2);
}