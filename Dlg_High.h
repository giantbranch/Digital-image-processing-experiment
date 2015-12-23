#if !defined(AFX_DLG_HIGH_H__A39711DD_5681_47F0_98B1_ED10A68CDAA4__INCLUDED_)
#define AFX_DLG_HIGH_H__A39711DD_5681_47F0_98B1_ED10A68CDAA4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlg_High.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Dlg_High dialog

class Dlg_High : public CDialog
{
// Construction
public:
	Dlg_High(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Dlg_High)
	enum { IDD = IDD_DIALOG_HIGH };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Dlg_High)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Dlg_High)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_HIGH_H__A39711DD_5681_47F0_98B1_ED10A68CDAA4__INCLUDED_)
