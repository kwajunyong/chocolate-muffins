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

private:
	map<int, vector<int>> next;
	map<int, vector<int>> previous;

	bool compute(int stmtNum1, int stmtNum2);
};