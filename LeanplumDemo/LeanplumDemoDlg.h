
// LeanplumDemoDlg.h : header file
//

#pragma once
#include "InterfaceObserver.h"
#include "Leanplum.h"

// CLeanplumDemoDlg dialog
class CLeanplumDemoDlg : public CDialogEx, InterfaceObserver
{
// Construction
public:
	CLeanplumDemoDlg(CWnd* pParent = NULL);	// standard constructor
	void Notify(MessageCode::MESSAGE_CODE messageCode, WPARAM wParam = NULL, LPARAM lParam = NULL);

// Dialog Data
	enum { IDD = IDD_LEANPLUMDEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	Leanplum m_leanplum;
	CString m_helloMsg;
	CString m_byeMsg;
	int m_userId;
	int m_deviceId;
	int m_verNum;

	int GetDeviceId();
	int GetUserId();
	void DefineLeanplumVariables();
	void RunLeanplum();
	void UpdateUI();
	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedBtnShop();
};
