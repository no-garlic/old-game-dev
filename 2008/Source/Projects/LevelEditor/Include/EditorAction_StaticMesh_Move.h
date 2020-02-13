
#ifndef __EDITOR_ACTION_STATIC_MESH_MOVE_H_
#define __EDITOR_ACTION_STATIC_MESH_MOVE_H_


#include "libEngine.h"
#include "libEditor.h"
#include "EditorAction.h"
#include "StaticMeshNode.h"


class EditorAction_StaticMesh_Move : public EditorAction
{
public:
  EditorAction_StaticMesh_Move();
  virtual ~EditorAction_StaticMesh_Move();

  virtual bool Init(const String &nodePath);

  virtual bool Complete();
  virtual void Discard();

  virtual void Update();

private:
  StaticMeshNode *m_pOrigNode;
  StaticMeshNode *m_pNode;
  Vec3            m_Pos;
  Vec3            m_Rot;
  Vec3            m_Scale;
  POINT           m_StartPoint;
  POINT           m_LastPoint;
  Plane           m_Plane;
  Vec3            m_PlaneInitPos;
  bool            m_Duplicate;

};


#endif // __EDITOR_ACTION_STATIC_MESH_MOVE_H_

// -- EOF

