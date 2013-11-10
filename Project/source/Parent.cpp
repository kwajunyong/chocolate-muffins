#include "Parent.h"

Parent::Parent(void)
{}

Parent::~Parent(void)
{}

bool Parent::addParent(int stmtNum1, int stmtNum2)
{
	if (parentMap[stmtNum2] < 1) {
		childMap[stmtNum1].push_back(stmtNum2);
		parentMap[stmtNum2] = stmtNum1;

		return true;
	} else {
		return false;
	}
}

bool Parent::isParent(int stmtNum1, int stmtNum2, bool transitive)
{
	if (!transitive) {
		return parentMap[stmtNum2] == stmtNum1;
	} else {
		return transitiveSearch(stmtNum1, stmtNum2);
	}
}

vector<int> Parent::getChild(int stmtNum, bool transitive)
{
	if (!transitive) {
		return childMap[stmtNum];
	} else {
		vector<int> results;

		dfs(results, stmtNum);

		return results;
	}
}

vector<int> Parent::getParent(int stmtNum, bool transitive)
{
	vector<int> results;

	if (!transitive) {
		int value = parentMap[stmtNum];

		if (value > 0) {
			results.push_back(value);
		}
	} else {
		transitiveSearch(results, stmtNum);
	}

	return results; 
}

bool Parent::exist()
{
	return parentMap.size() > 0;
}

void Parent::dfs(vector<int> &output, int key)
{
	vector<int> keys = childMap[key];

	for (size_t i = 0; i < keys.size(); i++) {
		output.push_back(keys[i]);

		dfs(output, keys[i]);
	}
}

void Parent::transitiveSearch(vector<int> &output, int key)
{
	int value = parentMap[key];

	if (value > 0) {
		output.push_back(value);

		transitiveSearch(output, value);
	}
}

bool Parent::transitiveSearch(int key, int value)
{
	int search = parentMap[value];

	if (search == key) {
		return true;
	} else if (search < 1) {
		return false;
	} else {
		return transitiveSearch(key, search);
	}
}