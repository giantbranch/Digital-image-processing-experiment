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

int statistics[256];	//����ͳ������
void Dialog_Grey::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	//y��
	CDC *pDC=GetDC();
	pDC->MoveTo(50,354);      
	pDC->LineTo(50,0);
	//x��
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

extern LPBITMAPINFO   lpBitsInfo;
BOOL Dialog_Grey::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	

	int w = lpBitsInfo->bmiHeader.biWidth;
	int h = lpBitsInfo->bmiHeader.biHeight;
	int LineBytes = (w * lpBitsInfo->bmiHeader.biBitCount + 31)/32 * 4;	//ÿ���ֽ�
	BYTE* lpBits = (BYTE*)&lpBitsInfo->bmiColors[lpBitsInfo->bmiHeader.biClrUsed];	//ʵ��λͼ����
	
	//��ʼ��ͳ������
	for (int k = 0; k<256 ;k++)
	{
		statistics[k] = 0;
	}

	
	BYTE* Pixel;	//����ָ��
	int R;
	for (int i = 0; i <=h ; i++)
	{
		for (int j = 0; j < w; j++)
		{
			Pixel = lpBits + LineBytes*i +j;
			R = lpBitsInfo->bmiColors[*Pixel].rgbRed;	//��ΪΪ256��ɫ����ȡ����һ��ֵ����
			statistics[R]++;
		}
	}

	//���Թ��̣��ҳ����ֵ���Ա㻭ͼʱȷ���߶ȵı���
	/*
	int maxNum = 0;
	CString str = "",a,b;
	for (i = 0; i<256; i++)
	{
		//a.Format("%d: ",i);
		//b.Format("%d; ",statistics[i]);
		//str = str + a + b;
		maxNum =  statistics[i]>maxNum?statistics[i]:maxNum;
	}
	str.Format("%d",maxNum);
	//AfxMessageBox(str);
	*/

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
