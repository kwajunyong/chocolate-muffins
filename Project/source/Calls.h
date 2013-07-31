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

	bool addCalls(string procedure1, string procedure2);
	bool isCalls(string procedure1, string procedure2, bool transitive);

	vector<string> getCalls(string procedure, bool transitive);
	vector<string> getCalled(string procedure, bool transitive);

private:
	map<string, vector<string>> calls;
	map<string, vector<string>> called;

	bool compute(string procedure1, string procedure2);

	string computeTransitive(string procedure, bool check);
}