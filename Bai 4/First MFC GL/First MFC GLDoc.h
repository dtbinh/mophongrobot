// First MFC GLDoc.h : interface of the CFirstMFCGLDoc class
//


#pragma once


class CFirstMFCGLDoc : public CDocument
{
protected: // create from serialization only
	CFirstMFCGLDoc();
	DECLARE_DYNCREATE(CFirstMFCGLDoc)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Implementation
public:
	virtual ~CFirstMFCGLDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};


