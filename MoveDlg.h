#if !defined(AFX_MOVEDLG_H__1B346B0B_F9EE_4F64_AE6E_C06DFC3790C1__INCLUDED_)
#define AFX_MOVEDLG_H__1B346B0B_F9EE_4F64_AE6E_C06DFC3790C1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MoveDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// MoveDlg dialog

class MoveDlg : public CDialog
{
// Construction
public:
	MoveDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(MoveDlg)
	enum { IDD = IDD_DIALOG1 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(MoveDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(MoveDlg)
	afx_msg void OnOkmove();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MOVEDLG_H__1B346B0B_F9EE_4F64_AE6E_C06DFC3790C1__INCLUDED_)
