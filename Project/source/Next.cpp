#include "Next.h"

;using namespace std;

Next::Next(void) {}

Next::~Next(void) {}

vector<int> visited;

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
	vector<vector<int>> temp;

	if(transitive)
	{
		answers = next[stmtNum];

		for(int i = 0; i < answers.size(); i++)
		{
			if(answers.size() > 0)
			{
				temp.push_back(getNext(answers[i], true));
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
		answers = previous[stmtNum];

		for(int i = 0; i < answers.size(); i++)
		{
			if(answers.size() > 0)
			{
				temp.push_back(getPrevious(answers[i], true));
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

//int main()
//{
//	Next n;
//
//	n.addNext(1, 2);
//	n.addNext(2, 3);
//	n.addNext(3, 4);
//	n.addNext(3, 7);
//	n.addNext(4, 5);
//	n.addNext(5, 6);
//	n.addNext(6, 3);
//	n.addNext(7, 8);
//	n.addNext(7, 9);
//	n.addNext(8, 10);
//	n.addNext(9, 10);
//	n.addNext(10, 11);
//	n.addNext(11, 12);
//
//	if(n.isNext(1, 12, true))
//	{
//		cout << "true" << endl;
//	}
//	else
//	{
//		cout << "false" << endl;
//	}
//
//	//vector<int> querys = n.getNext(1, false); //Select n such that Next*(1,n)
//	//vector<int> querys = n.getNexted(1, true);
//
//	/*for(int i = 0; i < querys.size(); i++)
//	{
//		int x = querys[i];
//		cout << x << endl;
//	}*/
//
//	system("Pause");
//	return 0;
//}