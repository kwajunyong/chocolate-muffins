#include "VarTable.h"

VarTable::VarTable(void)
{}

VarTable::~VarTable(void)
{}

int VarTable::addVariable(std::string variable)
{
	if (getIndex(variable) < 0) {
		_varTable.push_back(variable);
	}
	
	return getIndex(variable);
}

int VarTable::getIndex(std::string variable)
{
	for (size_t i=0; i<_varTable.size(); i++) {
		if (variable == _varTable[i]) {
			return i;
		}
	}

	return -1;
}

std::string VarTable::getName(int index)
{
	if (index < 0 || index >= _varTable.size()) {
		throw std::out_of_range("Variable index out of bound");
	}

	return _varTable[index];
}

std::vector<std::string> VarTable::getAllNames()
{
	return _varTable;
}

int VarTable::getSize()
{
	return _varTable.size();
}