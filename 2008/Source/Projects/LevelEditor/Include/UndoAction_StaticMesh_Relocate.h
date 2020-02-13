
#ifndef __UNDO_ACTION_STATIC_MESH_RELOCATE_H_
#define __UNDO_ACTION_STATIC_MESH_RELOCATE_H_


#include "libEngine.h"
#include "libEditor.h"
#include "UndoManager.h"


class UndoAction_StaticMesh_Relocate : public UndoAction
{
public:
  UndoAction_StaticMesh_Relocate();
  virtual ~UndoAction_StaticMesh_Relocate();

  void SetSrcPath(const String &path);
  void SetDstPath(const String &path);

  virtual void Undo();
  virtual void Redo();

private:
  String  m_SrcPath;
  String  m_DstPath;

};


#endif // __UNDO_ACTION_STATIC_MESH_RELOCATE_H_

// -- EOf

