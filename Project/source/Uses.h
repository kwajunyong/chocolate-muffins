#pragma once

#include <vector>
#include <map>

#include "VarTable.h"
#include "ProcTable.h"

class Uses
{
public:
	Uses(int numOfStmt);
	~Uses(void);

	bool addUsesStmt(int stmtNum, std::string variable);
	bool addUsesProc(std::string procedure, std::string variable);

	bool isUsesStmt(int stmtNum, std::string variable);
	bool isUsesProc(std::string procedure, std::string variable);

	std::vector<std::string> getUsedVar(int stmtNum);
	std::vector<std::string> getUsedVar(std::string procedure);

	std::vector<int> getUsesStmt(std::string variable);
	std::vector<std::string> getUsesProc(std::string variable);
private:
	int _numOfStmt;

	std::vector<std::vector<std::string>> _stmtVar;
	std::map<std::string, std::vector<std::string>> _procVar;

	std::map<std::string, std::vector<int>> _varStmt;
	std::map<std::string, std::vector<std::string>> _varProc;

	bool stmtNumOutOfRange(int stmtNum);
};