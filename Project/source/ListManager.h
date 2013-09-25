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
   const string &getValueAt(list<string>* valueList, int index);

   void sortVariable(string variable);
   void sortVariable(vector<list<string>*>* valueList, int varIndex); // given a list sort which particular variable;

   void quickSort(vector<list<string>*>* valueList, int varIndex, int start, int end); 
   void merge(vector<list<string>*> *valueList, int varIndex, int start, int middle,  int end);

   vector<vector<list<string>*>*> mainList;
   vector<vector<string>> variableList;	
   void deleteList(vector<list<string>*> * valueList, const vector<string> &listValue, bool keepList, int index);
   

   vector<list<string>*>::iterator bLookup(vector<list<string>*> * valueList, string value, int index);

   void createANewList(string variableName, const vector<string> &listValue);
};