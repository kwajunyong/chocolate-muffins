#include "ConstTable.h"

ConstTable::ConstTable(void)
{}

ConstTable::~ConstTable(void)
{}

bool ConstTable::addConstant(int constant)
{
	bool success = false;

	if (getIndex(constant) < 0) {
		_constTable.push_back(constant);
		
		success = true;
	}
	
	return success;
}

int ConstTable::getIndex(int constant)
{
	for (size_t i=0; i<_constTable.size(); i++) {
		if (constant == _constTable[i]) {
			return i;
		}
	}

	return -1;
}

int ConstTable::getValue(int index)
{
	if (index < 0 || index >= _constTable.size()) {
		throw std::out_of_range("Constant index out of bound");
	}

	return _constTable[index];
}

std::vector<int> ConstTable::getAllValues()
{
	return _constTable;
}

int ConstTable::getSize()
{
	return _constTable.size();
}