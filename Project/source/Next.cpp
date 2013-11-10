#include "Next.h"

using namespace std;

Next::Next(void) {}

Next::~Next(void) {}

vector<int> visited;
vector<int> path;
vector<vector<int>> paths;
bool same;
bool startBigger;

bool Next::addNext(int stmtNum1, int stmtNum2)
{
	for(int i = 0; i < next[stmtNum1].size(); i++)
	{
		if(next[stmtNum1][i] == stmtNum2)
		{
			return false;
		}
	}

	next[stmtNum1].push_back(stmtNum2);
	previous[stmtNum2].push_back(stmtNum1);
	return true;
}

bool Next::isNext(int stmtNum1, int stmtNum2, bool transitive)
{
	if(transitive)
	{
		visited.clear();
		if(compute(stmtNum1, stmtNum2))
			return true;
	}
	else
	{
		vector<int> querys = next[stmtNum1];
		
		for(int i = 0; i < querys.size(); i++)
		{
			if(querys[i] == stmtNum2)
			{
				return true;
			}
		}
	}
	return false;
}

vector<int> Next::getNext(int stmtNum, bool transitive)
{
	vector<int> answers;

	if(transitive)
	{
		visited.clear();
		answers = computeNext(stmtNum);
	}
	else
	{
		if(next.size() > 0)
		{
			answers = next[stmtNum];
		}
	}

	return answers;
}

vector<int> Next::getPrevious(int stmtNum, bool transitive)
{
	vector<int> answers;
	vector<vector<int>> temp;

	if(transitive)
	{
		visited.clear();
		answers = computePrevious(stmtNum);
	}
	else
	{
		if(previous.size() > 0)
		{
			answers = previous[stmtNum];
		}
	}

	return answers;
}

bool Next::compute(int stmtNum1, int stmtNum2)
{
	vector<int> querys = next[stmtNum1];
	bool check = false;

	if(stmtNum1 != stmtNum2)
		visited.push_back(stmtNum1);

	for(int i = 0; i < querys.size(); i++)
	{
		int temp = querys[i];

		if(temp == stmtNum2)
			return true;
		else
			if(find(visited.begin(), visited.end(), temp) == visited.end())
			{
				check = compute(temp, stmtNum2);
				if(check)
				break;
			}
	}
	return check;
}

vector<int> Next::computeNext(int stmtNum)
{
	vector<int> answers;
	vector<vector<int>> temp;

	answers = next[stmtNum];

	if(find(visited.begin(), visited.end(), stmtNum) == visited.end())
	{
		visited.push_back(stmtNum);

		for(int i = 0; i < answers.size(); i++)
		{
			if(answers.size() > 0)
			{
				temp.push_back(computeNext(answers[i]));
			}
		}

		for(int i = 0; i < temp.size(); i++)
		{
			for(int j = 0; j < temp[i].size(); j++)
			{
				if(find(answers.begin(), answers.end(), temp[i][j]) == answers.end())
				{
					answers.push_back(temp[i][j]);
				}
			}
		}
	}
	return answers;
}

vector<int> Next::computePrevious(int stmtNum)
{
	vector<int> answers;
	vector<vector<int>> temp;

	answers = previous[stmtNum];

	if(find(visited.begin(), visited.end(), stmtNum) == visited.end())
	{
		visited.push_back(stmtNum);

		for(int i = 0; i < answers.size(); i++)
		{
			if(answers.size() > 0)
			{
				temp.push_back(computePrevious(answers[i]));
			}
		}

		for(int i = 0; i < temp.size(); i++)
		{
			for(int j = 0; j < temp[i].size(); j++)
			{
				if(find(answers.begin(), answers.end(), temp[i][j]) == answers.end())
				{
					answers.push_back(temp[i][j]);
				}
			}
		}
	}
	return answers;
}

bool Next::exists()
{
	if(next.size() > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}