// ljz153Doc.h : interface of the CLjz153Doc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_LJZ153DOC_H__2BA5B7A9_B61E_475C_8DAB_A1607A8558F8__INCLUDED_)
#define AFX_LJZ153DOC_H__2BA5B7A9_B61E_475C_8DAB_A1607A8558F8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CLjz153Doc : public CDocument
{
protected: // create from serialization only
	CLjz153Doc();
	DECLARE_DYNCREATE(CLjz153Doc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLjz153Doc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CLjz153Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CLjz153Doc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LJZ153DOC_H__2BA5B7A9_B61E_475C_8DAB_A1607A8558F8__INCLUDED_)
