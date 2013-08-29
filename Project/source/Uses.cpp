#include "Uses.h"

Uses::Uses(int numOfStmt, VarTable* varTable, ProcTable* procTable)
{
	_numOfStmt = numOfStmt;
	_varTable = varTable;
	_procTable = procTable;

	_varUses.assign(_numOfStmt, std::vector<bool>(_varTable->getSize(), false));
	_procUses.assign(_procTable->getSize(), std::vector<bool>(_varTable->getSize(), false));
}

Uses::~Uses(void)
{}

bool Uses::addUsesStmt(int stmtNum, std::string variable)
{
	if (stmtNumOutOfRange(stmtNum)) {
		return false;
	}
	
	int varIndex = _varTable->getIndex(variable);
	
	if (varIndexOutOfRange(varIndex)) {
		return false;
	}

	_varUses[stmtNum-1][varIndex] = true;
	
	return true;
}

bool Uses::addUsesProc(std::string procedure, std::string variable)
{
	int procIndex = _procTable->getIndex(procedure);

	if (procIndexOutOfRange(procIndex)) {
		return false;
	}

	int varIndex = _varTable->getIndex(variable);

	if (varIndexOutOfRange(varIndex)) {
		return false;
	}

	_procUses[procIndex][varIndex] = true;
	
	return true;
}

bool Uses::isUsesStmt(int stmtNum, std::string variable)
{
	if (stmtNum < 1 || stmtNum > _varUses.size()) {
		return false;
	}

	int varIndex = _varTable->getIndex(variable);

	if (varIndexOutOfRange(varIndex)) {
		return false;
	}

	return _varUses[stmtNum - 1][varIndex];
}

bool Uses::isUsesProc(std::string procedure, std::string variable)
{
	int procIndex = _procTable->getIndex(procedure);

	if (procIndexOutOfRange(procIndex)) {
		return false;
	}

	int varIndex = _varTable->getIndex(variable);

	if (varIndexOutOfRange(varIndex)) {
		return false;
	}

	return _procUses[procIndex][varIndex];
}

std::vector<std::string> Uses::getUsedVar(int stmtNum)
{
	std::vector<std::string> results;

	if (stmtNumOutOfRange(stmtNum)) {
		return results;
	}

	for (size_t i = 0; i < _varUses[stmtNum-1].size(); i++) {
		if (_varUses[stmtNum - 1][i]) {
			results.push_back(_varTable->getName(i));
		}
	}

	return results;
}

std::vector<std::string> Uses::getUsedVar(std::string procedure)
{
	std::vector<std::string> results;

	int procIndex = _procTable->getIndex(procedure);

	if (procIndexOutOfRange(procIndex)) {
		return results;
	}

	for (size_t i = 0; i < _procUses[procIndex].size(); i++) {
		if (_procUses[procIndex][i]) {
			results.push_back(_varTable->getName(i));
		}
	}

	return results;
}

std::vector<int> Uses::getUsesStmt(std::string variable)
{
	std::vector<int> results;

	int varIndex = _varTable->getIndex(variable);
	
	if (varIndexOutOfRange(varIndex)) {
		return results;
	}

	for (size_t i = 0; i < _varUses.size(); i++) {
		if (_varUses[i][varIndex]) {
			results.push_back(i + 1);
		}
	}

	return results;
}

std::vector<std::string> Uses::getUsesProc(std::string variable)
{
	std::vector<std::string> results;

	int varIndex = _varTable->getIndex(variable);
	
	if (varIndexOutOfRange(varIndex)) {
		return results;
	}

	for (size_t i = 0; i < _procUses.size(); i++) {
		if (_procUses[i][varIndex]) {
			results.push_back(_procTable->getName(i));
		}
	}

	return results;
}

bool Uses::stmtNumOutOfRange(int stmtNum)
{
	return stmtNum < 1 || stmtNum > _numOfStmt;
}

bool Uses::varIndexOutOfRange(int varIndex)
{
	return varIndex == -1;
}

bool Uses::procIndexOutOfRange(int procIndex)
{
	return procIndex == -1;
}