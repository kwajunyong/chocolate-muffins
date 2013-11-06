#pragma once 
#include "EnumType.h"
#include <vector>

using namespace std;
class QueryScore {
public:
	static double getScore(QUERYTYPE qType, int noVar);
	static void initialize();
	static double getArmScore();
	static double getMultiplierArm(QUERYTYPE);
private:
	static std::map <QUERYTYPE, std::vector<int>> scoreList;
	static std::map <QUERYTYPE, double> multiplierArmList; // this is to store the multiplier for arm. 
													// One arm's linkage will have certain score multiplied with this multiplier
	static double armScore;
	static bool initialized;
};