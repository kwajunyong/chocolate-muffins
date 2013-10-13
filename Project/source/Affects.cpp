#include "Affects.h"

;using namespace std;

Affects::Affects(PKB* p)
{
	pkb = p;
	ast = pkb->getAST();
	modifies = pkb->getModifies();
	uses = pkb->getUses();
	next = pkb->getNext();
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

	visited.clear();
	return compute(assignment1, assignment2, var);
}

// From start to end, check whether the 2 statements are in Next*(i-1, i) relationship.
// If they are, proceed with checking, else use Next(i-1) to skip to next statement.
//
// The Next* checking is for handling if else loops.
// The visited checking is to handle cycles for while loops.
//
// When i = Assignment statement, check Modifies(i, var), if true return false.
//
// When i = While loop, skip to the end of the while statement.
// If end falls within the while loop, carry on checking in while loop.
// Else if end is outside of while loop, immediately go to the end of while loop and carry on checking.
//
// When i = If-Else loop,
// The algorithm continues in a recursive nature whenever we encounter an If-Else loop.
// For If-Else, check both THEN and ELSE branches, if both are false, return false.
//
// Work in progress:
// 1. The boolean checkElse might have loopholes, shall do further testing with complicated source code to confirm.
// 2. Have not done checking for whether both start and end are in the same procedure.
// 3. Have not done testing whether calling a procedure modifies a variable.
//

bool Affects::compute(int start, int end, string var)
{
	visited.push_back(start);
	for(int i = start+1; i < end; i++)
	{
		if(find(visited.begin(), visited.end(), i) == visited.end())
		{
			int x = i-1;
			if(checkElse)
			{
				x = i-2;
				checkElse = false;
			}
			
			if(next->isNext(x, i, true))
			{
				visited.push_back(i);
				cout << i << endl;
				
				if(ast->getStatementType(i) == ASSIGN)
				{
					if(modifies->isModifiesStmt(i, var))
						return false;
				}
				else if(ast->getStatementType(i) == WHILE)
				{
					int j = next->getNext(i, false)[0];
					int k = next->getNext(i, false)[1];
					if(k > j)
						j = k;
					if(end < j)
					{
						i = i;
					}
					else
					{
						i = j-1;
					}
				}
				else if(ast->getStatementType(i) == IF)
				{
					int j = next->getNext(i, false)[0];
					int k = next->getNext(i, false)[1];
					
					bool thenBranch = compute(j-1, end, var);
					checkElse = true;
					bool elseBranch = compute(k-1, end, var);

					if(!thenBranch && !elseBranch)
					{
						return false;
					}
					else
					{
						return true;
					}
				}
				else if(ast->getStatementType(i) == CALL)
				{
					if(modifies->isModifiesStmt(i, var))
						return false;
				}
			}
			else // Next* branch
			{
				i = next->getNext(i-1, false)[0]-1;
			}
		}
		else // Visited branch
		{
			int j = next->getNext(i-1, false)[0];
			int k = next->getNext(i-1, false)[1];
			if(k > j)
			{
				j = k;
			}
			i = j;
		}
	}
	return true;
}

//int main()
//{
//	Parser p;
//	DesignExtractor d;
//	PKB* pkb;
//
//	try
//	{
//		pkb = p.parse("Test.txt");
//		d.extract(pkb);
//	} catch (ParseException pe) {
//		cout << pe.what();
//		getchar();
//		return 0;
//	}
//
//	Affects a(pkb);
//
//	// Should return True
//	if(a.isAffects(1, 4))
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
//		cout << "Affects(4,12) = false" << endl;
//
//	// Should return False
//	if(a.isAffects(9, 11))
//		cout << "Affects(9,11) = true" << endl;
//	else
//		cout << "Affects(9,11) = false" << endl;
//
//	system("Pause");
//	return 0;
//}