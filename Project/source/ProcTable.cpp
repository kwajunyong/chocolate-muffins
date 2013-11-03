#include "ProcTable.h"

ProcTable::ProcTable(void)
{}

ProcTable::~ProcTable(void)
{}

bool ProcTable::addProcedure(std::string procedure, int fromStmtNum, int toStmtNum)
{
	bool success = false;

	if (getIndex(procedure) < 0) {
		_procNames.push_back(procedure);
		_stmtRanges.push_back(std::make_pair(fromStmtNum, toStmtNum));

		success = true;
	}
	
	return success;
}

int ProcTable::getIndex(std::string procedure)
{
	for (size_t i=0; i<_procNames.size(); i++) {
		if (procedure == _procNames[i]) {
			return i;
		}
	}

	return -1;
}

std::string ProcTable::getName(int index)
{
	if (index < 0 || index >= _procNames.size()) {
		throw std::out_of_range("Procedure index out of bound");
	}

	return _procNames[index];
}

std::string ProcTable::getProcedure(int stmtNum)
{
	for (size_t i=0; i<_stmtRanges.size(); i++) {
		if (inRange(stmtNum, _stmtRanges[i])) {
			return _procNames[i];
		}
	}

	throw std::out_of_range("Statement number out of bound");
}

std::pair<int, int> ProcTable::getRange(std::string procedure)
{
	int procIndex = getIndex(procedure);

	if (procIndex < 0) {
		return std::make_pair<int, int>(0, 0);
	}

	return _stmtRanges[procIndex];
}

std::vector<std::string> ProcTable::getAllNames()
{
	return _procNames;
}

int ProcTable::getSize()
{
	return _procNames.size();
}

bool ProcTable::inRange(int num, std::pair<int, int> range) {
	return num >= range.first && num <= range.second;
}