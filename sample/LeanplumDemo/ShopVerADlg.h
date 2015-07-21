#pragma once


// ShopVerADlg dialog

class ShopVerADlg : public CDialogEx
{
	DECLARE_DYNAMIC(ShopVerADlg)

public:
	ShopVerADlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~ShopVerADlg();

// Dialog Data
	// Generated message map functions
	virtual BOOL OnInitDialog();
	enum { IDD = IDD_SHOPVERADLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
