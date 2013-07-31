#include "Affects.h"

;using namespace std;

Affects::Affects(void) {}
Affects::~Affects(void) {}

bool Affects::addAffects(int statementNo1, int statementNo2)
{
	affects[statementNo1].push_back(statementNo2);
	affected[statementNo2].push_back(statementNo1);
	return true;
}

bool Affects::isAffects(int statementNo1, int statementNo2, bool transitive)
{
	if(transitive)
	{
		if(compute(statementNo1, statementNo2))
			return true;
	}
	else
	{
		vector<int> querys = affects[statementNo1];
		
		for(int i = 0; i < querys.size(); i++)
		{
			if(querys[i] == statementNo2)
			{
				return true;
			}
		}
	}
	return false;
}

vector<int> Affects::getAffects(int statementNo, bool transitive)
{
	vector<int> answers;
	vector<vector<int>> temp;

	if(transitive)
	{
		answers = affects[statementNo];

		if(answers.size() == 0)
		{
			answers.push_back(statementNo);
			return answers;
		}

		/*if(answers.size() == 1)
		{
			return answers;
		}*/

		for(int i = 0; i < answers.size(); i++)
		{
			if(answers.size() > 0)
			{
				temp.push_back(getAffects(answers[i], true));
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
		if(affects.size() > 0)
		{
			answers = affects[statementNo];
		}
	}

	return answers;
}

vector<int> Affects::getAffected(int statementNo, bool transitive)
{
	vector<int> answers;
	vector<vector<int>> temp;

	if(transitive)
	{
		answers = affected[statementNo];

		/*if(answers.size() == 0)
		{
			answers.push_back(procedure);
			return answers;
		}*/

		/*if(answers.size() == 1)
		{
			return answers;
		}*/

		for(int i = 0; i < answers.size(); i++)
		{
			if(answers.size() > 0)
			{
				temp.push_back(getAffected(answers[i], true));
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
		if(affected.size() > 0)
		{
			answers = affected[statementNo];
		}
	}

	return answers;
}

bool Affects::compute(int statementNo1, int statementNo2)
{
	vector<int> querys = affects[statementNo1];
	bool check = false;

	for(int i = 0; i < querys.size(); i++)
	{
		int temp = querys[i];

		if(temp == statementNo2)
			return true;
		else
			check = compute(temp, statementNo2);
			if(check)
				break;
	}
	return check;
}

//int main()
//{
//	Affects a;
//
//	a.addAffects(1, 2);
//	a.addAffects(1, 3);
//	a.addAffects(1, 4);
//	a.addAffects(2, 5);
//	a.addAffects(3, 6);
//
//	//vector<int> querys = a.getAffects(1, true);
//	vector<int> querys = a.getAffected(1, true);
//
//	for(int i = 0; i < querys.size(); i++)
//	{
//		int x = querys[i];
//		cout << x << endl;
//	}
//
//	/*if(a.isAffects(1, 5, true))
//	{
//		cout << "true" << endl;
//	}
//	else
//	{
//		cout << "false" << endl;
//	}*/
//
//	system("Pause");
//	return 0;
//}