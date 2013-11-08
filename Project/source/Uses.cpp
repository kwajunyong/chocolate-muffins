#include "Uses.h"

Uses::Uses(int numOfStmt)
{
	_numOfStmt = numOfStmt;

	_stmtVar.assign(_numOfStmt, std::vector<std::string>());
}

Uses::~Uses(void)
{}

bool Uses::addUsesStmt(int stmtNum, std::string variable)
{
	if (stmtNumOutOfRange(stmtNum)) {
		return false;
	}

	if (isUsesStmt(stmtNum, variable)) {
		return false;
	}

	_stmtVar[stmtNum - 1].push_back(variable);
	_varStmt[variable].push_back(stmtNum);

	return true;
}

bool Uses::addUsesProc(std::string procedure, std::string variable)
{
	if (isUsesProc(procedure, variable)) {
		return false;
	}

	_procVar[procedure].push_back(variable);
	_varProc[variable].push_back(procedure);

	return true;
}

bool Uses::isUsesStmt(int stmtNum, std::string variable)
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

bool Uses::isUsesProc(std::string procedure, std::string variable)
{
	size_t size = _procVar[procedure].size();

	for (int i = 0; i < size; i++) {
		if (_procVar[procedure][i] == variable) {
			return true;
		}
	}

	return false;
}

std::vector<std::string> Uses::getUsedVar(int stmtNum)
{
	if (stmtNumOutOfRange(stmtNum)) {
		return std::vector<std::string>();
	}

	return _stmtVar[stmtNum - 1];
}

std::vector<std::string> Uses::getUsedVar(std::string procedure)
{
	return _procVar[procedure];
}

std::vector<int> Uses::getUsesStmt(std::string variable)
{
	return _varStmt[variable];
}

std::vector<std::string> Uses::getUsesProc(std::string variable)
{
	return _varProc[variable];
}

bool Uses::stmtNumOutOfRange(int stmtNum)
{
	return stmtNum < 1 || stmtNum > _numOfStmt;
}