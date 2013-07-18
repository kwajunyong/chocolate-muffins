#pragma once

#include <vector>
#include <string>

class VarTable
{
public:
	VarTable(void);
	~VarTable(void);

	int addVariable(std::string variable);
	
	int getIndex(std::string variable);
	std::string getName(int index);

	std::vector<std::string> getAllNames();
	int getSize();

private:
	std::vector<std::string> _varTable;
};

