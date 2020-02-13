
#ifndef __EDITOR_ACTION_STATIC_MESH_ADD_H_
#define __EDITOR_ACTION_STATIC_MESH_ADD_H_


#include "libEngine.h"
#include "libEditor.h"
#include "EditorAction.h"


class EditorAction_StaticMesh_Add : public EditorAction
{
public:
  EditorAction_StaticMesh_Add();
  virtual ~EditorAction_StaticMesh_Add();

  virtual bool Init(const String &nodePath);

  virtual void SetParameter(const String &paramName, const Vec3 &paramValue);

  virtual bool Complete();
  virtual void Discard();

  virtual void Update();

private:
  String  m_Node;
  String  m_Filename;
  Vec3    m_Pos;
  Vec3    m_Rot;
  Vec3    m_Scale;

};


#endif // __EDITOR_ACTION_STATIC_MESH_ADD_H_

// -- EOF

