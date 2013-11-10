#pragma once

#include "ProcTable.h"
#include "ASTType.h"

#include <vector>

class Stats
{
public:
	Stats(ProcTable* procTable, int stmtNum);
	~Stats(void);
	
	bool addNumOfStmt(std::string procedure, ASTType type);
	bool setLevel(int stmtNum, int level);

	int getNumOfStmt(ASTType type);
	int getNumOfStmt(std::string procedure, ASTType type);
	int getLevel(int stmtNum);

private:
	ProcTable* _procTable;

	std::vector<int> _program;
	std::vector<std::vector<int>> _procedures;
	std::vector<int> _levels;

	int hashType(ASTType type);

	bool stmtNumOutOfRange(int stmtNum);
};