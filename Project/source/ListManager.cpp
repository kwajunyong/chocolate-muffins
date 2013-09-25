#include "ListManager.h"
#include <algorithm>

ListManager::ListManager() {

}

void ListManager::updateList(string variableName1, string variableName2, vector<string, string> &relationshipValue) {
	
	string abc;
}


void ListManager::updateList(string variableName, const vector<string> &listValue) {
	// check if the varialbe exists

	vector<vector<string>>::iterator iterVariableContainer;
	vector<string>::iterator iterVariableList;

	bool found = false;
	int firstList = 0;
	int secondList = 0; 

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

	if (found) {
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

// delete list can be fine tuned / optimized if necessary. 

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
