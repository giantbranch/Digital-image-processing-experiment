// ljz153Doc.cpp : implementation of the CLjz153Doc class
//

#include "stdafx.h"
#include "ljz153.h"

#include "ljz153Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLjz153Doc

IMPLEMENT_DYNCREATE(CLjz153Doc, CDocument)

BEGIN_MESSAGE_MAP(CLjz153Doc, CDocument)
	//{{AFX_MSG_MAP(CLjz153Doc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLjz153Doc construction/destruction

CLjz153Doc::CLjz153Doc()
{
	// TODO: add one-time construction code here

}

CLjz153Doc::~CLjz153Doc()
{
}

BOOL CLjz153Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CLjz153Doc serialization

void CLjz153Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CLjz153Doc diagnostics

#ifdef _DEBUG
void CLjz153Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CLjz153Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLjz153Doc commands
BOOL LoadBmpFile (char*);
BOOL CLjz153Doc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	
	// TODO: Add your specialized creation code here
	LoadBmpFile((char*) lpszPathName);
	return TRUE;
}
