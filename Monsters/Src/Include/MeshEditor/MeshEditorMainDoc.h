// ----------------------------------------------------------------------------
// File: MeshEditorMainDoc.h
// Desc: The main document
// Auth: Michael Petrou
// (C) Copyright: 2006
// ----------------------------------------------------------------------------
#ifndef __MESH_EDITOR_MAIN_DOC_H_
#define __MESH_EDITOR_MAIN_DOC_H_


// ----------------------------------------------------------------------------
// Includes
// ----------------------------------------------------------------------------
#include "Engine/EngineInc.h"


class MeshEditorMainDoc : public CDocument
{
protected:
  MeshEditorMainDoc();
  virtual ~MeshEditorMainDoc();
  DECLARE_DYNCREATE(MeshEditorMainDoc)

public:
  virtual BOOL OnNewDocument();
  virtual void Serialize(CArchive& ar);

protected:
  DECLARE_MESSAGE_MAP()

}; // MeshEditorMainDoc


#endif // __MESH_EDITOR_MAIN_DOC_H_

// -- EOF