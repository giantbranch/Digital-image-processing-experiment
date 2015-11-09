#if !defined(AFX_DIALOG_GREY_H__FE850591_312A_4B5D_8A7B_F0D555D98091__INCLUDED_)
#define AFX_DIALOG_GREY_H__FE850591_312A_4B5D_8A7B_F0D555D98091__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dialog_Grey.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Dialog_Grey dialog

class Dialog_Grey : public CDialog
{
// Construction
public:
	Dialog_Grey(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Dialog_Grey)
	enum { IDD = IDD_DIALOG_GREY_STATICS };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Dialog_Grey)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Dialog_Grey)
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOG_GREY_H__FE850591_312A_4B5D_8A7B_F0D555D98091__INCLUDED_)
