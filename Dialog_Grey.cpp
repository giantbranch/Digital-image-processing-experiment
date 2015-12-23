// Dialog_Grey.cpp : implementation file
//

#include "stdafx.h"
#include "ljz153.h"
#include "Dialog_Grey.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialog_Grey dialog


Dialog_Grey::Dialog_Grey(CWnd* pParent /*=NULL*/)
	: CDialog(Dialog_Grey::IDD, pParent)
{
	//{{AFX_DATA_INIT(Dialog_Grey)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void Dialog_Grey::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Dialog_Grey)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Dialog_Grey, CDialog)
	//{{AFX_MSG_MAP(Dialog_Grey)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Dialog_Grey message handlers

extern int statistics[256];	//储存统计数据

void Dialog_Grey::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	//y轴
	CDC *pDC=GetDC();
	pDC->MoveTo(50,354);      
	pDC->LineTo(50,0);
	//x轴
	pDC->MoveTo(50,354);      
	pDC->LineTo(608,354);
	ReleaseDC(pDC);

	// TODO: Add your message handler code here
	int x;
	for (int i = 0;i < 256 ;i++)
	{
		CDC *pDC=GetDC();
		x = i+4+50;
		pDC->MoveTo(x,354);      
		pDC->LineTo(x,354-statistics[i]*0.1);
		ReleaseDC(pDC);
	}
	// Do not call CDialog::OnPaint() for painting messages
}

void GrayStatistics ();
BOOL Dialog_Grey::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	GrayStatistics();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
