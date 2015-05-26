#pragma once


// ShopVerBDlg dialog

class ShopVerBDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ShopVerBDlg)

public:
	ShopVerBDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~ShopVerBDlg();

// Dialog Data
	enum { IDD = IDD_SHOPVERBDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
