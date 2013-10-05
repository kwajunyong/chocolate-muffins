#include "ListManager.h"
#include <algorithm>
#include <iterator>
#include "QueryManager.h"
ListManager::ListManager(QueryManager *qm) {
	parent = qm;
}

int ListManager::compare(const string &value1, const string &value2, const string &variableType){

	if (variableType.compare("string") == 0) 
		return value1.compare(value2);
	else {
		
		int intValue1 = atoi(value1.c_str());
		int intValue2 = atoi(value2.c_str());
		if (intValue1 == intValue2)
			return 0;
		else if (intValue1 > intValue2) 
			return 1;
		else
			return -1;
	}



}
void ListManager::updateList(string variableName1, string variableName2, const vector<pair<string, string>> &relationshipValue) {
	int varOneFirst, varOneSecond;
	int varTwoFirst, varTwoSecond;

	findVariable(variableName1, varOneFirst, varOneSecond);
	findVariable(variableName2, varTwoFirst, varTwoSecond);

	if (varOneFirst == -1 && varTwoFirst == -1) // both not found
		createANewList(variableName1, variableName2, relationshipValue);
	else if (varOneFirst == -1) { // varTwo is not empty
		sortVariable(mainList.at(varTwoFirst), varTwoSecond, variableName2); // disaster waiting to happen because i will forget to sort. 
		appendVariable(mainList.at(varTwoFirst), variableList.at(varTwoFirst), 
			varTwoSecond, variableName1, relationshipValue, false);

	} else if (varTwoFirst == -1) {// varOne is not empty
		sortVariable(mainList.at(varOneFirst), varOneSecond, variableName1);
		appendVariable(mainList.at(varOneFirst), variableList.at(varOneFirst), 
			varOneSecond, variableName2, relationshipValue, true);

	} else  if (varOneFirst == varTwoFirst) { // they both exists in the same list
		sortVariable(mainList.at(varOneFirst), varOneSecond, variableName1);

		shortenList(mainList.at(varOneFirst), varOneSecond, varTwoSecond, relationshipValue);

	} else { // they both exist in dfferent list.
		// mergelist

		// sort both
		sortVariable(mainList.at(varOneFirst), varOneSecond, variableName1);
		// sort both
		sortVariable(mainList.at(varTwoFirst), varTwoSecond, variableName2);		
		mergeList(mainList.at(varOneFirst), mainList.at(varTwoFirst), varOneSecond, varTwoSecond, relationshipValue);

		// delete the second list;
		mainList.erase(mainList.begin() + varTwoFirst);

        // copy the variable to first list
		vector<string> &varList1 = variableList.at(varOneFirst);					
		vector<string> &varList2 = variableList.at(varTwoFirst);					
		copy (varList2.begin(), varList2.end(), std::back_inserter(varList1));
	    
		variableList.erase(variableList.begin() + varTwoFirst);		
	}
}

// ASSUME Sorting the first variable. 
// uninformed deleting, hope it will work out on average *cross finger*. 

// benchmark here
void ListManager::mergeList(vector<list<string>*> * valueList1, vector<list<string>*> * valueList2, 
	int index1, int index2, const vector<pair<string, string>> &relationshipValue) {

		vector<list<string>*> newList;// temporary list;
		vector<list<string>*>::iterator iterFoundList1, iterFoundList2;
		vector<list<string>*>::iterator iterList1, iterList2;
		vector<pair<string, string>>::const_iterator iterListValue;

		list<string>* variableTuple1;
		list<string>* variableTuple2;
		list<string>* tempList;

		list<string>::iterator iterVariable;

		string secondValue;
		string first;
		string second;
		string value;
		for (iterListValue = relationshipValue.begin(); 
			iterListValue != relationshipValue.end(); iterListValue++) {
				first= (*iterListValue).first;
				second = (*iterListValue).second;

				iterFoundList1 = bLookup(valueList1, first, index1);
				iterFoundList2 = bLookup(valueList2, second, index2);

				iterList1 = iterFoundList1;
				iterList2 = iterFoundList2;

				/* --------------------------------------- (Looks like neon light)
				   valueList1                     valueList2
				   ==========                     ==========
				   a     b                        c      d
				   x  ->  1                       1   -> 8 
				   y  ->  1                       1 - > 9
				   z ->   1                       3 -> 10
				   a -> 2						  4 -> 11 	
				   b -> 2                           
				   c -> 2

				   if merging between b and c. Let's say relation contains (1,1), (2,3)
				   We will find b using blookup and c using blookup (assume sorted)
				   for value in b (using while(true) 
				      for value in c (using while(true)
					     do join 
				------------------------------------------*/ 
				// if found both
				if (iterFoundList1 != valueList1->end() &&
					iterFoundList2 != valueList2->end()) {


						while (true) {						   
							
							while (true) {
								if (iterList2 == valueList2->end() || 
									   getValueAt(*iterList2, index2).compare(second) !=0)
									   break; 

								variableTuple1 = *iterList1;
								variableTuple2 = *iterList2;					   
								// copy from variableTuple1
							
								tempList = new list<string>(*variableTuple1);					   
								// copy from variableTuple2
								tempList->insert(tempList->end(), variableTuple2->begin(), variableTuple2->end());	
								newList.push_back(tempList);
								iterList2++;
							}

							iterList2 = iterFoundList2;
							iterList1++;
							
							if (iterList1 == valueList1->end() || getValueAt(*iterList1, index1).compare(first) != 0) 
								break;
						}
				}
		}
		// remember when after clear must delete the list properly. 


		// new list 1
		clearVariableList(*valueList1);

		valueList1->assign(newList.begin(), newList.end());

		//copy(newList.begin(), newList.end(), valueList1->begin());

		
}


void ListManager::shortenList(vector<list<string>*> * valueList, int index1, int index2, 
	const vector<pair<string, string>> &relationshipValue) {

		vector<list<string>*> newList;// temporary list;
		vector<list<string>*>::iterator iterFound;
		vector<pair<string, string>>::const_iterator iterListValue;
		string secondValue;
		string first;
		string second;
		string value;
		for (iterListValue = relationshipValue.begin(); 
			iterListValue != relationshipValue.end(); iterListValue++) {
				first= (*iterListValue).first;
				second = (*iterListValue).second;
				iterFound = bLookup(valueList, first, index1);


				if (iterFound != valueList->end()) {
					do {
						secondValue = getValueAt(*iterFound,index2);

						if (secondValue.compare(second))					     
							newList.push_back((*iterFound));

						iterFound++;
						if (iterFound == valueList->end()) 
							break;

						value = getValueAt((*iterFound), index1);

						if (value.compare(first) != 0)
							break;
					} while (true);
				}
		}
		valueList->clear();
		copy(newList.begin(), newList.end(), valueList->begin());
}


// if the first is true, it means that first variable exists in the list, second variable nope. 

// ASSUME SORTED.

void ListManager::appendVariable(vector<list<string>*> * valueList, vector<string> &variable,  int index, 
	string newvariableName, const vector<pair<string, string>> &relationshipValue, bool first) {

		vector<list<string>*> newTupleList;// temporary list;
		vector<list<string>*>::iterator iterFound;
		list<string>* newList;

		vector<pair<string, string>>::const_iterator iterListValue;

		string looker;
		string valuer;

		string value;
		for (iterListValue = relationshipValue.begin(); iterListValue != relationshipValue.end(); iterListValue++) {

			if (first) {
				looker = (*iterListValue).first;
				valuer = (*iterListValue).second;
			} else {
				looker = (*iterListValue).second;
				valuer = (*iterListValue).first;
			}
			iterFound = bLookup(valueList, looker, index);

			if (iterFound != valueList->end()) {
				do {
					newList = new list<string>(**iterFound);
					newList->push_back(valuer);
					newTupleList.push_back(newList);
					
					iterFound++;
					if (iterFound == valueList->end()) 
						break;

					value = getValueAt((*iterFound), index);

					if (value.compare(looker) != 0)
						break;
				} while (true);
			}
		}

		clearVariableList(*valueList);
		valueList->assign(newTupleList.begin(), newTupleList.end());

		variable.push_back(newvariableName);
}


void ListManager::findVariable(const string &variableName, int &first, int &second){ // find respective list index

	int firstList = 0;
	int secondList = 0 ;


	vector<vector<string>>::iterator iterVariableContainer;
	vector<string>::iterator iterVariableList;

	bool found = false;
	// find variable
	for (iterVariableContainer= variableList.begin(); iterVariableContainer != variableList.end();  
		iterVariableContainer++) {

			vector<string> &variableList  = *iterVariableContainer;
			secondList = 0;		
			for (iterVariableList = variableList.begin(); iterVariableList != variableList.end(); 
				iterVariableList++) {
					if (variableName.compare((*iterVariableList)) == 0) {
						found = true;
						break;
					}
					secondList++;

			}

			if (found) {
				break;
			}
			firstList++;
	}

	if (found)  {
		first=  firstList;
		second = secondList;
	} else {
		first = -1;
		second = -1;
	}


}

void ListManager::clearVariableList(vector<list<string>*> &varList) {
	vector<list<string>*>::iterator iterVarList;

	for (iterVarList = varList.begin(); iterVarList != varList.end(); iterVarList++) {
	    free(*iterVarList);
	}

	varList.clear();
}

void ListManager::updateList(string variableName, const vector<string> &listValue) {


	// check if the varialbe exists
	int firstList = 0;
	int secondList = 0; 

	findVariable(variableName, firstList, secondList);

	if (firstList != -1) {

		// check if listvalue is empty
		vector<list<string>*> *valueList = mainList.at(firstList);
		sortVariable(valueList, secondList, variableName);
		deleteList(valueList, listValue, true, secondList);

	} else {
		createANewList(variableName, listValue);
	}
}

void ListManager::createANewList(string variableName, const vector<string> &listValue) {

	vector<string>::const_iterator  iterListValue;
	list<string> * newVariableList ;
	vector<list<string>*> *headerList = new vector<list<string>*>();

	for (iterListValue = listValue.begin(); iterListValue != listValue.end(); iterListValue++) {
		newVariableList = new list<string>;
		newVariableList->push_back(*iterListValue);		
		headerList->push_back(newVariableList);
	}
	

	mainList.push_back(headerList);

	vector<string> variable;
	variable.push_back(variableName);
	variableList.push_back(variable);
}

void ListManager::createANewList(const string &variableName1, const string &variableName2, 
	const vector<pair<string, string>> &relationshipValue) {

		list<string> * newVariableList;
		vector<list<string>*> *headerList = new vector<list<string>*>();
		vector<pair<string, string>>::const_iterator pairIterator;

		for (pairIterator = relationshipValue.begin(); pairIterator != relationshipValue.end(); pairIterator++) {
			newVariableList =  new list<string>();
			newVariableList->push_back(pairIterator->first);
			newVariableList->push_back(pairIterator->second);
			headerList->push_back(newVariableList);
		}
				
		mainList.push_back(headerList);

		vector<string> variable;

		variable.push_back(variableName1);
		variable.push_back(variableName2);
		variableList.push_back(variable);
}

// delete list can be fine tuned / optimized if necessary. 
// DELETE LIST ASSUME THE VARIABLE IS SORTED!!!!

void ListManager::deleteList(vector<list<string>*>* valueList, const vector<string> &listValue, bool keepList, int index ) {
	vector<list<string>*> newList;// temporary list;
	vector<list<string>*>::iterator iterFound;
	string value;
	if (keepList) { // the list value contains the value we want to keep. 
		vector<string>::const_iterator iterListValue;

		for (iterListValue = listValue.begin(); iterListValue != listValue.end(); iterListValue++) {
			iterFound = bLookup(valueList, (*iterListValue), index);

			if (iterFound != valueList->end()) {
				do {
					newList.push_back((*iterFound));
					iterFound++;

					if (iterFound == valueList->end()) 
						break;

					value = getValueAt((*iterFound), index);

					if (value.compare(*iterListValue) != 0)
						break;

				} while (true);
			}
		}

		clearVariableList(*valueList);
		// copy from the temp list to the original list. Let's hope it's fast. 
			valueList->assign(newList.begin(), newList.end()); 
	}
}


vector<list<string>*>::iterator ListManager::bLookup(vector<list<string>*> *valueList, string value, int index) {

	vector<list<string>*>::iterator iter;
	// this is not binary lookup. 
	// must ensure binary lookup find the first element. 
	for (iter = valueList->begin(); iter != valueList->end(); iter++) {
		if (getValueAt((*iter), index).compare(value) == 0) {
			return iter;
		}
	}
	return iter;
}



// quick quick sort variable 
void ListManager::sortVariable( vector<list<string>*> *valueList, int varIndex, const string &variableName) {
	

	string variableType = parent->getVariableType(variableName);
	mergeSort(valueList, varIndex, 0, valueList->size() - 1, variableType);

}

void ListManager::mergeSort(vector<list<string>*> *valueList, int varIndex, int start, int end, const string &variableType) {

	if (start >= end)
		return;

	int middle = (start + end) / 2;

	mergeSort(valueList, varIndex, start, middle, variableType);
	mergeSort(valueList, varIndex, middle + 1, end, variableType);

	merge(valueList, varIndex, start, middle, end, variableType);
}

void ListManager::merge(vector<list<string>*> *valueList, int varIndex, int start, int middle,  int end, const string &variableType) {

	int i = start; 
	int j = middle + 1;
	string iValue;
	string jValue;
	vector<list<string>*> newList;// temporary list;
	iValue = getValueAt(valueList->at(i), varIndex);
	jValue = getValueAt(valueList->at(j), varIndex);


	while (i <= middle || j <= end) {			

		
			if ((compare(iValue, jValue, variableType) <= 0 && i <= middle) || j > end) {
				newList.push_back(valueList->at(i));
				i++;
				if (i <= middle) 
					iValue = getValueAt(valueList->at(i), varIndex);
			} else if (j <= end) {
				newList.push_back(valueList->at(j));
				j++;
				if (j <= end)
					jValue = getValueAt(valueList->at(j), varIndex);
			}		
		
	} // finish while 

	// putting the list into the main list
	j = 0;
	vector<list<string>*>::iterator iter;
	for (i = start; i  <= end; i++) {		
		iter = valueList->erase(valueList->begin() + i);
		valueList->insert(iter, newList.at(j));		
		j++;
	}
}

const string &ListManager::getValueAt(list<string>* valueList, int index) {
	list<string>::iterator iter = valueList->begin();
	std::advance(iter, index);

	return (*iter);
}
