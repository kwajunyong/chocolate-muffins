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

	static void convertVector(const map<int, int> &mapList, vector<int>& resultList);
	static void convertVector(const map<int, int> &mapList, vector<string>& resultList);
	static void convertToMap(const vector<int>& resultList, map<int, int> &mapList);
};