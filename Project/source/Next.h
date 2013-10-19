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

	bool addNext(int stmtNum1, int stmtNum2);
	bool isNext(int stmtNum1, int stmtNum2, bool transitive);

	vector<int> getNext(int stmtNum, bool transitive);
	vector<int> getPrevious(int stmtNum, bool transitive);

	vector<vector<int>> getPaths(int start, int end);

private:
	map<int, vector<int>> next;
	map<int, vector<int>> previous;

	/*vector<int> visited;
	vector<int> path;
	vector<vector<int>> paths;*/

	bool reachedEnd;

	bool compute(int stmtNum1, int stmtNum2);
	vector<int> computeNext(int stmtNum);
	vector<int> computePrevious(int stmtNum);

	void init();
	void DFS(int start, int end);
};