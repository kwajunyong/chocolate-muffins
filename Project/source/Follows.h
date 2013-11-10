#pragma once

#include <vector>
#include <map>

class Follows
{
public:
	Follows(void);
	~Follows(void);

	bool addFollows(int stmtNum1, int stmtNum2);
	bool isFollows(int stmtNum1, int stmtNum2, bool transitive);
	std::vector<int> getFollowedBy(int stmtNum, bool transitive);
	std::vector<int> getFollows(int stmtNum, bool transitive);

	bool exist();

private:
	std::map<int, int> followedByMap;
	std::map<int, int> followsMap;

	void transitiveSearch(std::map<int, int> &input, std::vector<int> &output, int key);
	bool transitiveSearch(int key, int value);
};

