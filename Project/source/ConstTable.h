#pragma once

#include <vector>
#include <string>

class ConstTable
{
public:
	ConstTable(void);
	~ConstTable(void);

	bool addConstant(int constant);
	
	int getIndex(int constant);
	int getValue(int index);

	std::vector<int> getAllValues();
	int getSize();

private:
	std::vector<int> _constTable;
};