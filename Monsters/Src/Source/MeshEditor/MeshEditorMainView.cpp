// ----------------------------------------------------------------------------
// File: MeshEditorMainView.cpp
// Desc: The main view
// Auth: Michael Petrou
// (C) Copyright: 2006
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// Includes
// ----------------------------------------------------------------------------
#include "MeshEditor/MeshEditorModule.h"
#include "MeshEditor/MeshEditorMainView.h"
#include "MeshEditor/MeshEditorMainDoc.h"
#include "MeshEditor/Resource.h"


IMPLEMENT_DYNCREATE(MeshEditorMainView, CView)


BEGIN_MESSAGE_MAP(MeshEditorMainView, CView)
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


MeshEditorMainView::MeshEditorMainView()
{
} // MeshEditorMainView


MeshEditorMainView::~MeshEditorMainView()
{
} // ~MeshEditorMainView


BOOL MeshEditorMainView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
} // MeshEditorMainView


void MeshEditorMainView::OnDraw(CDC *pDC)
{
  pDC->FillRect(&CRect(0, 0, 2000, 2000), &CBrush(0x4f4f4f));
  UpdateWindow();
} // OnDraw


BOOL MeshEditorMainView::OnPreparePrinting(CPrintInfo *pInfo)
{
	return DoPreparePrinting(pInfo);
} // OnPreparePrinting


void MeshEditorMainView::OnBeginPrinting(CDC *pDC, CPrintInfo *pInfo)
{
} // OnBeginPrinting


void MeshEditorMainView::OnEndPrinting(CDC *pDC, CPrintInfo *pInfo)
{
} // OnEndPrinting


MeshEditorMainDoc *MeshEditorMainView::GetDocument() const
{
  return reinterpret_cast<MeshEditorMainDoc *>(m_pDocument);
} // GetDocument


void MeshEditorMainView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

  MFCDisplay::SetWnd(this);
  ApplicationCentral.Init(GetSafeHwnd(), MFCDisplay::GetModule());
} // OnInitialUpdate


void MeshEditorMainView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

  ApplicationCentral.ResizeDisplay();
} // OnSize


BOOL MeshEditorMainView::OnEraseBkgnd(CDC *pDC)
{
	return FALSE;
} // OnEraseBkgnd


// -- EOF

