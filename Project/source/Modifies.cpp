#include "Modifies.h"

Modifies::Modifies(int numOfStmt)
{
	_numOfStmt = numOfStmt;

	_stmtVar.assign(_numOfStmt, std::vector<std::string>());
}

Modifies::~Modifies(void)
{}

bool Modifies::addModifiesStmt(int stmtNum, std::string variable)
{
	if (stmtNumOutOfRange(stmtNum)) {
		return false;
	}

	if (isModifiesStmt(stmtNum, variable)) {
		return false;
	}

	_stmtVar[stmtNum - 1].push_back(variable);
	_varStmt[variable].push_back(stmtNum);

	return true;
}

bool Modifies::addModifiesProc(std::string procedure, std::string variable)
{
	if (isModifiesProc(procedure, variable)) {
		return false;
	}

	_procVar[procedure].push_back(variable);
	_varProc[variable].push_back(procedure);

	return true;
}

bool Modifies::isModifiesStmt(int stmtNum, std::string variable)
{
	if (stmtNumOutOfRange(stmtNum)) {
		return false;
	}

	size_t size = _stmtVar[stmtNum - 1].size();

	for (size_t i = 0; i < size; i++) {
		if (_stmtVar[stmtNum - 1][i] == variable) {
			return true;
		}
	}

	return false;
}

bool Modifies::isModifiesProc(std::string procedure, std::string variable)
{
	size_t size = _procVar[procedure].size();

	for (int i = 0; i < size; i++) {
		if (_procVar[procedure][i] == variable) {
			return true;
		}
	}

	return false;
}

std::vector<std::string> Modifies::getModifiedVar(int stmtNum)
{
	if (stmtNumOutOfRange(stmtNum)) {
		return std::vector<std::string>();
	}

	return _stmtVar[stmtNum - 1];
}

std::vector<std::string> Modifies::getModifiedVar(std::string procedure)
{
	return _procVar[procedure];
}

std::vector<int> Modifies::getModifiesStmt(std::string variable)
{
	return _varStmt[variable];
}

std::vector<std::string> Modifies::getModifiesProc(std::string variable)
{
	return _varProc[variable];
}

bool Modifies::stmtNumOutOfRange(int stmtNum)
{
	return stmtNum < 1 || stmtNum > _numOfStmt;
}