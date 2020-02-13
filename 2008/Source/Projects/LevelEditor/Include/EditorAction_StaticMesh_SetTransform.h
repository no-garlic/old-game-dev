
#ifndef __EDITOR_ACTION_STATIC_MESH_SET_TRANSFORM_H_
#define __EDITOR_ACTION_STATIC_MESH_SET_TRANSFORM_H_


#include "libEngine.h"
#include "libEditor.h"
#include "EditorAction.h"


class EditorAction_StaticMesh_SetTransform: public EditorAction
{
public:
  EditorAction_StaticMesh_SetTransform();
  virtual ~EditorAction_StaticMesh_SetTransform();

  virtual bool Init(const String &nodePath);

  virtual void SetParameter(const String &paramName, const Vec3 &paramValue);

  virtual bool Complete();
  virtual void Discard();

  virtual void Update();

private:
  String  m_Node;
  Vec3    m_Pos;
  Vec3    m_Rot;
  Vec3    m_Scale;
  Vec3    m_OldPos;
  Vec3    m_OldRot;
  Vec3    m_OldScale;

};


#endif // __EDITOR_ACTION_STATIC_MESH_SET_TRANSFORM_H_

// -- EOF

