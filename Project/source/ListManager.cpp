#include "ListManager.h"
#include <algorithm>

ListManager::ListManager() {

}

void ListManager::updateList(string variableName1, string variableName2, vector<pair<string, string>> &relationshipValue) {
	int varOneFirst, varOneSecond;
	int varTwoFirst, varTwoSecond;

	findVariable(variableName1, varOneFirst, varOneSecond);
	findVariable(variableName2, varTwoFirst, varTwoSecond);

	if (varOneFirst == -1 && varTwoFirst == -1) // both not found
		createANewList(variableName1, variableName2, relationshipValue);
	else if (varOneFirst == -1) { // varTwo is not empty
		sortVariable(mainList.at(varTwoFirst), varTwoSecond); // disaster waiting to happen because i will forget to sort. 
		appendVariable(mainList.at(varTwoFirst), variableList.at(varTwoFirst), 
			  varTwoSecond, variableName1, relationshipValue, false);

	} else if (varTwoFirst = -1) {// varOne is not empty
		sortVariable(mainList.at(varOneFirst), varOneSecond);
		appendVariable(mainList.at(varOneFirst), variableList.at(varOneFirst), 
			  varOneSecond, variableName2, relationshipValue, true);

	} else  if (varOneFirst == varTwoFirst) { // they both exists in the same list
		sortVariable(mainList.at(varOneFirst), varOneSecond);

		shortenList(mainList.at(varOneFirst), varOneSecond, varTwoSecond, relationshipValue);

	} else { // they both exist in dfferent list.
		// mergelist 
		// sort both
		sortVariable(mainList.at(varOneFirst), varOneSecond);
		// sort both
		sortVariable(mainList.at(varTwoFirst), varTwoSecond);


	}
}

// ASSUME Sorting the first variable. 
// uninformed deleting, hope it will work out on average *cross finger*. 
void mergeList(vector<list<string>*> * valueList1, vector<list<string>*> * valueList2, 
	   int index1, int index2, const vector<pair<string, string>> &relationshipValue) {
	   
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
	}
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
	copy(newList.begin(), newList.end(), valueList->begin());
}


// if the first is true, it means that first variable exists in the list, second variable nope. 

// ASSUME SORTED.

void ListManager::appendVariable(vector<list<string>*> * valueList, vector<string> &variable,  int index, 
	string newvariableName, const vector<pair<string, string>> &relationshipValue, bool first) {

		vector<list<string>*> newList;// temporary list;
		vector<list<string>*>::iterator iterFound;


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
					(*iterFound)->push_back(valuer);
					newList.push_back((*iterFound));
					iterFound++;
					if (iterFound == valueList->end()) 
						break;
					value = getValueAt((*iterFound), index);

					if (value.compare(looker) != 0)
						break;
				} while (true);
			}
		}

		valueList->clear();

		// copy from the temp list to the original list. Let's hope it's fast. 
		for (iterFound = newList.begin(); iterFound != newList.end(); iterFound++) {		
			valueList->push_back((*iterFound)); // complicated. 
		}

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
			for (iterVariableList = variableList.begin(); iterVariableList != variableList.begin(); 
				iterVariableList++) {
					secondList++;
					if (variableName.compare((*iterVariableList)) == 0) {
						found = true;
						break;
					}
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

void ListManager::updateList(string variableName, const vector<string> &listValue) {


	// check if the varialbe exists
	int firstList = 0;
	int secondList = 0; 

	findVariable(variableName, firstList, secondList);

	if (firstList != -1) {

		// check if listvalue is empty
		vector<list<string>*> *valueList = mainList.at(firstList);
		sortVariable(valueList, secondList);
		deleteList(valueList, listValue, true, secondList);

	} else {
		createANewList(variableName, listValue);
	}
}

void ListManager::createANewList(string variableName, const vector<string> &listValue) {

	list<string> * newVariableList = new list<string>(listValue.begin(), listValue.end());
	vector<list<string>*> *headerList = new vector<list<string>*>();

	headerList->push_back(newVariableList);
	mainList.push_back(headerList);

	vector<string> variable;
	variable.push_back(variableName);
	variableList.push_back(variable);
}

void ListManager::createANewList(string variableName1, string variableName2, 
	const vector<pair<string, string>> &relationshipValue) {

		list<string> * newVariableList1 = new list<string>();
		list<string> * newVariableList2 = new list<string>();

		vector<pair<string, string>>::const_iterator pairIterator;

		for (pairIterator = relationshipValue.begin(); pairIterator != relationshipValue.end(); pairIterator++) {
			newVariableList1->push_back(pairIterator->first);
			newVariableList2->push_back(pairIterator->second);
		}
		vector<list<string>*> *headerList = new vector<list<string>*>();

		headerList->push_back(newVariableList1);
		headerList->push_back(newVariableList2);
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

		valueList->clear();
		// copy from the temp list to the original list. Let's hope it's fast. 
		for (iterFound = newList.begin(); iterFound != newList.end(); iterFound++) {		
			valueList->push_back((*iterFound)); // complicated. 
		}
	}
}


vector<list<string>*>::iterator ListManager::bLookup(vector<list<string>*> *valueList, string value, int index) {

	vector<list<string>*>::iterator iter;

	for (iter = valueList->begin(); iter != valueList->end(); iter++) {
		if (getValueAt((*iter), index).compare(value) == 0) {
			return iter;
		}
	}
	return iter;
}



// quick quick sort variable 
void ListManager::sortVariable(vector<list<string>*> *valueList, int varIndex) {
	quickSort(valueList, varIndex, 0, valueList->size() - 1);

}

void ListManager::quickSort(vector<list<string>*> *valueList, int varIndex, int start, int end) {

	if (start >= end)
		return;

	int middle = (start + end) / 2;

	quickSort(valueList, varIndex, start, middle);
	quickSort(valueList, varIndex, middle + 1, end);

	merge(valueList, varIndex, start, middle, end);
}

void ListManager::merge(vector<list<string>*> *valueList, int varIndex, int start, int middle,  int end) {

	int i = start; 
	int j = middle + 1;
	string iValue;
	string jValue;
	vector<list<string>*> newList;// temporary list;
	iValue = getValueAt(valueList->at(i), varIndex);
	jValue = getValueAt(valueList->at(j), varIndex);

	while (i <= middle && j <= end) {			
		string variableType = "string";

		if (variableType.compare("string") == 0)  {
			if ((iValue.compare(jValue) <= 0 && i <= middle) || j > end) {
				newList.push_back(valueList->at(i));
				i++;
				iValue = getValueAt(valueList->at(i), varIndex);
			} else if (j <= end) {
				newList.push_back(valueList->at(j));
				j++;
				jValue = getValueAt(valueList->at(j), varIndex);
			}		
		} else { // integer type 			
			if ((atoi(iValue.c_str()) <= atoi(jValue.c_str()) && i <= middle) || j > end) {
				newList.push_back(valueList->at(i));
				i++;
				iValue = getValueAt(valueList->at(i), varIndex);
			} else if (j <= end) {
				newList.push_back(valueList->at(j));
				j++;
				jValue = getValueAt(valueList->at(j), varIndex);
			}		
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
