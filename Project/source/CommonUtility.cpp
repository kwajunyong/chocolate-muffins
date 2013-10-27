#include "CommonUtility.h"

using namespace std;

  string CommonUtility::NumberToString ( int Number )
  {
     ostringstream ss;
     ss << Number;
     return ss.str();
  }

  void CommonUtility::convertToMap(const vector<int>& resultList, map<int, int> &mapList) {
	 vector<int>::const_iterator vectorIterator;
	

	for (vectorIterator = resultList.begin(); vectorIterator != resultList.end(); vectorIterator++) {
		mapList[*vectorIterator] = 1;
	}
  }

  void CommonUtility::convertToMap(const vector<int>& resultList, map<int, bool> &mapList) {
	 vector<int>::const_iterator vectorIterator;
	

	for (vectorIterator = resultList.begin(); vectorIterator != resultList.end(); vectorIterator++) {
		mapList[*vectorIterator] = 1;
	}
  }

  void CommonUtility::convertToMap(const vector<string>& resultList, map<string, bool> &mapList) {
	 vector<string>::const_iterator vectorIterator;
	
	for (vectorIterator = resultList.begin(); vectorIterator != resultList.end(); vectorIterator++) {
		mapList[*vectorIterator] = 1;
	}
  }

  
  void CommonUtility::convertVector(const map<string, int> & mapList, vector<string>& resultList ) {
	map<string, int>::const_iterator mapIterator;
	
	for (mapIterator = mapList.begin(); mapIterator != mapList.end(); mapIterator++) {
		resultList.push_back(mapIterator->first);
	}
}

  void CommonUtility::convertVector(const map<string, bool> & mapList, vector<string>& resultList ) {
	map<string, bool>::const_iterator mapIterator;
	
	for (mapIterator = mapList.begin(); mapIterator != mapList.end(); mapIterator++) {
		resultList.push_back(mapIterator->first);
	}
}
void CommonUtility::convertVector(const map<int, int> & mapList, vector<int>& resultList ) {
	map<int, int>::const_iterator mapIterator;
	
	for (mapIterator = mapList.begin(); mapIterator != mapList.end(); mapIterator++) {
		resultList.push_back(mapIterator->first);
	}
}


void CommonUtility::convertVector(const map<int, int> & mapList, vector<string>& resultList ) {
	map<int, int>::const_iterator mapIterator;
	
	for (mapIterator = mapList.begin(); mapIterator != mapList.end(); mapIterator++) {
		resultList.push_back(NumberToString(mapIterator->first));
	}
}

void CommonUtility::convertVector(const map<int, bool> & mapList, vector<int>& resultList ) {
	map<int, bool>::const_iterator mapIterator;
	
	for (mapIterator = mapList.begin(); mapIterator != mapList.end(); mapIterator++) {
		resultList.push_back(mapIterator->first);
	}
}

void CommonUtility::convertIntVectorToString(const vector<int>& from, vector<string>& resultList) {

	vector<int>::const_iterator mapIterator;
	
	for (mapIterator = from.begin(); mapIterator != from.end(); mapIterator++) {
		resultList.push_back(NumberToString(*mapIterator));
	}
}

void CommonUtility::convertIntMapToStringMap(const map<int, bool> &mapList, map<string, bool> &resultList) {

	map<int, bool>::const_iterator iterMap;

	for (iterMap = mapList.begin(); iterMap != mapList.end(); iterMap++) {
		resultList[CommonUtility::NumberToString(iterMap->first)] = true;
	}
}

vector<string>::const_iterator CommonUtility::binaryLookup(const vector<string>& from, string &element) {
	vector<string>::const_iterator iter;
	// this is not binary lookup. 
	// must ensure binary lookup find the first element. 
	for (iter = from.begin(); iter != from.end(); iter++) {
		if (iter->compare(element) ==0)
			return iter;		
	}
	return iter;
}

void CommonUtility::split(const std::string &inputString, char delimiter, std::vector<std::string> &tokens) {
    std::stringstream strStream(inputString);
    std::string item;
    while (std::getline(strStream, item, delimiter)) {
        tokens.push_back(item);
    }   
}