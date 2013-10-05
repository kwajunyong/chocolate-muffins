#include "CommonUtility.h"

using namespace std;

  string CommonUtility::NumberToString ( int Number )
  {
     ostringstream ss;
     ss << Number;
     return ss.str();
  }

  
  void CommonUtility::convertVector(const map<string, int> & mapList, vector<string>& resultList ) {
	map<string, int>::const_iterator mapIterator;
	
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