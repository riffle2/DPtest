
// DPtestDlg.h : header file
//

#pragma once
#include "afxwin.h"
class CRunInfo
{
public:
	CString strMessage1;
	CString strMessage2;
	CString strMessage3;
	CString strResult;
	int TotalRoutine;
	int DeletedRoutine;
	ULONGLONG dwTickCount;
	CRunInfo()
	{
		TotalRoutine = DeletedRoutine = 0;
	}
};

// CDPtestDlg dialog
class CDPtestDlg : public CDialogEx
{
// Construction
public:
	CDPtestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DPTEST_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	void ShowRunInfo(CRunInfo* pInfo);
	void ShowResultInfo(CRunInfo* pInfo);
	CStatic m_stMsg1;
	CStatic m_stMsg2;
	CEdit m_edtResult;
	CEdit m_edtMaxDays;
	CEdit m_edtpercent;
};
