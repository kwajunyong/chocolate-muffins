#pragma once
#include <sstream>

#include <string>
#include <map>
#include <vector>

using namespace std;

class CommonUtility {
public:
	static string NumberToString ( int Number );

	static void convertVector(const map<string, int> &mapList, vector<string> & resultList);
	static void convertVector(const map<string, bool> &mapList, vector<string> & resultList);
	
	
	static void convertVector(const map<int, int> &mapList, vector<int>& resultList);
	static void convertVector(const map<int, bool> &mapList, vector<int>& resultList);

	static void convertVector(const map<int, int> &mapList, vector<string>& resultList);

	static void convertToMap(const vector<int>& resultList, map<int, int> &mapList);
	static void convertToMap(const vector<int>& resultList, map<int, bool> &mapList);
	static void convertToMap(const vector<string>& resultList, map<string, bool> &mapList);

	static void convertIntVectorToString(const vector<int>& from, vector<string>& resultList);
	static vector<string>::const_iterator binaryLookup(const vector<string> &vector, string &element);
};