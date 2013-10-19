#include "Affects.h"

;using namespace std;

Affects::Affects(PKB* p)
{
	pkb = p;
	ast = pkb->getAST();
	modifies = pkb->getModifies();
	uses = pkb->getUses();
	next = pkb->getNext();
	procTable = pkb->getProcTable();
	checkElse = false;
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

	/*visited.clear();
	return compute(assignment1, assignment2, var);*/

	vector<vector<int>> paths = next->getPaths(assignment1, assignment2);
	vector<bool> path;
	path.assign(paths.size(), true);

	if(paths.size() == 0)
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
					path[i] = false;
					if(paths.size() < 1)
						i++;
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
			return true;
		}
	}
	return false;
}

//bool Affects::compute(int start, int end, string var)
//{
//	visited.push_back(start);
//	for(int i = start+1; i < end; i++)
//	{
//		if(find(visited.begin(), visited.end(), i) == visited.end())
//		{
//			int x = i-1;
//			if(checkElse)
//			{
//				x = i-2;
//				checkElse = false;
//			}
//			
//			if(next->isNext(x, i, true))
//			{
//				visited.push_back(i);
//				cout << i << endl;
//				
//				if(ast->getStatementType(i) == ASSIGN)
//				{
//					if(modifies->isModifiesStmt(i, var))
//						return false;
//				}
//				else if(ast->getStatementType(i) == WHILE)
//				{
//					if(next->getNext(i, false).size() == 1)
//					{
//						i = i;
//					}
//					else
//					{
//						int j = next->getNext(i, false)[0];
//						int k = next->getNext(i, false)[1];
//						if(k > j)
//							j = k;
//						if(end < j)
//						{
//							i = i;
//						}
//						else
//						{
//							i = j-1;
//						}
//					}
//				}
//				else if(ast->getStatementType(i) == IF)
//				{
//					int j = next->getNext(i, false)[0];
//					int k = next->getNext(i, false)[1];
//					
//					bool thenBranch = compute(j-1, end, var);
//					checkElse = true;
//					bool elseBranch = compute(k-1, end, var);
//
//					if(!thenBranch && !elseBranch)
//					{
//						return false;
//					}
//					else
//					{
//						return true;
//					}
//				}
//				else if(ast->getStatementType(i) == CALL)
//				{
//					if(modifies->isModifiesStmt(i, var))
//						return false;
//				}
//			}
//			else // Next* branch
//			{
//				i = next->getNext(i-1, false)[0]-1;
//			}
//		}
//		else // Visited branch
//		{
//			if(next->getNext(i-1, false).size() == 1)
//			{
//				i = i;
//			}
//			else
//			{
//					int j = next->getNext(i-1, false)[0];
//					int k = next->getNext(i-1, false)[1];
//					if(k > j)
//					{
//						j = k;
//					}
//					i = j;
//			}
//		}
//	}
//	return true;
//}

vector<int> Affects::getAffects(int assignment)
{
	vector<int> results;
	int end = pkb->getNumOfStmt();

	vector<string> variables = modifies->getModifiedVar(assignment);
	string var = variables[0];
	
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

	int end = pkb->getNumOfStmt();

	vector<string> variables = modifies->getModifiedVar(assignment);
	string var = variables[0];
	
	for(int i = end; i > 0; i--)
	{
		if(isAffects(i, assignment))
		{
			results.push_back(i);
		}
	}

	return results;
}

//int main()
//{
//	Parser p;
//	DesignExtractor d;
//	PKB* pkb;
//
//	try
//	{
//		//pkb = p.parse("CS3201Assignment1Source.txt");
//		pkb = p.parse("Test.txt");
//		//pkb = p.parse("Integration.txt");
//		d.extract(pkb);
//	} catch (ParseException pe) {
//		cout << pe.what();
//		getchar();
//		return 0;
//	}
//
//	Affects a(pkb);
//
//	/* Start CS3201Assignment1Source.txt */
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
//	//// Should return false
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
//	///*End of CS3201AssignmentSource1.txt */
//	//
//
//
//
//	///* Start of Test.txt */
//	//// Should return true
//	//if(a.isAffects(1, 4))
//	//	cout << "Affects(1,4) = true" << endl;
//	//else
//	//	cout << "Affects(1,4) = false" << endl;
//
//	//if(a.isAffects(2, 6))
//	//	cout << "Affects(2,6) = true" << endl;
//	//else
//	//	cout << "Affects(2,6) = false" << endl;
//
//	//if(a.isAffects(4, 8))
//	//	cout << "Affects(4,8) = true" << endl;
//	//else
//	//	cout << "Affects(4,8) = false" << endl;
//
//	//if(a.isAffects(4, 10))
//	//	cout << "Affects(4,10) = true" << endl;
//	//else
//	//	cout << "Affects(4,10) = false" << endl;
//
//	//if(a.isAffects(9, 10))
//	//	cout << "Affects(9,10) = true" << endl;
//	//else
//	//	cout << "Affects(9,10) = false" << endl;
//
//	//if(a.isAffects(1, 10))
//	//	cout << "Affects(1,10) = true" << endl;
//	//else
//	//	cout << "Affects(1,10) = false" << endl;
//
//	//if(a.isAffects(2, 10))
//	//	cout << "Affects(2,10) = true" << endl;
//	//else
//	//	cout << "Affects(2,10) = false" << endl;
//
//	//if(a.isAffects(1, 12))
//	//	cout << "Affects(1,12) = true" << endl;
//	//else
//	//	cout << "Affects(1,12) = false" << endl;
//
//	//if(a.isAffects(4, 4))
//	//	cout << "Affects(4,4) = true" << endl;
//	//else
//	//	cout << "Affects(4,4) = false" << endl;
//
//	//if(a.isAffects(6, 6))
//	//	cout << "Affects(6,6) = true" << endl;
//	//else
//	//	cout << "Affects(6,6) = false" << endl;
//
//	//if(a.isAffects(8, 10))
//	//	cout << "Affects(8,10) = true" << endl;
//	//else
//	//	cout << "Affects(8,10) = false" << endl;
//
//	//if(a.isAffects(4, 12))
//	//	cout << "Affects(4,12) = true" << endl;
//	//else
//	//	cout << "Affects(4,12) = false" << endl;
//
//	//// Should return False
//	//if(a.isAffects(9, 11))
//	//	cout << "Affects(9,11) = true" << endl;
//	//else
//	//	cout << "Affects(9,11) = false" << endl;
//	/*End of Test.txt */
//
//	vector<int> querys = a.getAffects(4);
//	//vector<int> querys = a.getAffected(15);
//
//	for(int i = 0; i < querys.size(); i++)
//	{
//		cout << querys[i] << endl;
//	}
//
//	system("Pause");
//	return 0;
//}