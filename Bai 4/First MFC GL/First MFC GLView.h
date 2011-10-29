// First MFC GLView.h : interface of the CFirstMFCGLView class
//


#pragma once


class CFirstMFCGLView : public CView
{
protected: // create from serialization only
	CFirstMFCGLView();
	DECLARE_DYNCREATE(CFirstMFCGLView)

// Attributes
public:
	CFirstMFCGLDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CFirstMFCGLView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDestroy();
};

#ifndef _DEBUG  // debug version in First MFC GLView.cpp
inline CFirstMFCGLDoc* CFirstMFCGLView::GetDocument() const
   { return reinterpret_cast<CFirstMFCGLDoc*>(m_pDocument); }
#endif

