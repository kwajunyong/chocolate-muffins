#include "ProcTable.h"

ProcTable::ProcTable(void)
{}

ProcTable::~ProcTable(void)
{}

int ProcTable::addProcedure(std::string procedure)
{
	if (getIndex(procedure) < 0) {
		_procTable.push_back(procedure);
	}
	
	return getIndex(procedure);
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
	if (index < 0 || index > _procTable.size()) {
		throw std::out_of_range("Procedure index out of bound");
	}

	return _procTable[index];
}

int ProcTable::getSize()
{
	return _procTable.size();
}