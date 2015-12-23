// Dlg_High.cpp : implementation file
//

#include "stdafx.h"
#include "ljz153.h"
#include "Dlg_High.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dlg_High dialog


Dlg_High::Dlg_High(CWnd* pParent /*=NULL*/)
	: CDialog(Dlg_High::IDD, pParent)
{
	//{{AFX_DATA_INIT(Dlg_High)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void Dlg_High::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Dlg_High)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Dlg_High, CDialog)
	//{{AFX_MSG_MAP(Dlg_High)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Dlg_High message handlers
extern int radius;
void Dlg_High::OnOK() 
{
	// TODO: Add extra validation here

	radius = GetDlgItemInt(IDC_EDIT_HIGH);
	radius = -radius;
	CDialog::OnOK();
}
