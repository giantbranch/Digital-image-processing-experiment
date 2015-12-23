#if !defined(AFX_DLG_LOW_H__1371F57A_5BA9_4E0D_9834_21A842439D15__INCLUDED_)
#define AFX_DLG_LOW_H__1371F57A_5BA9_4E0D_9834_21A842439D15__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlg_Low.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Dlg_Low dialog

class Dlg_Low : public CDialog
{
// Construction
public:
	Dlg_Low(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Dlg_Low)
	enum { IDD = IDD_DIALOG_LOW };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Dlg_Low)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Dlg_Low)
	virtual BOOL OnInitDialog();
	afx_msg void OnOk2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_LOW_H__1371F57A_5BA9_4E0D_9834_21A842439D15__INCLUDED_)
