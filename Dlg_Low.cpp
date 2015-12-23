// Dlg_Low.cpp : implementation file
//

#include "stdafx.h"
#include "ljz153.h"
#include "Dlg_Low.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dlg_Low dialog


Dlg_Low::Dlg_Low(CWnd* pParent /*=NULL*/)
	: CDialog(Dlg_Low::IDD, pParent)
{
	//{{AFX_DATA_INIT(Dlg_Low)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void Dlg_Low::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Dlg_Low)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Dlg_Low, CDialog)
	//{{AFX_MSG_MAP(Dlg_Low)
	ON_BN_CLICKED(IDOK2, OnOk2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Dlg_Low message handlers
BOOL Dlg_Low::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
extern int radius;
void Dlg_Low::OnOk2() 
{
	// TODO: Add your control notification handler code here
	radius = GetDlgItemInt(IDC_EDIT_LOW);

	CDialog::OnOK();

}
