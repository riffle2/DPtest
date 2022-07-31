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

int Routie::compare(const Routie& otherRoutie)
{
	int iResult = 0;
	if (index == otherRoutie.index) {
		iResult = (cost <= otherRoutie.cost) ? -1 : 1;
	}
	else {
		if (index < otherRoutie.index)
		{
			if (cost + maxCost(otherRoutie.index - index) <= otherRoutie.cost)
			{
				iResult = -1;
			}
		}
		else {
			if (cost >= otherRoutie.cost + maxCost(index - otherRoutie.index))
			{
				iResult = 1;
			}
		}
	}
	return iResult;
}

void DeleteHighCost(CRunInfo& runInfo, vector <Routie>& routies)
{
	//Routie curRoutie;
	int iResult;
	bool bErased;
	for (auto iter = routies.begin(); iter != routies.end(); )
	{
		bErased = false;
		for (auto iterSub = iter + 1; iterSub != routies.end();) {
			iResult = iter->compare(*iterSub);
			if (iResult < 0) {
				iterSub = routies.erase(iterSub);
				++runInfo.DeletedRoutie;
			}else if (iResult > 0) {
				iter = routies.erase(iter);
				bErased = true;
				++runInfo.DeletedRoutie;
				break;
			}else {
				++iterSub;
			}
		}
		if (!bErased)
			++iter;
	}
	// follow code performance isn't well, rewrite 
	//for (auto iter = routies.begin(); iter != routies.end(); ++iter)
	//{
	//	if (iter->deleted)
	//		continue;
	//	for (auto iterSub = iter + 1; iterSub != routies.end(); ++iterSub) {
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

	//for (auto iter = routies.begin(); iter != routies.end(); )
	//{
	//	if (iter->deleted) {
	//		iter = routies.erase(iter);
	//		++runInfo.DeletedRoutie;
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
	vector <Routie> routies;
	vector <Routie>::iterator iter;
	Routie curRoutie;
	int  iLp;
	int n;
	curRoutie.index = -1;
	routies.push_back(curRoutie);
	int iCount = 1;
	for ( auto day = AtDays.begin(); day < AtDays.end(); ++day, ++iCount) {
		n = *day;
		vector <Routie> newInsert;
		for (iter = routies.begin(); iter != routies.end(); iter++)
		{
			if (n > iter->index)
			{
				for (iLp = 1; iLp < TicketCount; ++iLp) {
					curRoutie = *iter;
					curRoutie.index = (n + Tickets[iLp].Days - 1);
					curRoutie.cost += Tickets[iLp].Cost;
					curRoutie.Points.push_back((iLp << 28) + n);
					newInsert.push_back(curRoutie);
				}

				iter->index = n + Tickets[0].Days - 1;
				iter->cost += Tickets[0].Cost;
				iter->Points.push_back((0 << 28) + n);
			}
		}
		routies.insert(routies.end(), newInsert.begin(), newInsert.end());
		runinfo.TotalRoutie += newInsert.size();

		//
		DeleteHighCost(runinfo,routies);

		if (!(iCount % onePercent)) {
			runinfo.strMessage1.Format(TEXT("Do %d/%d rout Count:%d"), iCount, AtDays.size(), routies.size());
			pDlg->ShowRunInfo(&runinfo);
		}
	}

	// get minimum Cost 
	Routie minRoutie = *routies.begin();
	int minCost = routies.begin()->cost;
	for (auto iter : routies)
	{
		if (minCost > iter.cost){
			minRoutie = iter;
			minCost = iter.cost;
		}
	}
	Routie ResultRoutie = minRoutie;

	// Show Result
	CString strOne;
	strOne.Format(_T("\r\nResult:  Minimum Cost:%d\t\t(Calc Time:%lldms,Search total routine :%d)\r\n"), ResultRoutie.cost, GetTickCount64() - runinfo.dwTickCount, runinfo.TotalRoutie);
	runinfo.strResult += strOne;
	runinfo.strResult += "Data:\r\n";
	for (auto day :AtDays) {
		strOne.Format(_T("%d,"), day);
		runinfo.strResult.Append(strOne);
	}
	runinfo.strResult += _T("\r\nticket Detail:\r\n");
	for (auto buyaction : ResultRoutie.Points) {
		strOne.Format(_T("Day%d, buy %s\r\n"), (buyaction) & 0xfffffff, Tickets[(buyaction) >> 28].decr.c_str());
		runinfo.strResult.Append(strOne);
	}
	pDlg->ShowResultInfo(&runinfo);
	return ResultRoutie.cost;
}

