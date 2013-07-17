#pragma once

#include <vector>

#include "VarTable.h"
#include "ProcTable.h"

class Uses
{
public:
	Uses(int _numOfStmt, VarTable* varTable, ProcTable* procTable);
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

	VarTable* _varTable;
	ProcTable* _procTable;

	std::vector<std::vector<bool>> _varUses;
	std::vector<std::vector<bool>> _procUses;

	bool stmtNumOutOfRange(int stmtNum);
	bool varIndexOutOfRange(int varIndex);
	bool procIndexOutOfRange(int procIndex);
};