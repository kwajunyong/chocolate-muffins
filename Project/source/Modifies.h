#pragma once

#include <vector>

#include "VarTable.h"
#include "ProcTable.h"

class Modifies
{
public:
	Modifies(int _numOfStmt, VarTable* varTable, ProcTable* procTable);
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

	VarTable* _varTable;
	ProcTable* _procTable;

	std::vector<std::vector<bool>> _varModifies;
	std::vector<std::vector<bool>> _procModifies;

	bool stmtNumOutOfRange(int stmtNum);
	bool varIndexOutOfRange(int varIndex);
	bool procIndexOutOfRange(int procIndex);
};