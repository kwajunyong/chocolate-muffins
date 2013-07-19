#include "Modifies.h"

Modifies::Modifies(int numOfStmt, VarTable* varTable, ProcTable* procTable)
{
	_numOfStmt = numOfStmt;
	_varTable = varTable;
	_procTable = procTable;

	_varModifies.assign(_numOfStmt, std::vector<bool>(_varTable->getSize(), false));
	_procModifies.assign(_procTable->getSize(), std::vector<bool>(_varTable->getSize(), false));
}

Modifies::~Modifies(void)
{}

bool Modifies::addModifiesStmt(int stmtNum, std::string variable)
{
	if (stmtNumOutOfRange(stmtNum)) {
		return false;
	}
	
	int varIndex = _varTable->getIndex(variable);
	
	if (varIndexOutOfRange(varIndex)) {
		return false;
	}

	_varModifies[stmtNum-1][varIndex] = true;
	
	return true;
}

bool Modifies::addModifiesProc(std::string procedure, std::string variable)
{
	int procIndex = _procTable->getIndex(procedure);

	if (procIndexOutOfRange(procIndex)) {
		return false;
	}

	int varIndex = _varTable->getIndex(variable);

	if (varIndexOutOfRange(varIndex)) {
		return false;
	}

	_procModifies[procIndex][varIndex] = true;
	
	return true;
}

bool Modifies::isModifiesStmt(int stmtNum, std::string variable)
{
	if (stmtNum < 1 || stmtNum > _varModifies.size()) {
		return false;
	}

	int varIndex = _varTable->getIndex(variable);

	if (varIndexOutOfRange(varIndex)) {
		return false;
	}

	return _varModifies[stmtNum - 1][varIndex];
}

bool Modifies::isModifiesProc(std::string procedure, std::string variable)
{
	int procIndex = _procTable->getIndex(procedure);

	if (procIndexOutOfRange(procIndex)) {
		return false;
	}

	int varIndex = _varTable->getIndex(variable);

	if (varIndexOutOfRange(varIndex)) {
		return false;
	}

	return _procModifies[procIndex][varIndex];
}

std::vector<std::string> Modifies::getModifiedVar(int stmtNum)
{
	std::vector<std::string> results;

	if (stmtNumOutOfRange(stmtNum)) {
		return results;
	}

	for (int i = 0; i < _varModifies[stmtNum-1].size(); i++) {
		if (_varModifies[stmtNum - 1][i]) {
			results.push_back(_varTable->getName(i));
		}
	}

	return results;
}

std::vector<std::string> Modifies::getModifiedVar(std::string procedure)
{
	std::vector<std::string> results;

	int procIndex = _procTable->getIndex(procedure);

	if (procIndexOutOfRange(procIndex)) {
		return results;
	}

	for (int i = 0; i < _procModifies[procIndex].size(); i++) {
		if (_procModifies[procIndex][i]) {
			results.push_back(_varTable->getName(i));
		}
	}

	return results;
}

std::vector<int> Modifies::getModifiesStmt(std::string variable)
{
	std::vector<int> results;

	int varIndex = _varTable->getIndex(variable);
	
	if (varIndexOutOfRange(varIndex)) {
		return results;
	}

	for (int i = 0; i < _varModifies.size(); i++) {
		if (_varModifies[i][varIndex]) {
			results.push_back(i + 1);
		}
	}

	return results;
}

std::vector<std::string> Modifies::getModifiesProc(std::string variable)
{
	std::vector<std::string> results;

	int varIndex = _varTable->getIndex(variable);
	
	if (varIndexOutOfRange(varIndex)) {
		return results;
	}

	for (int i = 0; i < _procModifies.size(); i++) {
		if (_procModifies[i][varIndex]) {
			results.push_back(_procTable->getName(i));
		}
	}

	return results;
}

bool Modifies::stmtNumOutOfRange(int stmtNum)
{
	return stmtNum < 1 || stmtNum > _numOfStmt;
}

bool Modifies::varIndexOutOfRange(int varIndex)
{
	return varIndex == -1;
}

bool Modifies::procIndexOutOfRange(int procIndex)
{
	return procIndex == -1;
}