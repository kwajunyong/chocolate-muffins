#pragma once

#include <vector>
#include <string>

class ProcTable
{
public:
	ProcTable(void);
	~ProcTable(void);

	int addProcedure(std::string procedure);
	
	int getIndex(std::string procedure);
	std::string getName(int index);

	int getSize();

private:
	std::vector<std::string> _procTable;
};

