// MoveDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ljz153.h"
#include "MoveDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// MoveDlg dialog


MoveDlg::MoveDlg(CWnd* pParent /*=NULL*/)
	: CDialog(MoveDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(MoveDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void MoveDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(MoveDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(MoveDlg, CDialog)
	//{{AFX_MSG_MAP(MoveDlg)
	ON_BN_CLICKED(IDOKMOVE, OnOkmove)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// MoveDlg message handlers
void MovePic(int x, int y);
void MoveDlg::OnOkmove() 
{
	// TODO: Add your control notification handler code here
	CString strX,strY;  
	GetDlgItem(IDC_EDIT_MOVE_X)->GetWindowText(strX);
	GetDlgItem(IDC_EDIT_MOVE_Y)->GetWindowText(strY);
	int x = _ttoi(strX);
	int y = _ttoi(strY);
	MovePic(x,y);
	
}
