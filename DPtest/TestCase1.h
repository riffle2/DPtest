#pragma once
#include <vector>

class Routie
{
public:
	int cost;
	int index;
	int deleted;
	std::vector<int> Points;
	int compare(const Routie& otherRoutie);
};

int DoTest(void* pDlg, const std::vector<int>& AtDays);


