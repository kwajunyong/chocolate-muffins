#include "Stats.h"

Stats::Stats(ProcTable* procTable, int numOfStmt)
{
	_procTable = procTable;

	_program.assign(4, 0);
	
	_procedures.assign(_procTable->getSize(), std::vector<int>(4, 0));

	_levels.assign(numOfStmt, 0);
}

Stats::~Stats(void)
{}

int Stats::getNumOfStmt(ASTType type)
{
	int typeIndex = hashType(type);

	if (typeIndex < 0) {
		return 0;
	}

	return _program[typeIndex];
}

int Stats::getNumOfStmt(std::string procedure, ASTType type)
{
	int procIndex = _procTable->getIndex(procedure);

	if (procIndex < 0) {
		return 0;
	}
	
	int typeIndex = hashType(type);

	if (typeIndex < 0) {
		return 0;
	}
	
	return _procedures[procIndex][typeIndex];
}

int Stats::getLevel(int stmtNum)
{
	if (stmtNumOutOfRange(stmtNum)) {
		return 0;
	}

	return _levels[stmtNum - 1];
}

bool Stats::addNumOfStmt(std::string procedure, ASTType type)
{
	int procIndex = _procTable->getIndex(procedure);

	if (procIndex < 0) {
		return false;
	}
	
	int typeIndex = hashType(type);

	if (typeIndex < 0) {
		return false;
	}
	
	_program[typeIndex]++;
	_procedures[procIndex][typeIndex]++;

	return true;
}

bool Stats::setLevel(int stmtNum, int level)
{
	if (stmtNumOutOfRange(stmtNum)) {
		return false;
	}

	_levels[stmtNum - 1] = level;

	return true;
}

int Stats::hashType(ASTType type)
{
	if (type != ASSIGN && type != WHILE && type != IF && type != CALL) {
		return -1;
	}

	return type % 4;
}

bool Stats::stmtNumOutOfRange(int stmtNum)
{
	return stmtNum < 1 || stmtNum > _levels.size();
}