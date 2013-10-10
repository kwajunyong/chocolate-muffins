#include "Calls.h"

Calls::Calls(void) {}

Calls::~Calls(void) {}

bool Calls::addCalls(string procedure1, string procedure2)
{
	calls[procedure1].push_back(procedure2);
	called[procedure2].push_back(procedure1);
	return true;
}

bool Calls::addCalls(int stmtNum, string procedure)
{
	callStmt[procedure].push_back(stmtNum);
	return true;
}

bool Calls::isCalls(string procedure1, string procedure2, bool transitive)
{
	if(transitive)
	{
		if(compute(procedure1, procedure2))
			return true;
	}
	else
	{
		vector<string> querys = calls[procedure1];
		
		for(size_t i = 0; i < querys.size(); i++)
		{
			if(querys[i] == procedure2)
			{
				return true;
			}
		}
	}
	return false;
}

vector<string> Calls::getCalls(string procedure, bool transitive)
{
	vector<string> answers;
	vector<vector<string>> temp;

	if(transitive)
	{
		answers = calls[procedure];

		for(size_t i = 0; i < answers.size(); i++)
		{
			if(answers.size() > 0)
			{
				temp.push_back(getCalls(answers[i], true));
			}
		}

		for(size_t i = 0; i < temp.size(); i++)
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
	else
	{
		if(calls.size() > 0)
		{
			answers = calls[procedure];
		}
	}

	return answers;
}

vector<string> Calls::getCalled(string procedure, bool transitive)
{
	vector<string> answers;
	vector<vector<string>> temp;

	if(transitive)
	{
		answers = called[procedure];

		for(size_t i = 0; i < answers.size(); i++)
		{
			if(answers.size() > 0)
			{
				temp.push_back(getCalled(answers[i], true));
			}
		}

		for(size_t i = 0; i < temp.size(); i++)
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
	else
	{
		if(called.size() > 0)
		{
			answers = called[procedure];
		}
	}

	return answers;
}

vector<int> Calls::getCallsStmt(string procedure)
{
	vector<int> answers;

	if(callStmt.size() > 0)
	{
		answers = callStmt[procedure];
	}

	return answers;
}

bool Calls::compute(string procedure1, string procedure2)
{
	vector<string> querys = calls[procedure1];
	bool check = false;

	for(size_t i = 0; i < querys.size(); i++)
	{
		string temp = querys[i];

		if(temp == procedure2)
			return true;
		else
			check = compute(temp, procedure2);
			if(check)
				break;
	}
	return check;
}