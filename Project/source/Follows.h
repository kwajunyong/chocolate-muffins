#pragma once

#include <vector>
#include <map>
#include <stdio.h>
#include <iostream>
#include <queue>
#include <utility>
#include <algorithm>

using namespace std;

class Follows
{
public:
	Follows(void);
	~Follows(void);

	bool addFollows(int stmtNum1, int stmtNum2);
	bool isFollows(int stmtNum1, int stmtNum2, bool transitive);
	vector<int> getFollowedBy(int stmtNum, bool transitive);
	vector<int> getFollows(int stmtNum, bool transitive);

private:
	map<int, int> followedByMap;
	map<int, int> followsMap;

	void transitiveSearch(map<int, int> &input, vector<int> &output, int key);
	bool transitiveSearch(int key, int value);
};

