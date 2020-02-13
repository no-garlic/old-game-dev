
#ifndef __UNDO_ACTION_STATIC_MESH_TRANSFORM_H_
#define __UNDO_ACTION_STATIC_MESH_TRANSFORM_H_


#include "libEngine.h"
#include "libEditor.h"
#include "UndoManager.h"


class UndoAction_StaticMesh_Transform : public UndoAction
{
public:
  UndoAction_StaticMesh_Transform();
  virtual ~UndoAction_StaticMesh_Transform();

  void SetNode(const String &path);
  void SetFrom(const Vec3 &pos, const Vec3 &rot, const Vec3 &scale);
  void SetTo(const Vec3 &pos, const Vec3 &rot, const Vec3 &scale);

  virtual void Undo();
  virtual void Redo();

private:
  String  m_Node;
  Vec3    m_FromPos;
  Vec3    m_FromRot;
  Vec3    m_FromScale;
  Vec3    m_ToPos;
  Vec3    m_ToRot;
  Vec3    m_ToScale;

};


#endif // __UNDO_ACTION_STATIC_MESH_TRANSFORM_H_

// -- EOf

