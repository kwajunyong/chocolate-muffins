#pragma once

#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <algorithm>

using namespace std;

class Calls
{
public:
	Calls(void);
	~Calls(void);

	bool addCalls(string procedure1, string procedure2, int stmtNum);
	bool isCalls(string procedure1, string procedure2, bool transitive);

	vector<string> getCalls(string procedure, bool transitive);
	vector<string> getCalled(string procedure, bool transitive);
	vector<int> getCallsStmt(string procedure);

private:
	map<string, vector<string>> calls;
	map<string, vector<string>> called;
	map<string, vector<int>> callStmt;

	bool compute(string procedure1, string procedure2);

	string computeTransitive(string procedure, bool check);
};