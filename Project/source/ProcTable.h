#pragma once

#include <vector>
#include <string>
#include <utility>

class ProcTable
{
public:
	ProcTable(void);
	~ProcTable(void);

	bool addProcedure(std::string procedure, int fromStmtNum, int toStmtNum);
	
	int getIndex(std::string procedure);
	std::string getName(int index);

	std::string getProcedure(int stmtNum);
	std::vector<std::string> getAllNames();
	int getSize();

private:
	std::vector<std::string> _procNames;
	std::vector<std::pair<int, int>> _stmtRanges;

	bool inRange(int num, std::pair<int, int> range);
};