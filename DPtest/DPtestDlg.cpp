
// DPtestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DPtest.h"
#include "DPtestDlg.h"
#include "afxdialogex.h"
#include "TestCase1.h"
#include <ctime>
#include <set>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CDPtestDlg dialog



CDPtestDlg::CDPtestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DPTEST_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDPtestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MSG1, m_stMsg1);
	DDX_Control(pDX, IDC_MSG2, m_stMsg2);
	DDX_Control(pDX, IDC_EDIT1, m_edtResult);
	DDX_Control(pDX, IDC_EDIT2, m_edtMaxDays);
	DDX_Control(pDX, IDC_EDIT3, m_edtpercent);
}

BEGIN_MESSAGE_MAP(CDPtestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CDPtestDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CDPtestDlg message handlers

BOOL CDPtestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	SetDlgItemInt(m_edtMaxDays.GetDlgCtrlID(), 30000);
	SetDlgItemInt(m_edtpercent.GetDlgCtrlID(), 60);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDPtestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDPtestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDPtestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//int __cdecl FuncCompare(void const *base1, void const*base2)
//{
//	return *(int*)base1 - *(int*)base2;
//}

void CDPtestDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
	m_edtResult.SetWindowText(_T(""));

	UINT maxDay = GetDlgItemInt(m_edtMaxDays.GetDlgCtrlID());
	UINT dayCount = maxDay* GetDlgItemInt(m_edtpercent.GetDlgCtrlID()) / 100;
	if (dayCount < 2) {
		MessageBox(_T("Day Count is too small"), MB_OK);
		return;
	}/*else if (dayCount >= RAND_MAX-1) {
		MessageBox(_T("Day Count is too big"), MB_OK);
		return;
	}	*/

	vector<int> vertify = {1,3,5,6,8,9,29,30};
	int result = DoTest(this, vertify);
	if (result != 13) {
		// calc result is error
		return;
	}

	// create unrepeated data 
	set<int> setDays;
	vector<int> AtDays;
	std::srand((unsigned int)std::time(NULL));
	
	if (maxDay < RAND_MAX) {
		while (setDays.size() < dayCount) {
			setDays.insert(std::rand()*maxDay / (RAND_MAX + 1u));
		}
	}
	else {
		UINT Level = (maxDay / (RAND_MAX + 1u))+1;
		UINT  tempval;
		while (setDays.size() < dayCount) {
			tempval =(std::rand() * Level / (RAND_MAX + 1u) )*RAND_MAX + std::rand();
			if (tempval <maxDay)
				setDays.insert(tempval);
		}
	}

	// moveto vector
	for (auto nIterator : setDays)
		AtDays.push_back(nIterator+1);
	//sort 
//	qsort(&*AtDays.begin(), AtDays.size(), sizeof(int), FuncCompare);
	std::sort(AtDays.begin(), AtDays.end(),std::less<int>());
	HCURSOR hold =::GetCursor();
	::SetCursor(LoadCursor(NULL, IDC_WAIT));
	DoTest(this, AtDays);
	::SetCursor(hold);
}

void CDPtestDlg::ShowRunInfo(CRunInfo* pInfo)
{
	m_stMsg1.SetWindowText(pInfo->strMessage1);
	m_stMsg2.SetWindowText(pInfo->strMessage2);
}
void CDPtestDlg::ShowResultInfo(CRunInfo* pInfo)
{
	CString  strText;
	m_edtResult.GetWindowText(strText);
	m_edtResult.SetWindowText(strText+pInfo->strResult + _T("\r\n\r\n"));
}
