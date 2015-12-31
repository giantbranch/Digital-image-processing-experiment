// ljz153View.cpp : implementation of the CLjz153View class
//

#include "stdafx.h"
#include "ljz153.h"

#include "ljz153Doc.h"
#include "ljz153View.h"

#include "Dialog_Grey.h"
#include "Dlg_Low.h"
#include "Dlg_High.h"
#include "MoveDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLjz153View

IMPLEMENT_DYNCREATE(CLjz153View, CScrollView)

BEGIN_MESSAGE_MAP(CLjz153View, CScrollView)
	//{{AFX_MSG_MAP(CLjz153View)
	ON_COMMAND(ID_GREY, OnGrey)
	ON_UPDATE_COMMAND_UI(ID_GREY, OnUpdateGrey)
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_GREY_STATIS, OnGreyStatis)
	ON_COMMAND(IDT_PIC1, OnPic1)
	ON_COMMAND(IDT_PIC2, OnPic2)
	ON_COMMAND(IDM_FT, OnFt)
	ON_COMMAND(IDM_FFT, OnFft)
	ON_UPDATE_COMMAND_UI(IDM_FFT, OnUpdateFft)
	ON_COMMAND(IDM_IFFT, OnIfft)
	ON_UPDATE_COMMAND_UI(IDM_IFFT, OnUpdateIfft)
	ON_COMMAND(IDM_IFT, OnIft)
	ON_COMMAND(ID_AVERAGE_FILTER, OnAverageFilter)
	ON_UPDATE_COMMAND_UI(ID_AVERAGE_FILTER, OnUpdateAverageFilter)
	ON_COMMAND(ID_MEDIAN_FILTER, OnMedianFilter)
	ON_UPDATE_COMMAND_UI(ID_MEDIAN_FILTER, OnUpdateMedianFilter)
	ON_COMMAND(ID_GRAD_SHARP, OnGradSharp)
	ON_UPDATE_COMMAND_UI(ID_GRAD_SHARP, OnUpdateGradSharp)
	ON_COMMAND(ID_RAPLAS_SHARP, OnRaplasSharp)
	ON_UPDATE_COMMAND_UI(ID_RAPLAS_SHARP, OnUpdateRaplasSharp)
	ON_COMMAND(IDM_LOW, OnLow)
	ON_UPDATE_COMMAND_UI(IDM_LOW, OnUpdateLow)
	ON_UPDATE_COMMAND_UI(IDM_HIGH, OnUpdateHigh)
	ON_COMMAND(IDM_HIGH, OnHigh)
	ON_COMMAND(IDM_MOVE, OnMove)
	ON_COMMAND(IDM_LINE, OnLine)
	ON_COMMAND(IDM_EQUAL, OnEqual)
	ON_COMMAND(IDM_BPF, OnBpf)
	ON_COMMAND(IDM_BHPF, OnBhpf)
	ON_UPDATE_COMMAND_UI(IDM_FT, OnUpdateFt)
	ON_UPDATE_COMMAND_UI(IDM_IFT, OnUpdateIft)
	ON_UPDATE_COMMAND_UI(IDM_BHPF, OnUpdateBhpf)
	ON_UPDATE_COMMAND_UI(IDM_BPF, OnUpdateBpf)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLjz153View construction/destruction

CLjz153View::CLjz153View()
{
	// TODO: add construction code here

}

CLjz153View::~CLjz153View()
{
}

BOOL CLjz153View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CLjz153View drawing
extern LPBITMAPINFO   lpBitsInfo;
extern LPBITMAPINFO   lpBitsInfo1;
extern BITMAPINFO *lpDIB_FFT;
extern BITMAPINFO *lpDIB_IFFT;
void CLjz153View::OnDraw(CDC* pDC)
{
	CLjz153Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	if (NULL != lpBitsInfo){
		LPVOID lpBits = (LPVOID)&lpBitsInfo ->bmiColors[lpBitsInfo ->bmiHeader.biClrUsed];
		StretchDIBits (pDC->GetSafeHdc(), 
			0, 0, lpBitsInfo->bmiHeader.biWidth, lpBitsInfo->bmiHeader.biHeight,
			0, 0, lpBitsInfo->bmiHeader.biWidth, lpBitsInfo->bmiHeader.biHeight,
			lpBits, lpBitsInfo,
		DIB_RGB_COLORS, SRCCOPY);
	} 
	if (NULL != lpBitsInfo1)
	{
		LPVOID lpBits1 = (LPVOID)&lpBitsInfo1 ->bmiColors[lpBitsInfo1 ->bmiHeader.biClrUsed];
		StretchDIBits (pDC->GetSafeHdc(), 
			lpBitsInfo->bmiHeader.biWidth + 50, 0, lpBitsInfo1->bmiHeader.biWidth, lpBitsInfo1->bmiHeader.biHeight,
			0, 0, lpBitsInfo1->bmiHeader.biWidth, lpBitsInfo1->bmiHeader.biHeight,
			lpBits1, lpBitsInfo1,
		DIB_RGB_COLORS, SRCCOPY);
	}

	
	
	if (lpDIB_FFT)
	{
		LPVOID lpBits = (LPVOID)&lpDIB_FFT->bmiColors[lpDIB_FFT->bmiHeader.biClrUsed];
		StretchDIBits( 
			pDC->GetSafeHdc(),
			600,0,
			lpDIB_FFT->bmiHeader.biWidth,
			lpDIB_FFT->bmiHeader.biHeight,
			0,0,
			lpDIB_FFT->bmiHeader.biWidth,
			lpDIB_FFT->bmiHeader.biHeight,
			lpBits,
			lpDIB_FFT, // bitmap data 
			DIB_RGB_COLORS,
			SRCCOPY);
		
	}

	if (lpDIB_IFFT)
	{
		LPVOID lpBits = (LPVOID)&lpDIB_IFFT->bmiColors[lpDIB_IFFT->bmiHeader.biClrUsed];
		StretchDIBits( 
			pDC->GetSafeHdc(),
			600,600,
			lpDIB_IFFT->bmiHeader.biWidth,
			lpDIB_IFFT->bmiHeader.biHeight,
			0,0,
			lpDIB_IFFT->bmiHeader.biWidth,
			lpDIB_IFFT->bmiHeader.biHeight,
			lpBits,
			lpDIB_IFFT, // bitmap data 
			DIB_RGB_COLORS,
			SRCCOPY);
	}
	return;
}

void CLjz153View::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: calculate the total size of this view
	sizeTotal.cx = 1500;
	sizeTotal.cy = 2000;
	SetScrollSizes(MM_TEXT, sizeTotal);
}

/////////////////////////////////////////////////////////////////////////////
// CLjz153View printing

BOOL CLjz153View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CLjz153View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CLjz153View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CLjz153View diagnostics

#ifdef _DEBUG
void CLjz153View::AssertValid() const
{
	CScrollView::AssertValid();
}

void CLjz153View::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CLjz153Doc* CLjz153View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLjz153Doc)));
	return (CLjz153Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLjz153View message handlers
void Gray();
void CLjz153View::OnGrey() 
{
	// TODO: Add your command handler code here
	Gray();
	Invalidate();
}

void CLjz153View::OnUpdateGrey(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(lpBitsInfo != NULL);
}
void ShowDetail(CPoint point);
extern int picNum;
void CLjz153View::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
//	if (picNum != 0)
//	{
//		
//	}else{
//		AfxMessageBox("没有图像");
// 	}
	ShowDetail(point);
	CScrollView::OnLButtonDown(nFlags, point);
}


void CLjz153View::OnGreyStatis() 
{
	// TODO: Add your command handler code here
	Dialog_Grey dlg;
	dlg.DoModal();
}
LPBITMAPINFO LoadBmpFile (char*);
extern int picNum;
void CLjz153View::OnPic1() 
{
	// TODO: Add your command handler code here
	CFileDialog pic1( TRUE, _T( ".bmp" ), _T( "test.bmp" ), OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, _T( "应用程序(bmp)|*.bmp|所有文件|*||" ) );
	if ( pic1.DoModal() == IDOK ) 
	{
		CString path = pic1.GetPathName();	//获取路径
		//AfxMessageBox(path);
		char* name = path.GetBuffer(path.GetLength());
		path.ReleaseBuffer();
		lpBitsInfo = LoadBmpFile(name);
		Invalidate();
		picNum++;
	}
}

void CLjz153View::OnPic2() 
{
	// TODO: Add your command handler code here
	CFileDialog pic2( TRUE, _T( ".bmp" ), _T( "test.bmp" ), OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, _T( "图片(bmp)|*.bmp|所有文件|*||" ) );
	if ( pic2.DoModal() == IDOK ) 
	{
		CString path = pic2.GetPathName();	//获取路径
		//AfxMessageBox(path);
		char* name = path.GetBuffer(path.GetLength());
		path.ReleaseBuffer();
		lpBitsInfo1 = LoadBmpFile(name);
		Invalidate();
		picNum++;
	}
}

void lowFourier();
//傅里叶变换
void CLjz153View::OnFt() 
{
	// TODO: Add your command handler code here
	lowFourier();
	Invalidate();

}

void lowIFourier();
void CLjz153View::OnIft() 
{
	// TODO: Add your command handler code here
	lowIFourier();
	Invalidate();
}


void Fourier();
void CLjz153View::OnFft() 
{
	// TODO: Add your command handler code here
	if (lpDIB_FFT)
		free(lpDIB_FFT);
	lpDIB_IFFT = NULL;
	Fourier();
	Invalidate();

	
}



void CLjz153View::OnUpdateFft(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(lpBitsInfo != NULL && lpBitsInfo->bmiHeader.biBitCount == 8);
}
void IFourier();
void CLjz153View::OnIfft() 
{
	// TODO: Add your command handler code here
	if (lpDIB_IFFT)
		free(lpDIB_IFFT);

	IFourier();
	Invalidate();
}

void CLjz153View::OnUpdateIfft(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(lpDIB_FFT != NULL);
}
//声明
void AverageFilter();
void MedianFilter();
void GradSharp();
void RaplasSharp();

void CLjz153View::OnAverageFilter() 
{
	// TODO: Add your command handler code here
	AverageFilter();
	Invalidate();
}

void CLjz153View::OnUpdateAverageFilter(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(lpBitsInfo != NULL);
}

void CLjz153View::OnMedianFilter() 
{
	// TODO: Add your command handler code here
	MedianFilter();
	Invalidate();
}

void CLjz153View::OnUpdateMedianFilter(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(lpBitsInfo != NULL);
}

void CLjz153View::OnGradSharp() 
{
	// TODO: Add your command handler code here
	GradSharp();
	Invalidate();
}

void CLjz153View::OnUpdateGradSharp(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(lpBitsInfo != NULL);
}

void CLjz153View::OnRaplasSharp() 
{
	// TODO: Add your command handler code here
	RaplasSharp();
	Invalidate();
}

void CLjz153View::OnUpdateRaplasSharp(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(lpBitsInfo != NULL);
}

int radius = 10;
void Ideal_Filter_FFT(int D);
void BLPF_Filter_FFT(int D);
void CLjz153View::OnLow() 
{
	// TODO: Add your command handler code here
	Dlg_Low dlg_low;
	dlg_low.DoModal();
	Ideal_Filter_FFT(radius);
	Invalidate();
	
}

void CLjz153View::OnUpdateLow(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(lpDIB_FFT != NULL);
}

void CLjz153View::OnUpdateHigh(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(lpDIB_FFT != NULL);
}

void CLjz153View::OnHigh() 
{
	// TODO: Add your command handler code here
	Dlg_High dlg_high;
	dlg_high.DoModal();
	Ideal_Filter_FFT(radius);
	Invalidate();
}

void CLjz153View::OnMove() 
{
	// TODO: Add your command handler code here
	MoveDlg Mdlg;
	Mdlg.DoModal();
}


void linearity();
void equalization();
void CLjz153View::OnLine() 
{
	// TODO: Add your command handler code here
	linearity();
	Invalidate();
}

void CLjz153View::OnEqual() 
{
	// TODO: Add your command handler code here
	equalization();
	Invalidate();
}

void CLjz153View::OnBpf() 
{
	// TODO: Add your command handler code here
	Dlg_Low dlg_low;
	dlg_low.DoModal();
	BLPF_Filter_FFT(radius);
	Invalidate();
}

void CLjz153View::OnBhpf() 
{
	// TODO: Add your command handler code here
	Dlg_High dlg_high;
	dlg_high.DoModal();
	BLPF_Filter_FFT(radius);
	Invalidate();
}

void CLjz153View::OnUpdateFt(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(lpBitsInfo != NULL);
}

void CLjz153View::OnUpdateIft(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(lpBitsInfo != NULL);
}

void CLjz153View::OnUpdateBhpf(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(lpDIB_FFT != NULL);
}

void CLjz153View::OnUpdateBpf(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(lpDIB_FFT != NULL);
}
