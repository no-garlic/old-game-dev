// ----------------------------------------------------------------------------
// File: MeshEditorMainView.h
// Desc: The main view
// Auth: Michael Petrou
// (C) Copyright: 2006
// ----------------------------------------------------------------------------
#ifndef __MESH_EDITOR_MAIN_VIEW_H_
#define __MESH_EDITOR_MAIN_VIEW_H_


// ----------------------------------------------------------------------------
// Includes
// ----------------------------------------------------------------------------
#include "Engine/EngineInc.h"


class MeshEditorMainDoc;


class MeshEditorMainView : public CView
{
protected:
  MeshEditorMainView();
  virtual ~MeshEditorMainView();
  DECLARE_DYNCREATE(MeshEditorMainView)

  MeshEditorMainDoc *GetDocument() const;

public:
  virtual void OnDraw(CDC *pDC);
  virtual void OnInitialUpdate();
  virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

protected:
  virtual BOOL OnPreparePrinting(CPrintInfo *pInfo);
  virtual void OnBeginPrinting(CDC *pDC, CPrintInfo *pInfo);
  virtual void OnEndPrinting(CDC *pDC, CPrintInfo *pInfo);

protected:
  DECLARE_MESSAGE_MAP()

public:
  afx_msg void OnSize(UINT nType, int cx, int cy);
  afx_msg BOOL OnEraseBkgnd(CDC* pDC);

}; // MeshEditorMainView


#endif // __MESH_EDITOR_MAIN_VIEW_H_

// -- EOF