#pragma once
#include <vector>

class Routine
{
public:
	int cost;
	int index;
	int deleted;
	std::vector<int> Points;
	int compare(const Routine& otherRoutine);
};

int DoTest(void* pDlg, const std::vector<int>& AtDays);


