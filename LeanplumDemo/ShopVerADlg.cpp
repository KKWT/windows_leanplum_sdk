// ShopVerADlg.cpp : implementation file
//

#include "stdafx.h"
#include "LeanplumDemo.h"
#include "ShopVerADlg.h"
#include "afxdialogex.h"


// ShopVerADlg dialog

IMPLEMENT_DYNAMIC(ShopVerADlg, CDialogEx)

ShopVerADlg::ShopVerADlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(ShopVerADlg::IDD, pParent)
{
}

ShopVerADlg::~ShopVerADlg()
{
}

BOOL ShopVerADlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CBitmap Bitmap;
	CPngImage image;
	image.Load(IDB_PNG_711);
	Bitmap.Attach(image.Detach());
	HBITMAP hBitmap=(HBITMAP)Bitmap.Detach();
	CButton *pButton=(CButton*)GetDlgItem(IDC_BTN_711);
	pButton->SetBitmap(hBitmap); 
	image.Load(IDB_PNG_FAMI);
	Bitmap.Attach(image.Detach());

	hBitmap=(HBITMAP)Bitmap.Detach();
	pButton=(CButton*)GetDlgItem(IDC_BTN_FAMI);
	pButton->SetBitmap(hBitmap); 
	image.Load(IDB_PNG_CARD);
	Bitmap.Attach(image.Detach());

	hBitmap=(HBITMAP)Bitmap.Detach();
	pButton=(CButton*)GetDlgItem(IDC_BTN_MYCARD);
	pButton->SetBitmap(hBitmap); 
	image.Load(IDB_PNG_KKCARD);
	Bitmap.Attach(image.Detach());

	hBitmap=(HBITMAP)Bitmap.Detach();
	pButton=(CButton*)GetDlgItem(IDC_BTN_KKCARD);
	pButton->SetBitmap(hBitmap); 

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void ShopVerADlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ShopVerADlg, CDialogEx)
END_MESSAGE_MAP()


// ShopVerADlg message handlers
