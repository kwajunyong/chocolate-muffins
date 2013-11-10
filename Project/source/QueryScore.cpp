#include "QueryScore.h"
#include <iostream>
/*
High score means desirable 
*/
bool QueryScore::initialized = false;
double QueryScore::armScore = 800; // 
std::map <QUERYTYPE, std::vector<int>> QueryScore::scoreList;
std::map <QUERYTYPE, double> QueryScore::multiplierArmList; 
double QueryScore::getScore(QUERYTYPE type, int var) {

	if (var > 2)  {
		cout << "Not a valid variable";
		throw new exception("Not a valid variable");
	}

	initialize();

	return scoreList.find(type)->second.at(var);

}

double QueryScore::getArmScore() {
	return armScore;
}

double QueryScore::getMultiplierArm(QUERYTYPE type){


	initialize();

	return multiplierArmList.find(type)->second;

}

//double QueryScore::get
void QueryScore::initialize() {

	if (!initialized)
		initialized = true;
	else
		return;

	// 1.--------------------------------------------------------------
	{
		// Affect's variable
		vector<int> affectScore;
		// no variable 
		affectScore.push_back(1000);
		// one variable 
		affectScore.push_back(500);
		// two variable 
		affectScore.push_back(200);
		scoreList[QT_AFFECT] = affectScore;
	}

	// 2.--------------------------------------------------------------
	{
		// Affect Star's variable
		vector<int> affectStarScore;
		// no variable 
		affectStarScore.push_back(500);
		// one variable 
		affectStarScore.push_back(250);
		// two variable 
		affectStarScore.push_back(100);
		scoreList[QT_AFFECTSTAR] = affectStarScore;
	}

	// 3.--------------------------------------------------------------
	{
		// Next's variable
		vector<int> nextScore;
		// no variable 
		nextScore.push_back(20000);
		// one variable 
		nextScore.push_back(8000);
		// two variable 
		nextScore.push_back(2000);
		scoreList[QT_NEXT] = nextScore;
	}

	// 4.--------------------------------------------------------------
	{
		// nextStar's variable
		vector<int> nextStarScore;
		// no variable 
		nextStarScore.push_back(500);
		// one variable 
		nextStarScore.push_back(200);
		// two variable 
		nextStarScore.push_back(100);
		scoreList[QT_NEXTSTAR] = nextStarScore;
	}

	// 5.--------------------------------------------------------------
	{
		// parent's variable
		vector<int> parentScore;
		// no variable 
		parentScore.push_back(20000);
		// one variable 
		parentScore.push_back(10000);
		// two variable 
		parentScore.push_back(5000);
		scoreList[QT_PARENT] = parentScore;
	}

	// 6.--------------------------------------------------------------
	{
		// parent star's variable
		vector<int> parentStarScore;
		// no variable 
		parentStarScore.push_back(2000);
		// one variable 
		parentStarScore.push_back(1000);
		// two variable 
		parentStarScore.push_back(500);
		scoreList[QT_PARENTSTAR] = parentStarScore;
	}

	// 7.--------------------------------------------------------------
	{
		// modifies score's variable
		vector<int> modifiesScore;
		// no variable 
		modifiesScore.push_back(25000);
		// one variable 
		modifiesScore.push_back(12000);
		// two variable 
		modifiesScore.push_back(3000);
		scoreList[QT_MODIFIES] = modifiesScore;
	}

	// 8.--------------------------------------------------------------

	{
		// uses score's variable
		vector<int> usesScore;
		// no variable 
		usesScore.push_back(28000);
		// one variable 
		usesScore.push_back(14000);
		// two variable 
		usesScore.push_back(5000);
		scoreList[QT_USES] = usesScore;
	}


	// 9.--------------------------------------------------------------

	{
		// follow score's variable
		vector<int> followsScore;
		// no variable 
		followsScore.push_back(21000);
		// one variable 
		followsScore.push_back(10000);
		// two variable 
		followsScore.push_back(4000);
		scoreList[QT_FOLLOWS] = followsScore;
	}

	// 10.--------------------------------------------------------------

	{
		// uses score's variable
		vector<int> followsStarScore;
		// no variable 
		followsStarScore.push_back(3000);
		// one variable 
		followsStarScore.push_back(2000);
		// two variable 
		followsStarScore.push_back(800);
		scoreList[QT_FOLLOWSSTAR] = followsStarScore;
	}

	// 11.-------------------------------------------------------------


	{
		// While score's variable
		vector<int> whilesScore;
		// no variable 
		whilesScore.push_back(25000);
		// one variable 
		whilesScore.push_back(23000);
		// two variable 
		whilesScore.push_back(10000);
		scoreList[QT_WHILEPATTERN] = whilesScore;
	}

	// 12.-------------------------------------------------------------

	{
		// if score's variable
		vector<int> ifScore;
		// no variable 
		ifScore.push_back(23000);
		// one variable 
		ifScore.push_back(23000);
		// two variable 
		ifScore.push_back(10000);
		scoreList[QT_IFPATTERN] = ifScore;
	}

	// 13-------------------------------------------------------------

	{
		// expression score's variable
		vector<int> expressionScore;
		// no variable 
		expressionScore.push_back(15000);
		// one variable 
		expressionScore.push_back(18000);
		// two variable 
		expressionScore.push_back(10000);
		scoreList[QT_EXPRESSIONPATTERN] = expressionScore;
	}
	// 14-------------------------------------------------------------

	{
		// binaryRelation score's variable
		vector<int> binaryRelation;
		// no variable 
		binaryRelation.push_back(20000);
		// one variable 
		binaryRelation.push_back(40000);
		// two variable 
		binaryRelation.push_back(50000);
		scoreList[QT_BINARYRELATION] = binaryRelation;
	}

	// 15-------------------------------------------------------------



	{
		// callScore score's variable
		vector<int> callScore;
		// no variable 
		callScore.push_back(25000);
		// one variable 
		callScore.push_back(20000);
		// two variable 
		callScore.push_back(10000);
		scoreList[QT_CALLS] = callScore;
	}
	// 16-------------------------------------------------------------

	{
		// binaryRelation score's variable
		vector<int> callStarScore;
		// no variable 
		callStarScore.push_back(10000);
		// one variable 
		callStarScore.push_back(15000);	
		// two variable 
		callStarScore.push_back(3000);
		scoreList[QT_CALLSSTAR] = callStarScore;
	}



	multiplierArmList[QT_NEXT] = 1; 
	multiplierArmList[QT_NEXTSTAR] = .3; 
	multiplierArmList[QT_AFFECT] = .1; 
	multiplierArmList[QT_AFFECTSTAR] = .1; 
	multiplierArmList[QT_PARENT] = 1.2;
	multiplierArmList[QT_PARENTSTAR] = .3;
	multiplierArmList[QT_FOLLOWS] = 1.1;
	multiplierArmList[QT_FOLLOWSSTAR] = .1;
	multiplierArmList[QT_CALLS] = .6; 
	multiplierArmList[QT_CALLSSTAR] = .2; 
	multiplierArmList[QT_USES] = 2;
	multiplierArmList[QT_MODIFIES] = 2;
	multiplierArmList[QT_IFPATTERN] = 1;
	multiplierArmList[QT_WHILEPATTERN] = 1.3;
	multiplierArmList[QT_BINARYRELATION] = 1.2;
	multiplierArmList[QT_EXPRESSIONPATTERN] = 1.5;

}