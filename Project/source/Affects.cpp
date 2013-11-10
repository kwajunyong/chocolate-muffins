#include "Affects.h"

using namespace std;

Affects::Affects(AST* ast, Modifies* modifies, Uses* uses, Next* next, ProcTable* procTable, int stmtNum)
{
	this->ast = ast;
	this->modifies = modifies;
	this->uses = uses;
	this->next = next;
	this->procTable = procTable;
	numOfStmt = stmtNum;
	cache.assign(numOfStmt+1, temp);
	cached.assign(numOfStmt+1, temp);
}

Affects::~Affects(void) {}

bool Affects::isAffects(int assignment1, int assignment2)
{
	// Check if assignment1 and assignment2 are Assignment statements. If both are not, return false
	if(ast->getStatementType(assignment1) != ASSIGN || ast->getStatementType(assignment2) != ASSIGN)
	{
		return false;
	}

	// Check if assignment1 and assignment 2 are in the same procedure.
	if(procTable->getProcedure(assignment1) != procTable->getProcedure(assignment2))
	{
		return false;
	}

	// Check if assignment1 and assignment2 has a control flow path, Next*(assignment1, assignment2). If not true, return false
	if(assignment1 == assignment2)
		if(!next->isNext(assignment1, assignment2, true))
		{
			return false;
		}

	vector<string> variables;
	string var;

	variables = modifies->getModifiedVar(assignment1);
	var = variables[0];

	// Check if assignment2 uses variable var. If not true, return false
	if(!uses->isUsesStmt(assignment2, var))
	{
		return false;
	}

	int start = 0;
	seen.clear();
	if(next->next[assignment1].size() > 0)
	{
		start = next->next[assignment1][0];
	}
	else
	{
		start = assignment1;
	}

	return getPaths(start, assignment2, var);
}

bool Affects::isAffectsStar(int assignment1, int assignment2)
{
	visited.clear();
	return compute(assignment1, assignment2);
}

bool Affects::compute(int assignment1, int assignment2)
{
	vector<int> querys = getAffects(assignment1);
	bool check = false;

	visited.push_back(assignment1);

	for(int i = 0; i < querys.size(); i++)
	{
		if(querys[i] == assignment2)
			return true;
		else
		{
			if(find(visited.begin(), visited.end(), querys[i]) == visited.end())
			{
				check = compute(querys[i], assignment2);
				if(check)
					break;
			}
		}
	}
	return check;
}

vector<int> Affects::getAffects(int assignment)
{
	vector<int> results;
	pair<int, int> range = procTable->getRange(procTable->getProcedure(assignment));
	int start = range.first;
	int end = range.second;
	
	for(int i = start; i <= end; i++)
	{
		if(isAffects(assignment, i))
		{
			results.push_back(i);
		}
	}
	return results;
}

vector<int> Affects::getAffected(int assignment)
{
	vector<int> results;
	pair<int, int> range = procTable->getRange(procTable->getProcedure(assignment));
	int start = range.first;
	int end = range.second;
	
	for(int i = start; i <= end; i++)
	{
		if(isAffects(i, assignment))
		{
			results.push_back(i);
		}
	}
	return results;
}

vector<int> Affects::getAffectsStar(int assignment)
{
	visited.assign(numOfStmt+1, false);
	results.assign(numOfStmt+1, false);

	if(assignment > numOfStmt || assignment < 0)
		return vector<int>();

	computeAffects(assignment);
	
	for(int i = 0; i < pairs.size(); i++)
	{
		if(pairs[i].first != pairs[i].second)
		{
			cache[pairs[i].second] = cache[pairs[i].first];
		}
	}

	vector<int> answers;
	for(int i = 1; i < results.size(); i++)
	{
		if(results[i])
			answers.push_back(i);
	}
	return answers;
}

void Affects::computeAffects(int assignment)
{
	vector<int> answers;
	vector<int> temp;
	bool allCached = true;

	if(!cache[assignment].empty() && cache[assignment][0] != -1)
	{
		answers = cache[assignment];
		
		if(find(visited.begin(), visited.end(), assignment) == visited.end())
			visited.push_back(assignment);

			for(int i = 0; i < answers.size(); i++)
			{
				results[answers[i]] = true;
			}
	}
	else
	{
		answers = getAffects(assignment);

		// if leaf node
		if(answers.size() == 0)
		{
			if(cache[assignment].size() != 1)
				cache[assignment].push_back(0);
		}

		if(find(visited.begin(), visited.end(), assignment) == visited.end())
		{
			visited.push_back(assignment);

			for(int i = 0; i < answers.size(); i++)
			{
				results[answers[i]] = true;
				computeAffects(answers[i]);
			}

			// return from recursion
			for(int i = 0; i < answers.size(); i++)
			{
				if(!cache[answers[i]].empty())
				{
					temp = cache[answers[i]];
					if(temp[0] != 0)
					{
						if(temp[0] == -1)
						{
							if(answers[i] == assignment)
								temp[0] = assignment;
							else
								temp[0] = answers[i];
								fix.first = temp[0];
								fix.second = assignment;
								if(fix.first != fix.second)
									pairs.push_back(fix);
						}
						for(int j = 0; j < temp.size(); j++)
						{
							if(find(answers.begin(), answers.end(), temp[j]) == answers.end())
							{
								answers.push_back(temp[j]);
							}
						}
					}
				}
				else
				{
					allCached = false;
					break;
				}
			}

			if(allCached)
			{
				if(answers.size() != 0)
					cache[assignment] = answers;
			}
		}
		else
		{
			// Assignment affects itself
			if(cache[assignment].size() != 1)
				cache[assignment].push_back(-1);
		}
	}
}

vector<int> Affects::getAffectedStar(int assignment)
{
	visited.clear();
	results.assign(numOfStmt+1, false);

	if(assignment > numOfStmt || assignment < 0)
		return vector<int>();

	computeAffected(assignment);

	for(int i = 0; i < paired.size(); i++)
	{
		if(paired[i].first != paired[i].second)
		{
			cached[paired[i].second] = cached[paired[i].first];
		}
	}

	vector<int> answers;
	for(int i = 1; i < results.size(); i++)
	{
		if(results[i])
			answers.push_back(i);
	}
	return answers;
}

void Affects::computeAffected(int assignment)
{
	vector<int> answers;
	vector<int> temp;
	bool allCached = true;

	if(!cached[assignment].empty() && cached[assignment][0] != -1)
	{
		answers = cached[assignment];

		if(find(visited.begin(), visited.end(), assignment) == visited.end())
			visited.push_back(assignment);
		
			for(int i = 0; i < answers.size(); i++)
			{
				results[answers[i]] = true;
			}
	}
	else
	{
		answers = getAffected(assignment);

		// if leaf node
		if(answers.size() == 0)
		{
			if(cached[assignment].size() != 1)
				cached[assignment].push_back(0);
		}

		if(find(visited.begin(), visited.end(), assignment) == visited.end())
		{
			visited.push_back(assignment);

			for(int i = 0; i < answers.size(); i++)
			{
				results[answers[i]] = true;
				computeAffected(answers[i]);
			}
			// return from recursion
			for(int i = 0; i < answers.size(); i++)
			{
				if(!cached[answers[i]].empty())
				{
					temp = cached[answers[i]];
					if(temp[0] != 0)
					{
						if(temp[0] == -1)
						{
							if(answers[i] == assignment)
								temp[0] = assignment;
							else
								temp[0] = answers[i];
								fix.first = temp[0];
								fix.second = assignment;
								if(fix.first != fix.second)
									paired.push_back(fix);
						}
						for(int j = 0; j < temp.size(); j++)
						{
							if(find(answers.begin(), answers.end(), temp[j]) == answers.end())
							{
								answers.push_back(temp[j]);
							}
						}
					}
				}
				else
				{
					allCached = false;
					break;
				}
			}
			if(allCached)
			{
				if(answers.size() != 0)
					cached[assignment] = answers;
			}
		}
		else
		{
			// Assignment affects itself
			if(cached[assignment].size() != 1)
				cached[assignment].push_back(-1);
		}
	}
}

void Affects::clearCache()
{
	cache.assign(numOfStmt+1, temp);
	cached.assign(numOfStmt+1, temp);
}

bool Affects::getPaths(int stmtNum, int end, string var)
{
	bool ans = false;
	if(find(seen.begin(), seen.end(), stmtNum) == seen.end())
	{
		seen.push_back(stmtNum);

		if(stmtNum == end)
				return true;
		if(ast->getStatementType(stmtNum) == ASSIGN || ast->getStatementType(stmtNum) == CALL)
		{
			if(modifies->isModifiesStmt(stmtNum, var))
			{
				return false;
			}
			else
			{
				int start = 0;
				if(next->next[stmtNum].size() > 0)
				{
					start = next->next[stmtNum][0];
				}
				else
				{
					start = stmtNum;
				}
				ans = getPaths(start, end, var);
			}
		}
		else if(ast->getStatementType(stmtNum) == WHILE)
		{
			if(next->next[stmtNum].size() > 1)
			{
				int x = next->next[stmtNum][1];
				int y = next->next[stmtNum][0];
				if(end > x)
				{
					ans = getPaths(x, end, var);
					if(!ans)
						ans = getPaths(y, end, var);
				}
				else
				{
					ans = getPaths(y , end, var);
					if(!ans)
						ans = getPaths(x, end, var);
				}
			}
			else
			{
				int x = next->next[stmtNum][0];
				ans = getPaths(x, end, var);
			}
		}
		else if(ast->getStatementType(stmtNum) == IF)
		{
			int x = next->next[stmtNum][0];
			int y = next->next[stmtNum][1];

			ans = getPaths(x, end, var);
			if(ans)
				return true;
			ans = getPaths(y , end, var);
			if(ans)
				return true;
		}
	}
	return ans;
}

bool Affects::exists()
{
	vector<int> temp;
	for(int i = 1; i <= numOfStmt; i++)
	{
		temp = getAffects(i);
		if(!temp.empty())
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}