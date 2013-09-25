#pragma once
#include <vector>
#include <list>

/*  List Manager is used to store the list of variable and their relationship


     Conceptual Design

	 List 1	 
	 a       b
	 =========
	 1   ->  c
	 2   -> d

	 List 2
	 c     d    e (vector<list<string>*>
	 ============
	 1  -> a -> 3 list<string>*
	 2 -> e -> 4
 */



using namespace std;

class ListManager {

public:
	ListManager();
	
	void updateList(string variableName, const vector<string> &listValue);
	void updateList(string variableName1, string variableName2, vector<string, string> &relationshipValue);
   
private:	
   void sortVariable(string variable);
   vector<vector<list<string>*>*> mainList;
   vector<vector<string>> variableList;	
};