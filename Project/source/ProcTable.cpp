#include "ProcTable.h"

ProcTable::ProcTable(void)
{}

ProcTable::~ProcTable(void)
{}

bool ProcTable::addProcedure(std::string procedure)
{
	bool success = false;

	if (getIndex(procedure) < 0) {
		_procTable.push_back(procedure);

		success = true;
	}
	
	return success;
}

int ProcTable::getIndex(std::string procedure)
{
	for (size_t i=0; i<_procTable.size(); i++) {
		if (procedure == _procTable[i]) {
			return i;
		}
	}

	return -1;
}

std::string ProcTable::getName(int index)
{
	if (index < 0 || index >= _procTable.size()) {
		throw std::out_of_range("Procedure index out of bound");
	}

	return _procTable[index];
}

std::vector<std::string> ProcTable::getAllNames()
{
	return _procTable;
}

int ProcTable::getSize()
{
	return _procTable.size();
}