#include "Follows.h"

using namespace std;

Follows::Follows(void)
{}

Follows::~Follows(void)
{}

bool Follows::addFollows(int stmtNum1, int stmtNum2)
{
	if (followedByMap[stmtNum1] < 1) {
		followedByMap[stmtNum1] = stmtNum2;
		followsMap[stmtNum2] = stmtNum1;

		return true;
	} else {
		return false;
	}
}

bool Follows::isFollows(int stmtNum1, int stmtNum2, bool transitive)
{
	if (!transitive) {
		return followedByMap[stmtNum1] == stmtNum2;
	} else {
		return transitiveSearch(stmtNum1, stmtNum2);
	}
}

vector<int> Follows::getFollowedBy(int stmtNum, bool transitive)
{
	vector<int> results;

	if (!transitive) {
		int value = followedByMap[stmtNum];

		if (value > 0) {
			results.push_back(value);
		}
	} else {
		transitiveSearch(followedByMap, results, stmtNum);
	}

	return results;
}

vector<int> Follows::getFollows(int stmtNum, bool transitive)
{
	vector<int> results;

	if (!transitive) {
		int value = followsMap[stmtNum];

		if (value > 0) {
			results.push_back(value);
		}
	} else {
		transitiveSearch(followsMap, results, stmtNum);
	}

	return results;
}

bool Follows::exist() {
	return followedByMap.size() > 0;
}

void Follows::transitiveSearch(map<int, int> &input, vector<int> &output, int key)
{
	int value = input[key];

	if (value > 0) {
		output.push_back(value);

		transitiveSearch(input, output, value);
	}
}

bool Follows::transitiveSearch(int key, int value)
{
	int search = followedByMap[key];

	if (search == value) {
		return true;
	} else if (search < 1) {
		return false;
	} else {
		return transitiveSearch(search, value);
	} 
}