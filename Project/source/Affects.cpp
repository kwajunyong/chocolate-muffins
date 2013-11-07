#include "Affects.h"

using namespace std;

Affects::Affects(AST* ast, Modifies* modifies, Uses* uses, Next* next, ProcTable* procTable, int stmtNum)
{
	time = 0;
	times = 0;
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

	/*vector<vector<int>> paths = next->getPaths(assignment1, assignment2);
	vector<bool> path;
	path.assign(paths.size(), true);

	if(paths.size() == 0 || paths[0].empty())
	{
		if(uses->isUsesStmt(assignment2, var))
			return true;
	}

	for(int i = 0; i < paths.size(); i++)
	{
		for(int j = 0; j < paths[i].size(); j++)
		{
			int x = paths[i][j];
			
			if(ast->getStatementType(x) == ASSIGN)
			{
				if(modifies->isModifiesStmt(x, var))
				{
					if(x != assignment2)
					{
						path[i] = false;
						if(paths.size() < 1)
							i++;
					}
				}
			}
			else if(ast->getStatementType(x) == CALL)
			{
				if(modifies->isModifiesStmt(x, var))
				{
					path[i] = false;
					if(paths.size() < 1)
						i++;
				}
			}
		}
		if(path[i])
		{
			if(!paths[i].empty())
			{
				if(paths[i].back() != assignment2)
					path[i] = false;
				else
					return true;
			}
		}
	}
	return false;*/

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
	// stopped here
	/*if(start == assignment2)
		if(!next->isNext(start, assignment2, true))
			return false;*/
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
	int end = numOfStmt;
	
	for(int i = 1; i <= end; i++)
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

	int end = numOfStmt;
	
	for(int i = end; i > 0; i--)
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
	//visited.clear();
	visited.assign(numOfStmt+1, false);
	results.assign(numOfStmt+1, false);
	//pairs.clear();
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
	map<int, bool> mapAns;

	if(!cache[assignment].empty() && cache[assignment][0] != -1)
	{
		answers = cache[assignment];
		for(int i = 0; i < answers.size(); i++)
		{
			mapAns[answers[i]] = true;
		}

		if(find(visited.begin(), visited.end(), assignment) == visited.end())
			visited.push_back(assignment);

			for(int i = 0; i < answers.size(); i++)
			{
				results[answers[i]] = true;
			}
	}
	else
	{
		vector<int> holder;

		answers = getAffects(assignment);
		for(int i = 0; i < answers.size(); i++)
		{
			mapAns[answers[i]] = true;
		}

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
							//times++;
							//if(find(answers.begin(), answers.end(), temp[j]) == answers.end())
							if(!mapAns[temp[j]])
							{
								mapAns[temp[j]] = true;
								answers.push_back(temp[j]);
								//holder.push_back(temp[j]);
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
			/*for(int k = 0; k < holder.size(); k++)
			{
				times++;
				answers.push_back(holder[k]);
			}*/

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
	//paired.clear();
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
	//pairs.clear();
}

bool Affects::getPaths(int stmtNum, int end, string var)
{
	bool ans = false;
	//int v = next->next[stmtNum][0];
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
			//ans = getPaths(v, end, var);
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

//int main()
//{
//	Parser p;
//	DesignExtractor d;
//	PKB* pkb;
//	/*AST* ast;
//	Modifies* modifies;
//	Uses* uses;
//	Next* next;
//	ProcTable* procTable;
//	int numOfStmt = 0;*/
//
//	try
//	{
//		pkb = p.parse("CS3201Assignment1Source.txt");
//		//pkb = p.parse("Test.txt");
//		//pkb = p.parse("Integration.txt");
//		d.extract(pkb);
//	} catch (ParseException pe) {
//		cout << pe.what();
//		getchar();
//		return 0;
//	}
//
//	Affects a;
//	a = pkb->getAffects();
//
//	// Start CS3201Assignment1Source.txt
//	// Should return true
//	/*if(a.isAffects(1, 2))
//		cout << "Affects(1,2) = true" << endl;
//	else
//		cout << "Affects(1,2) = false" << endl;
//
//	if(a.isAffects(1, 3))
//		cout << "Affects(1,3) = true" << endl;
//	else
//		cout << "Affects(1,3) = false" << endl;
//
//	if(a.isAffects(25, 26))
//		cout << "Affects(25,26) = true" << endl;
//	else
//		cout << "Affects(25,26) = false" << endl;
//
//	if(a.isAffects(25, 27))
//		cout << "Affects(25,27) = true" << endl;
//	else
//		cout << "Affects(25,27) = false" << endl;*/
//
//	// Should return false
//	/*if(a.isAffects(1, 4))
//		cout << "Affects(1,4) = true" << endl;
//	else
//		cout << "Affects(1,4) = false" << endl;
//
//	if(a.isAffects(2, 5))
//		cout << "Affects(2,5) = true" << endl;
//	else
//		cout << "Affects(2,5) = false" << endl;
//
//	if(a.isAffects(2, 7))
//		cout << "Affects(2,7) = true" << endl;
//	else
//		cout << "Affects(2,7) = false" << endl;
//
//	if(a.isAffects(3, 11))
//		cout << "Affects(3,11) = true" << endl;
//	else
//		cout << "Affects(3,11) = false" << endl;*/
//	//End of CS3201AssignmentSource1.txt
//	
//
//
//
//	// Start of Test.txt 
//	// Should return true
//	/*if(a.isAffects(1, 4))
//		cout << "Affects(1,4) = true" << endl;
//	else
//		cout << "Affects(1,4) = false" << endl;
//
//	if(a.isAffects(2, 6))
//		cout << "Affects(2,6) = true" << endl;
//	else
//		cout << "Affects(2,6) = false" << endl;
//
//	if(a.isAffects(4, 8))
//		cout << "Affects(4,8) = true" << endl;
//	else
//		cout << "Affects(4,8) = false" << endl;
//
//	if(a.isAffects(4, 10))
//		cout << "Affects(4,10) = true" << endl;
//	else
//		cout << "Affects(4,10) = false" << endl;
//
//	if(a.isAffects(9, 10))
//		cout << "Affects(9,10) = true" << endl;
//	else
//		cout << "Affects(9,10) = false" << endl;
//
//	if(a.isAffects(1, 10))
//		cout << "Affects(1,10) = true" << endl;
//	else
//		cout << "Affects(1,10) = false" << endl;
//
//	if(a.isAffects(2, 10))
//		cout << "Affects(2,10) = true" << endl;
//	else
//		cout << "Affects(2,10) = false" << endl;
//
//	if(a.isAffects(1, 12))
//		cout << "Affects(1,12) = true" << endl;
//	else
//		cout << "Affects(1,12) = false" << endl;
//
//	if(a.isAffects(4, 4))
//		cout << "Affects(4,4) = true" << endl;
//	else
//		cout << "Affects(4,4) = false" << endl;
//
//	if(a.isAffects(6, 6))
//		cout << "Affects(6,6) = true" << endl;
//	else
//		cout << "Affects(6,6) = false" << endl;
//
//	if(a.isAffects(8, 10))
//		cout << "Affects(8,10) = true" << endl;
//	else
//		cout << "Affects(8,10) = false" << endl;
//
//	if(a.isAffects(4, 12))
//		cout << "Affects(4,12) = true" << endl;
//	else
//		cout << "Affects(4,12) = false" << endl;*/
//
//	// Should return False
//	/*if(a.isAffects(9, 11))
//		cout << "Affects(9,11) = true" << endl;
//	else
//		cout << "Affects(9,11) = false" << endl;*/
//	/*End of Test.txt */
//
//	/*vector<int> querys = a.getAffects(22);
//	vector<int> querys = a.getAffected(15);*/
//
//	/*for(int i = 0; i < querys.size(); i++)
//	{
//		cout << querys[i] << endl;
//	}*/
//
//	/*Affects*
//	 Start of CS3102Assignment1Query.txt
//	 Should return true*/
//	/*if(a.isAffectsStar(1, 2))
//		cout << "Affects*(1,2) = true" << endl;
//	else
//		cout << "Affects*(1,2) = false" << endl;
//
//	if(a.isAffectsStar(1, 3))
//		cout << "Affects*(1,3) = true" << endl;
//	else
//		cout << "Affects*(1,3) = false" << endl;
//
//	if(a.isAffectsStar(1, 5))
//		cout << "Affects*(1,5) = true" << endl;
//	else
//		cout << "Affects*(1,5) = false" << endl;
//
//	if(a.isAffectsStar(11, 11))
//		cout << "Affects*(11,11) = true" << endl;
//	else
//		cout << "Affects*(11,11) = false" << endl;
//
//	if(a.isAffectsStar(11, 13))
//		cout << "Affects*(11,13) = true" << endl;
//	else
//		cout << "Affects*(11,13) = false" << endl;
//
//	if(a.isAffectsStar(21, 22))
//		cout << "Affects*(21,22) = true" << endl;
//	else
//		cout << "Affects*(21,22) = false" << endl;*/
//
//	//Should return false
//	/*if(a.isAffectsStar(1, 7))
//		cout << "Affects*(1,7) = true" << endl;
//	else
//		cout << "Affects*(1,7) = false" << endl;*/
//	 //End of CS3201AssignmentQuery.txt
//
//	/*vector<int> querys = a.getAffectsStar(22);
//	vector<int> querys = a.getAffectedStar(28);
//
//	for(int i = 0; i < querys.size(); i++)
//	{
//		cout << querys[i] << endl;
//	}*/
//
//	system("Pause");
//	return 0;
//}