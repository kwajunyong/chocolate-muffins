#include "ListManager.h"
#include <algorithm>
#include <iterator>
#include "QueryManager.h"
ListManager::ListManager(QueryManager *qm) {
	parent = qm;
}

void ListManager::prepareResultList(list<string> &payloadList, vector<string> &variableResultList) {

	// okay, the idea is this
	// first we have to hunt down the position of the ListManager's mainList
	// store that position and used that position to populate the row 
	// in each group
	// let's say <a, b, c, d, e> a<1, 3> means that a is found at list 1st and 3rdElement
	// minus -1 is means that particular variable is not used at the 
	// executtion at all

	// afat that we have to prepare the result a, b, c, d, e;
	// however the result group list may not be in sequence a and b might  be different result
	// hence requires cartersian product. 
	// The cartesian product is another headache a,b,c,d,e may reflect grouping such as
	// <1,2,1,2,3> hence we have to insert position according to the location
	// positionMap is the map to map the resultGroupList to it's position
	// 1,1 -> 1, 2-1 -> 2, 1-2 -> 3

	
	map<int, vector<int>> variableGroup;
	map<int, vector<bool>> variableGroupProcName;

	
	vector<string>::iterator iterVar;

	map<int, vector<int>>::iterator iterMap;
	map<int, vector<bool>>::iterator iterMapProcName;
	vector<string> leftOver;
	vector<int> foundPos;


	int first, second; 

	// find the location to pick up the good
	// load the position where it finds; 

	vector<int> leftOverPos;
	vector<bool> leftOverProcName;
	
	bool procName = false;
	for (iterVar = variableResultList.begin(); iterVar != variableResultList.end(); iterVar++) {
		procName = false;
		string var = *iterVar;

		std::size_t loc = var.find(".");

		if (loc != string::npos) {
			var = var.substr(0, loc); // to include the dot. 
			procName = true;
		} // found

		
		findVariable(var, first, second);

		if (first == -1)  {			
			// handle call procName for call 

			
			leftOver.push_back(var);

			foundPos.push_back(-1);
			// store the position in tuple result list
			leftOverPos.push_back(distance(variableResultList.begin(), iterVar));			 

			// new addition - to handle procName
			leftOverProcName.push_back(procName);

			continue;
		} else {
			foundPos.push_back(first);
		}

		iterMap = variableGroup.find(first);
		if (iterMap != variableGroup.end()) {
			iterMap->second.push_back(second);
			iterMapProcName = variableGroupProcName.find(first);
			iterMapProcName->second.push_back(procName);
			
		} else {

			vector<int> newVector;
			newVector.push_back(second);
			variableGroup[first] = newVector;

			vector<bool> newVectorProcName;
			newVectorProcName.push_back(procName);
			variableGroupProcName[first] = newVectorProcName;

		}	
	}

	vector<int>::iterator iterPos;
	

	map<pair<int, int>, int> positionMap; 
	// position map 
	// -> pair (

	map<int, vector<int>>::iterator iterFound;
	map<int, int> recordMap;
	map<int, int>::iterator iterRecordMap;
	int foundPosition;
	// recordMap is a map to keep track the numbering 

	// load the position of the one that's found in the list manager
	// found pos to to check the 
	// let's say 
	// <a, b> => a is stored in list 2 , b in stored in list 1 then b's position is at 0, a's position is at 1. 
	// NOTE ------------------------
	// recordMap is the helping counter
	for (iterPos = foundPos.begin(); iterPos != foundPos.end(); iterPos++) {
		if (*iterPos != -1) {
			iterFound = variableGroup.find(*iterPos);
			foundPosition = distance(variableGroup.begin(), iterFound);
			iterRecordMap = recordMap.find(foundPosition);
			if (iterRecordMap == recordMap.end()) {
				pair<int, int> p(foundPosition, 0);
				positionMap[p] = distance(foundPos.begin(), iterPos);
				recordMap[foundPosition] = 0;
			} else {
				iterRecordMap->second =iterRecordMap->second + 1;
				pair<int, int> p(foundPosition, iterRecordMap->second);
				positionMap[p] = distance(foundPos.begin(), iterPos);
			}			
		}
	}


	// pickup the good 
	vector<map<string, bool>> resultGroupList;
	//map<int, map<string, bool>>::iterator iterResult;
	vector<int>::iterator iterVarIndex;
	map<string, bool> *tempMap;

	vector<list<string>*>* tempResultList;
	vector<list<string>*>::iterator iterTempResultList;

	list<string>::iterator iterLastList;
	
	int indexMapSecond;
	for (iterMap = variableGroup.begin(); iterMap != variableGroup.end(); iterMap++) {
		map<string, bool> newMap;
		resultGroupList.push_back(newMap);
		tempMap = &resultGroupList.back();


		// get from the variable
		iterMapProcName = variableGroupProcName.find(iterMap->first);
		tempResultList = mainList.at(iterMap->first);
		for (iterTempResultList = tempResultList->begin(); iterTempResultList != tempResultList->end(); iterTempResultList++) {
			string temp;
			indexMapSecond = 0;
			for (iterVarIndex = iterMap->second.begin(); iterVarIndex!= iterMap->second.end(); iterVarIndex++) {
				
				iterLastList = (*iterTempResultList)->begin();
				advance(iterLastList, *iterVarIndex); // go to that location based

				if (iterMapProcName->second.at(indexMapSecond)) { // if it's a call 
					temp.append(parent->getProcNameUsingCall(atoi(iterLastList->c_str())));
				} else {
					temp.append(*iterLastList);
				}
				
				temp.push_back(' ');
				indexMapSecond++;
			}

			if (temp.size() >0) 
				temp.pop_back();
			tempMap->insert(pair<string, bool>(temp, true));
		}

		// for procName 
	}

	vector<string>::iterator iterLeftOver; 
	map<string, bool> tempResultMap;
	int lastOfMap = resultGroupList.size() - 1;
	// left over always standalone 

	for (iterLeftOver = leftOver.begin(); iterLeftOver != leftOver.end(); iterLeftOver++) {
		lastOfMap++;

		pair<int, int> p(lastOfMap, 0);
		int index = distance(leftOver.begin(), iterLeftOver);
		positionMap[p] = leftOverPos.at(index);

		// must be call
		if (leftOverProcName.at(index)) { /// new Addition
			FastSearchInteger callMap = parent->getValueListIntegerMap(*iterLeftOver);
			FastSearchInteger::iterator iterCall; 

			FastSearchInteger callProc;

			FastSearchString allProcName;
			for (iterCall = callMap.begin(); iterCall != callMap.end(); iterCall++) 
				allProcName[parent->getProcNameUsingCall(iterCall->first)] = true;
			
			resultGroupList.push_back(allProcName);

		} else { /// -------------------------------------------new Addition
			
			if (parent->getVariableType(*iterLeftOver).compare("string") == 0)  {
				resultGroupList.push_back( parent->getValueListMap(*iterLeftOver));
			} else {
				tempResultMap.clear();
				CommonUtility::convertIntMapToStringMap(parent->getValueListIntegerMap(*iterLeftOver), tempResultMap);
				resultGroupList.push_back(tempResultMap);
			}			
		}
	}


	// package done
	vector<string> initialString;

	recursivePrepare(resultGroupList, 0, positionMap, initialString, payloadList);


}

void ListManager::recursivePrepare(vector<map<string, bool>> &resultGroupList, int index, 
	map<pair<int, int>, int> &positionList, vector<string> stringList, list<string> &resultList) {
		map<string, bool> &tempList = resultGroupList.at(index);
		map<string, bool>::iterator iterMap;
		vector<string>::iterator iterString;
		int curr = 0;
		int pos = 0; 
		for (iterMap = tempList.begin(); iterMap != tempList.end(); iterMap++) {
			// getPosition; 
			vector<string> splitList;
			CommonUtility::split(iterMap->first, ' ', splitList);
			curr = 0;
			vector<string> newList = stringList;
			for (iterString = splitList.begin(); iterString != splitList.end(); iterString++) {
				pair<int, int> p (index, curr); 
				pos = positionList.find(p)->second;
				if (newList.size() <= pos) 
					newList.push_back(*iterString);
				else
					newList.insert(newList.begin() + pos, *iterString);
				curr++;
			}

			if (index < resultGroupList.size() - 1) {

				recursivePrepare(resultGroupList, index + 1, 
					positionList, newList, resultList);

			} else {
				string temp;
				for (iterString = newList.begin(); iterString != newList.end(); iterString++)  {
					temp.append(*iterString);
					temp.push_back(' ');
				}

				if (temp.size() >0) 
					temp.pop_back();
				resultList.push_back(temp);				
			}
		}
}



void ListManager::clear() {


	vector<vector<list<string>*>*>::iterator mainListIter;
	vector<list<string>*>::iterator mainListVectorIter;
	for (mainListIter = mainList.begin(); mainListIter != mainList.end(); mainListIter++) {

		for (mainListVectorIter = (*mainListIter)->begin(); mainListVectorIter != (*mainListIter)->end(); mainListVectorIter++) {
			delete (*mainListVectorIter);
		}

		delete (*mainListIter);
	}
	mainList.clear();

	variableList.clear();

}

void ListManager::getValueListMapInteger(string &variableName, FastSearchInteger &tempResult) {

	int firstList, secondList;
	findVariable(variableName, firstList, secondList);

	if (firstList != -1) {
		vector<list<string>*>* valueList = mainList.at(firstList);

		vector<list<string>*>::iterator iterList;

		for (iterList = valueList->begin(); iterList != valueList->end(); iterList++) {
			tempResult[atoi(getValueAt(*iterList, secondList).c_str())] = true;
		}

	}

}
void ListManager::getValueListMapString(string &variableName, FastSearchString &tempResult) {

	int firstList, secondList;
	findVariable(variableName, firstList, secondList);

	if (firstList != -1) {
		vector<list<string>*>* valueList = mainList.at(firstList);
		vector<list<string>*>::iterator iterList;
		for (iterList = valueList->begin(); iterList != valueList->end(); iterList++) {
			tempResult[getValueAt(*iterList, secondList)] = true;
		}
	}
}

vector<int> ListManager::getValueListInteger(string &variableName) {
	FastSearchInteger tempResult;
	getValueListMapInteger(variableName,tempResult);
	vector<int> resultList;

	CommonUtility::convertVector(tempResult, resultList);

	return resultList;
}

vector<string> ListManager::getValueListString(string &variableName) {
	FastSearchString tempResult;

	getValueListMapString(variableName, tempResult);

	vector<string> resultList;
	CommonUtility::convertVector(tempResult, resultList);
	return resultList;
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
void ListManager::updateList(string variableName1, string variableName2,  vector<pair<string, string>> &relationshipValue) {
	int varOneFirst, varOneSecond;
	int varTwoFirst, varTwoSecond;

	findVariable(variableName1, varOneFirst, varOneSecond);
	findVariable(variableName2, varTwoFirst, varTwoSecond);

	if (varOneFirst == -1 && varTwoFirst == -1) // both not found
		createANewList(variableName1, variableName2, relationshipValue);
	else if (varOneFirst == -1) { // varTwo is not empty
		sortRelation(relationshipValue, false, variableName2); // disaster waiting to happen because i will forget to sort. 
		appendVariable(mainList.at(varTwoFirst), variableList.at(varTwoFirst), 
			varTwoSecond, variableName1, relationshipValue, false);

	} else if (varTwoFirst == -1) {// varOne is not empty
		sortRelation(relationshipValue, true, variableName1); // disaster waiting to happen because i will forget to sort. 
		appendVariable(mainList.at(varOneFirst), variableList.at(varOneFirst), 
			varOneSecond, variableName2, relationshipValue, true);

	} else  if (varOneFirst == varTwoFirst) { // they both exists in the same list
		//sortVariable(mainList.at(varOneFirst), varOneSecond, variableName1);

		shortenList(mainList.at(varOneFirst), varOneSecond, varTwoSecond, relationshipValue, variableName1);

	} else { // they both exist in dfferent list.
		// mergelist

		// sort both
		sortVariable(mainList.at(varOneFirst), varOneSecond, variableName1);
		// sort both
		sortVariable(mainList.at(varTwoFirst), varTwoSecond, variableName2);		
		mergeList(mainList.at(varOneFirst), mainList.at(varTwoFirst), varOneSecond, varTwoSecond, relationshipValue, variableName1, variableName2);

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
	int index1, int index2, const vector<pair<string, string>> &relationshipValue, const string  &variableOne, const string &variableTwo) {

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

				iterFoundList1 = bLookup(valueList1, first, index1,variableOne);
				iterFoundList2 = bLookup(valueList2, second, index2,variableTwo);

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
	const vector<pair<string, string>> &relationshipValue, const string &variableOne) {

		vector<list<string>*> newList;// temporary list;
		vector<list<string>*>::iterator iter;
		vector<pair<string, string>>::const_iterator iterRelationValue;
		string secondValue;
		string firstValue;

		FastSearchString newRelationship;

		// for each relationship value 
		// convert to first + "()" + second;
		string symbol = "()";
		for (iterRelationValue = relationshipValue.begin(); 
			iterRelationValue != relationshipValue.end(); iterRelationValue++) {
				string key = iterRelationValue->first + symbol + iterRelationValue->second;
				newRelationship[key] = true;
		}

		for (iter = valueList->begin(); iter != valueList->end(); ) {
			firstValue = getValueAt(*iter, index1);
			secondValue = getValueAt(*iter, index2);
			string key = firstValue + symbol + secondValue;

			if (newRelationship.find(key) == newRelationship.end()) { // check if the key is qualified				
				delete (*iter);
				iter =valueList->erase(iter);							
			} else {
				iter++;
			}
		}

	
}


// if the first is true, it means that first variable exists in the list, second variable nope. 

// ASSUME SORTED.

void ListManager::appendVariable(vector<list<string>*> * valueList, vector<string> &variable,  int index, 
	string newvariableName,  vector<pair<string, string>>  &relationshipValue, bool first) {

		vector<list<string>*> newTupleList;// temporary list;
		vector<pair<string, string>>::iterator iterFound;
		list<string>* newList;

		vector<list<string>*>::const_iterator iterListValue;


		string value;


		string variableName = variable.at(index);
		for (iterListValue = valueList->begin(); iterListValue != valueList->end(); iterListValue++) {

			const string &looker = getValueAt(*iterListValue, index);

			iterFound = bRelationLookup(relationshipValue, looker, first, variableName);

			if (iterFound != relationshipValue.end()) {
				do {
					newList = new list<string>(**iterListValue);

					if (first) 
						newList->push_back(iterFound->second);						
					else
						newList->push_back(iterFound->first);

					newTupleList.push_back(newList);

					iterFound++;
					if (iterFound == relationshipValue.end()) 
						break;

					if (first)
						value = iterFound->first;
					else
						value = iterFound->second;

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

void ListManager::updateList(string variableName, const FastSearchString &listValue) {


	// check if the varialbe exists
	int firstList = 0;
	int secondList = 0; 

	findVariable(variableName, firstList, secondList);

	if (firstList != -1) {

		// check if listvalue is empty
		vector<list<string>*> *valueList = mainList.at(firstList);
		//sortVariable(valueList, secondList, variableName);
		deleteList(valueList, listValue, true, secondList);

	} else {
		createANewList(variableName, listValue);
	}
}

void ListManager::createANewList(string variableName, const FastSearchString &listValue) {

	FastSearchString::const_iterator  iterListValue;
	list<string> * newVariableList ;
	vector<list<string>*> *headerList = new vector<list<string>*>();

	for (iterListValue = listValue.begin(); iterListValue != listValue.end(); iterListValue++) {
		newVariableList = new list<string>;
		newVariableList->push_back(iterListValue->first);		
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

void ListManager::deleteList(vector<list<string>*>* valueList, const FastSearchString &listValue, bool keepList, int index ) {

	vector<list<string>*> newList;// temporary list;
	vector<list<string>*>::iterator iter;
	FastSearchString::const_iterator iterFound;
	string value;

	if (keepList) { // the list value contains the value we want to keep. 
		vector<string>::const_iterator iterListValue;
		iter = valueList->begin();
		while(iter != valueList->end()) {
			string value = getValueAt((*iter), index);

			iterFound = listValue.find(value);

			if (iterFound == listValue.end()) {

				delete (*iter);
				iter =valueList->erase(iter);							
			} else 
				iter++;

		}


	}
}


vector<list<string>*>::iterator ListManager::bLookup(vector<list<string>*> *valueList, string value, int index, const string &variableName) {

	vector<list<string>*>::iterator iter;
	vector<list<string>*>::iterator iterPrevious;

	
	int min = 0;
	int max = valueList->size() -1;
	int curr = (max + min) / 2;


	string variableType = parent->getVariableType(variableName);
	int compareResult ; 
	while (max >= min) {
		iter = valueList->begin() + curr;

		compareResult = compare(getValueAt((*iter), index), value, variableType);
		if (compareResult == 0) {

			if (iter == valueList->begin())
				return iter;

			iterPrevious = iter;
			iterPrevious--;
			while (true) {
				compareResult = compare(getValueAt((*iterPrevious), index), value, variableType);
				if (compareResult != 0)
					return iter;
				else {
					if (iterPrevious == valueList->begin())
						return iterPrevious;
					iter = iterPrevious;
					iterPrevious--;
				}
			}
		} else if (compareResult > 0) {
			max = curr - 1;
		} else {
			min = curr + 1; 
		}
		curr = (max+ min) /2; 

	}

	return valueList->end();
}



// quick quick sort variable 
void ListManager::sortVariable( vector<list<string>*> *valueList, int varIndex, const string &variableName) {


	string variableType = parent->getVariableType(variableName);
	mergeSort(valueList, varIndex, 0, valueList->size() - 1, variableType);

}

void ListManager::sortRelation(vector<pair<string, string>> &toSort, const bool &firstItem, const string &variableName) {


	string variableType = parent->getVariableType(variableName);
	mergeRelationSort(toSort, firstItem, 0, toSort.size() - 1, variableType);

}
void ListManager::mergeRelationSort(vector<pair<string, string>> &valueList, const bool &firstItem, int start, int end, const string &variableType) {


	if (start >= end)
		return;

	int middle = (start + end) / 2;

	mergeRelationSort(valueList, firstItem, start, middle , variableType);
	mergeRelationSort(valueList, firstItem, middle + 1, end, variableType);

	mergeRelation(valueList, firstItem, start, middle, end, variableType);
}

void ListManager::mergeRelation(vector<pair<string, string>> &valueList, const bool &firstItem, const int &start, const int &middle,  const int &end, const string &variableType) {
	int i = start; 
	int j = middle + 1;
	string iValue;
	string jValue;
	vector<pair<string, string>> newList;// temporary list;

	if (firstItem) {
		iValue = valueList.at(i).first;
		jValue = valueList.at(j).first;
	} else {
		iValue = valueList.at(i).second;
		jValue = valueList.at(j).second;
	}

	while (i <= middle || j <= end) {			


		if (i <= middle && (compare(iValue, jValue, variableType) <= 0 ) || j > end) {
			newList.push_back(valueList.at(i));
			i++;
			if (i <= middle) 
				if (firstItem)
					iValue = valueList.at(i).first;
				else
					iValue = valueList.at(i).second;

		} else if (j <= end) {
			newList.push_back(valueList.at(j));
			j++;
			if (j <= end)
				if (firstItem)
					jValue = valueList.at(j).first;
				else
					jValue = valueList.at(j).second;
		}		

	} // finish while 

	// putting the list into the main list
	vector<pair<string, string>>::iterator iter;
	valueList.erase(valueList.begin() + start, valueList.begin() + end +1);
	iter = valueList.begin() + start;
	valueList.insert(iter, newList.begin(), newList.end());		

}


vector<pair<string, string>>::iterator ListManager::bRelationLookup(vector<pair<string, string>> &valueList, string value, bool first, const string &variableName) {

	vector<pair<string, string>>::iterator iter;
	vector<pair<string, string>>::iterator iterPrevious;

	// this is not binary lookup. 
	// must ensure binary lookup find the first element. 
	int min = 0;
	int max = valueList.size() -1;
	int curr = (max + min) / 2;


	string variableType = parent->getVariableType(variableName);
	int compareResult ; 
	while (max >= min) {
		iter = valueList.begin() + curr;

		if (first)
			compareResult = compare(iter->first, value, variableType);
		else
			compareResult = compare(iter->second, value, variableType);

		if (compareResult == 0) {

			if (iter == valueList.begin())
				return iter;



			iterPrevious = iter;
			iterPrevious--;
			while (true) {
				if (first)
					compareResult = compare(iterPrevious->first, value, variableType);
				else
					compareResult = compare(iterPrevious->second, value, variableType);
				if (compareResult != 0)
					return iter;
				else {
					if (iterPrevious == valueList.begin())
						return iterPrevious;
					iter = iterPrevious;
					iterPrevious--;
				}
			}
		} else if (compareResult > 0) {
			max = curr - 1;
		} else {
			min = curr + 1; 
		}
		curr = (max+ min) /2; 

	}

	return valueList.end();
}


void ListManager::mergeSort(vector<list<string>*> *valueList, int varIndex, int start, int end, const string &variableType) {

	if (start >= end)
		return;

	int middle = (start + end) / 2;

	mergeSort(valueList, varIndex, start, middle , variableType);
	mergeSort(valueList, varIndex, middle + 1, end, variableType);

	merge(valueList, varIndex, start, middle, end, variableType);
}

void ListManager::merge(vector<list<string>*> *valueList, const int &varIndex, const int &start, const int &middle,  const int &end, const string &variableType) {

	int i = start; 
	int j = middle + 1;
	string iValue;
	string jValue;
	vector<list<string>*> newList;// temporary list;
	iValue = getValueAt(valueList->at(i), varIndex);
	jValue = getValueAt(valueList->at(j), varIndex);


	while (i <= middle || j <= end) {			


		if (i <= middle && (compare(iValue, jValue, variableType) <= 0 ) || j > end) {
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
	vector<list<string>*>::iterator iter;
	valueList->erase(valueList->begin() + start, valueList->begin() + end +1);
	iter = valueList->begin() + start;
	valueList->insert(iter, newList.begin(), newList.end());		

}

const string &ListManager::getValueAt(list<string>* valueList, int index) {
	list<string>::iterator iter = valueList->begin();
	std::advance(iter, index);

	return (*iter);
}
