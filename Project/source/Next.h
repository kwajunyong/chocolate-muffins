#pragma once

#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <algorithm>

using namespace std;

class Next
{
public:
	Next(void);
	~Next(void);

	map<int, vector<int>> next;
	map<int, vector<int>> previous;

	bool addNext(int stmtNum1, int stmtNum2);
	bool isNext(int stmtNum1, int stmtNum2, bool transitive);
	bool exists();

	vector<int> getNext(int stmtNum, bool transitive);
	vector<int> getPrevious(int stmtNum, bool transitive);

private:
	bool reachedEnd;

	bool compute(int stmtNum1, int stmtNum2);
	vector<int> computeNext(int stmtNum);
	vector<int> computePrevious(int stmtNum);

	void init();
	void DFS(int start, int end);
};