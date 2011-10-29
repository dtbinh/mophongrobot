// First MFC GLDoc.cpp : implementation of the CFirstMFCGLDoc class
//

#include "stdafx.h"
#include "First MFC GL.h"

#include "First MFC GLDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#pragma warning ( disable : 4566 )

// CFirstMFCGLDoc

IMPLEMENT_DYNCREATE(CFirstMFCGLDoc, CDocument)

BEGIN_MESSAGE_MAP(CFirstMFCGLDoc, CDocument)
END_MESSAGE_MAP()


// CFirstMFCGLDoc construction/destruction

CFirstMFCGLDoc::CFirstMFCGLDoc()
{
	// TODO: add one-time construction code here

}

CFirstMFCGLDoc::~CFirstMFCGLDoc()
{
}

BOOL CFirstMFCGLDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CFirstMFCGLDoc serialization

void CFirstMFCGLDoc::Serialize(CArchive& ar)
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


// CFirstMFCGLDoc diagnostics

#ifdef _DEBUG
void CFirstMFCGLDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CFirstMFCGLDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CFirstMFCGLDoc commands
