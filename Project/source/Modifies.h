#pragma once

#include <vector>
#include <map>

#include "VarTable.h"
#include "ProcTable.h"

class Modifies
{
public:
	Modifies(int numOfStmt);
	~Modifies(void);

	bool addModifiesStmt(int stmtNum, std::string variable);
	bool addModifiesProc(std::string procedure, std::string variable);

	bool isModifiesStmt(int stmtNum, std::string variable);
	bool isModifiesProc(std::string procedure, std::string variable);

	std::vector<std::string> getModifiedVar(int stmtNum);
	std::vector<std::string> getModifiedVar(std::string procedure);

	std::vector<int> getModifiesStmt(std::string variable);
	std::vector<std::string> getModifiesProc(std::string variable);
private:
	int _numOfStmt;

	std::vector<std::vector<std::string>> _stmtVar;
	std::map<std::string, std::vector<std::string>> _procVar;

	std::map<std::string, std::vector<int>> _varStmt;
	std::map<std::string, std::vector<std::string>> _varProc;

	bool stmtNumOutOfRange(int stmtNum);
};