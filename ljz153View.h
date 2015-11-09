// ljz153View.h : interface of the CLjz153View class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_LJZ153VIEW_H__1AF180B7_0447_4A62_AA5E_57E07B58DB93__INCLUDED_)
#define AFX_LJZ153VIEW_H__1AF180B7_0447_4A62_AA5E_57E07B58DB93__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CLjz153View : public CScrollView
{
protected: // create from serialization only
	CLjz153View();
	DECLARE_DYNCREATE(CLjz153View)

// Attributes
public:
	CLjz153Doc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLjz153View)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CLjz153View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CLjz153View)
	afx_msg void OnGrey();
	afx_msg void OnUpdateGrey(CCmdUI* pCmdUI);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnGreyStatis();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ljz153View.cpp
inline CLjz153Doc* CLjz153View::GetDocument()
   { return (CLjz153Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LJZ153VIEW_H__1AF180B7_0447_4A62_AA5E_57E07B58DB93__INCLUDED_)
