
// LeanplumDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "LeanplumDemo.h"
#include "LeanplumDemoDlg.h"
#include "afxdialogex.h"
#include "ShopVerADlg.h"
#include "ShopVerBDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CLeanplumDemoDlg dialog



CLeanplumDemoDlg::CLeanplumDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLeanplumDemoDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLeanplumDemoDlg::Notify(MessageCode::MESSAGE_CODE messageCode, WPARAM wParam /*= NULL*/, LPARAM lParam /*= NULL*/)
{
	if (MessageCode::MESSAGE_GETVARS_FINISH == messageCode) {
		m_leanplum.GetValuebyId(_T("HelloMessage"), m_helloMsg);
		m_leanplum.GetValuebyId(_T("ByeMessage"), m_byeMsg);
		m_leanplum.GetValuebyId(_T("VersionNumber"), m_verNum);
		// update UI
		UpdateUI();
		// stop session
		m_leanplum.Stop();
	} else if (MessageCode::MESSAGE_START_FINISH == messageCode) {
		// get variables
		m_leanplum.SyncVariables();
	}
}

void CLeanplumDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CLeanplumDemoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON3, &CLeanplumDemoDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON2, &CLeanplumDemoDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BTN_SHOP, &CLeanplumDemoDlg::OnBnClickedBtnShop)
END_MESSAGE_MAP()


// CLeanplumDemoDlg message handlers

int CLeanplumDemoDlg::GetDeviceId()
{
	return m_deviceId++;
}

int CLeanplumDemoDlg::GetUserId()
{
	return m_userId++;
}

void CLeanplumDemoDlg::DefineLeanplumVariables()
{
	// define variables
	m_leanplum.DefineVariable(_T("HelloMessage"), std::make_pair(Leanplum::VARIABLE_TYPE::STRING, _T("Become a premium member.")));
	m_leanplum.DefineVariable(_T("VersionNumber"), std::make_pair(Leanplum::VARIABLE_TYPE::INT, _T("1")));
	m_leanplum.DefineVariable(_T("ByeMessage"), std::make_pair(Leanplum::VARIABLE_TYPE::STRING, _T("Thanks!")));
	m_leanplum.FinishVariablesDefinition();
}

void CLeanplumDemoDlg::RunLeanplum()
{
	// initial leanplum object
	m_leanplum.ResetApisData();
	// set user info
	m_leanplum.SetUserId(m_userId);
	m_leanplum.SetDeviceId(m_deviceId);
	// start session
	m_leanplum.Start();
}

void CLeanplumDemoDlg::UpdateUI()
{
	GetDlgItem(IDC_STATIC_MSG)->SetWindowText(m_helloMsg);
	if (1 == m_verNum) {
		GetDlgItem(IDC_BTN_SHOP)->ShowWindow(TRUE);
	} else {
		// 顯示Button1 圖片
		CBitmap Bitmap;
		Bitmap.LoadBitmap(IDB_PLEASE);
		HBITMAP hBitmap=(HBITMAP)Bitmap.Detach();
		CButton *pButton=(CButton*)GetDlgItem(IDC_BUTTON2);
		pButton->SetBitmap(hBitmap); 
		GetDlgItem(IDC_BUTTON2)->ShowWindow(TRUE);
	}
}

BOOL CLeanplumDemoDlg::OnInitDialog()
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

	// add as LeanplumSDK observer
	m_leanplum.AttachObserver(this);
	// define app keys
	m_leanplum.SetAppId(_T("Your App ID"));
	m_leanplum.SetProductionKey(_T("Your Production Key"));
	m_leanplum.SetDevelopmentKey(_T("Your Development Key"));
	m_leanplum.SetDataExportKey(_T("Your Data Export Key"));
	m_leanplum.SetContentReadonlyKey(_T("Your Content Read-only Key"));
	// initialize Ids
	m_userId = 1;
	m_deviceId = 1;
	// initial leanplum
	DefineLeanplumVariables();
	RunLeanplum();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CLeanplumDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CLeanplumDemoDlg::OnPaint()
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
HCURSOR CLeanplumDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CLeanplumDemoDlg::OnBnClickedButton3()
{
	GetDlgItem(IDC_BTN_SHOP)->ShowWindow(FALSE);
	GetDlgItem(IDC_BUTTON2)->ShowWindow(FALSE);
	GetDeviceId();
	GetUserId();
	RunLeanplum();
}

void CLeanplumDemoDlg::OnBnClickedButton2()
{
	//AfxMessageBox(m_byeMsg);
	ShopVerADlg dlg;
	dlg.DoModal();
}

void CLeanplumDemoDlg::OnBnClickedBtnShop()
{
	//AfxMessageBox(m_byeMsg);
	ShopVerBDlg dlg;
	dlg.DoModal();
}
