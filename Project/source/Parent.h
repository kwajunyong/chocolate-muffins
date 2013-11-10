#pragma once

#include <stdio.h>
#include <vector>
#include <map>
#include <queue>
#include <utility>
#include <algorithm>
#include <iostream>

using namespace std;

class Parent
{
public:
	Parent(void);
	~Parent(void);

	bool Parent::addParent(int stmtNum1, int stmtNum2);
	bool isParent(int stmtNum1, int stmtNum2, bool transitive);
	vector<int> getChild(int stmtNum, bool transitive);
	vector<int> getParent(int stmtNum, bool transitive);

	bool exist();
private:
	map<int, vector<int>> childMap;
	map<int, int> parentMap;
	
	void dfs(vector<int> &output, int stmtNum);
	void transitiveSearch(vector<int> &output, int key);
	bool transitiveSearch(int key, int value);

};

