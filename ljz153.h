// ljz153.h : main header file for the LJZ153 application
//

#if !defined(AFX_LJZ153_H__A3211C9A_A33F_42F2_909E_4A5A529EC6B3__INCLUDED_)
#define AFX_LJZ153_H__A3211C9A_A33F_42F2_909E_4A5A529EC6B3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CLjz153App:
// See ljz153.cpp for the implementation of this class
//

class CLjz153App : public CWinApp
{
public:
	CLjz153App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLjz153App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CLjz153App)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LJZ153_H__A3211C9A_A33F_42F2_909E_4A5A529EC6B3__INCLUDED_)
