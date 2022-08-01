#include "stdafx.h"
#include "TestCase1.h"
#include "DPtestDlg.h"
#include <cstdlib>
#include <vector>
using namespace std;

typedef struct {
	int Days;
	int Cost;
	wstring decr;
}TICKET;

const TICKET Tickets[] = {
	{ 30,25,_T("month ticket") },
	{ 7,7,_T("week ticket") },
	{ 1,2,_T("day ticket") },
};
constexpr int TicketCount = sizeof(Tickets) / sizeof(Tickets[0]);

int maxCost(int days)
{
	if (days <= 0)
		return 0;
	if (days <= 7)
		return days * 2 > 7 ? 7 : days * 2;
	else if (days <= 30)
		return (days + 6) / 7 * 7 > 7 ? 25 : (days + 6) / 7 * 7;
	else
		return 0X7fffffff;
}

int Routine::compare(const Routine& otherRoutine)
{
	int iResult = 0;
	if (index == otherRoutine.index) {
		iResult = (cost <= otherRoutine.cost) ? -1 : 1;
	}
	else {
		if (index < otherRoutine.index)
		{
			if (cost + maxCost(otherRoutine.index - index) <= otherRoutine.cost)
			{
				iResult = -1;
			}
		}
		else {
			if (cost >= otherRoutine.cost + maxCost(index - otherRoutine.index))
			{
				iResult = 1;
			}
		}
	}
	return iResult;
}

void DeleteHighCost(CRunInfo& runInfo, vector <Routine>& routines)
{
	//Routine curRoutine;
	int iResult;
	bool bErased;
	for (auto iter = routines.begin(); iter != routines.end(); )
	{
		bErased = false;
		for (auto iterSub = iter + 1; iterSub != routines.end();) {
			iResult = iter->compare(*iterSub);
			if (iResult < 0) {
				iterSub = routines.erase(iterSub);
				++runInfo.DeletedRoutine;
			}else if (iResult > 0) {
				iter = routines.erase(iter);
				bErased = true;
				++runInfo.DeletedRoutine;
				break;
			}else {
				++iterSub;
			}
		}
		if (!bErased)
			++iter;
	}
	// follow code performance isn't well, rewrite 
	//for (auto iter = routines.begin(); iter != routines.end(); ++iter)
	//{
	//	if (iter->deleted)
	//		continue;
	//	for (auto iterSub = iter + 1; iterSub != routines.end(); ++iterSub) {
	//		if (iterSub->deleted)
	//			continue;
	//		iResult = iter->compare(*iterSub);
	//		if (iResult < 0) {
	//			iterSub->deleted = true;
	//		}
	//		else if (iResult > 0) {
	//			iter->deleted = true;
	//			break;
	//		}
	//	}
	//}

	//for (auto iter = routines.begin(); iter != routines.end(); )
	//{
	//	if (iter->deleted) {
	//		iter = routines.erase(iter);
	//		++runInfo.DeletedRoutine;
	//	}
	//	else
	//		iter++;
	//}
}


int DoTest(void* pUserData, const vector<int>& AtDays)
{
	CDPtestDlg* pDlg = reinterpret_cast<CDPtestDlg*>(pUserData);
	int onePercent = AtDays.size() / 100;
	if (onePercent <= 0)onePercent = 1;

	CRunInfo runinfo;
	runinfo.dwTickCount = GetTickCount64();
	vector <Routine> routines;
	vector <Routine>::iterator iter;
	Routine curRoutine;
	int  iLp;
	int n;
	curRoutine.index = -1;
	routines.push_back(curRoutine);
	int iCount = 1;
	for ( auto day = AtDays.begin(); day < AtDays.end(); ++day, ++iCount) {
		n = *day;
		vector <Routine> newInsert;
		for (iter = routines.begin(); iter != routines.end(); iter++)
		{
			if (n > iter->index)
			{
				for (iLp = 1; iLp < TicketCount; ++iLp) {
					curRoutine = *iter;
					curRoutine.index = (n + Tickets[iLp].Days - 1);
					curRoutine.cost += Tickets[iLp].Cost;
					curRoutine.Points.push_back((iLp << 28) + n);
					newInsert.push_back(curRoutine);
				}

				iter->index = n + Tickets[0].Days - 1;
				iter->cost += Tickets[0].Cost;
				iter->Points.push_back((0 << 28) + n);
			}
		}
		routines.insert(routines.end(), newInsert.begin(), newInsert.end());
		runinfo.TotalRoutine += newInsert.size();

		//
		DeleteHighCost(runinfo,routines);

		if (!(iCount % onePercent)) {
			runinfo.strMessage1.Format(TEXT("Do %d/%d rout Count:%d"), iCount, AtDays.size(), routines.size());
			pDlg->ShowRunInfo(&runinfo);
		}
	}

	// get minimum Cost 
	Routine minRoutine = *routines.begin();
	int minCost = routines.begin()->cost;
	for (auto iter : routines)
	{
		if (minCost > iter.cost){
			minRoutine = iter;
			minCost = iter.cost;
		}
	}
	Routine ResultRoutine = minRoutine;

	// Show Result
	CString strOne;
	strOne.Format(_T("\r\nResult:  Minimum Cost:%d\t\t(Calc Time:%lldms,Search total routine :%d)\r\n"), ResultRoutine.cost, GetTickCount64() - runinfo.dwTickCount, runinfo.TotalRoutine);
	runinfo.strResult += strOne;
	runinfo.strResult += "Data:\r\n";
	for (auto day :AtDays) {
		strOne.Format(_T("%d,"), day);
		runinfo.strResult.Append(strOne);
	}
	runinfo.strResult += _T("\r\nticket Detail:\r\n");
	for (auto buyaction : ResultRoutine.Points) {
		strOne.Format(_T("Day%d, buy %s\r\n"), (buyaction) & 0xfffffff, Tickets[(buyaction) >> 28].decr.c_str());
		runinfo.strResult.Append(strOne);
	}
	pDlg->ShowResultInfo(&runinfo);
	return ResultRoutine.cost;
}

