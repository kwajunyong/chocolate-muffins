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

vector<vector<int>> Next::getPaths(int start, int end)
{
	init();
	if(start == end)
		same = true;
	if(start > end)
		startBigger = true;
	DFS(start, end);
	/*for(int i = 0; i < paths.size(); i++)
	{
		for(int j = 0; j < paths[i].size(); j++)
		{
			cout << "Path " << i << "is " << paths[i][j] << endl;
		}
	}*/
	return paths;
}

void Next::init()
{
	visited.clear();
	path.clear();
	paths.clear();
	reachedEnd = false;
	same = false;
	startBigger = false;
}

void Next::DFS(int stmtNum, int end)
{
	if(same && visited.size() == 0)
	{
		visited.push_back(-1);
	}
	else
	{
		visited.push_back(stmtNum);
	}
	
	for(int i = 0; i < next[stmtNum].size(); i++)
	{
		int v = next[stmtNum][i];
		if(v > end)
		{
			if(!same)
			{
				if(!startBigger)
				{
					if(path.size() > 0)
					{
						path.pop_back();
					}
					break;
				}
			}
		}
		if(find(visited.begin(), visited.end(), v) == visited.end()) // v not visited yet
		{
			path.push_back(v);
			//cout << v << endl;
			if(v == end)
			{
				reachedEnd = true;
				//path.pop_back(); // edited here
				paths.push_back(path);
				//path.clear();
				break;
			}
			DFS(v, end);

			if(reachedEnd)
			{
				visited.pop_back();
				//added here
				if(path.size() > 0) // edited here
				{
					if(find(path.begin(), path.end(), v) != path.end())
					{
						while(path.back() != v)
							path.pop_back();
						path.pop_back();
					}
					else
					{
						path.pop_back();
					}
				}
			}
			else// here
			{
				//if(visited.back() != v)
				if(path.size() > 0 && path.back() == v)
						path.pop_back();
			}
		}
		else
		{
			if(!reachedEnd)
			{
				if(next[v].size() > 1)
				{
					/*path.push_back(v);
					int x = next[v][1];
					path.push_back(x);
					DFS(x, end);*/
					paths.push_back(path);
				}
				else
				{
					path.pop_back();
				}
			}
		}// here
	}
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
//	n.getPaths(3,12);
//
//	/*if(n.isNext(3, 3, true))
//	{
//		cout << "true" << endl;
//	}
//	else
//	{
//		cout << "false" << endl;
//	}*/
//
//	//vector<int> querys = n.getNext(4, true); //Select n such that Next*(1,n)
//	//vector<int> querys = n.getPrevious(3, true);
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