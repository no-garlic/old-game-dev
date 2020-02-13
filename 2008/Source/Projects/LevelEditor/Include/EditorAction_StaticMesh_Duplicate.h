
#ifndef __EDITOR_ACTION_STATIC_MESH_DUPLICATE_H_
#define __EDITOR_ACTION_STATIC_MESH_DUPLICATE_H_


#include "libEngine.h"
#include "libEditor.h"
#include "EditorAction.h"


class EditorAction_StaticMesh_Duplicate : public EditorAction
{
public:
  EditorAction_StaticMesh_Duplicate();
  virtual ~EditorAction_StaticMesh_Duplicate();

  virtual bool Init(const String &nodePath);

  virtual void SetParameter(const String &paramName, const String &paramValue);

  virtual bool Complete();
  virtual void Discard();

  virtual void Update();

private:
  String  m_SrcNode;
  String  m_DstNode;
};


#endif // __EDITOR_ACTION_STATIC_MESH_DUPLICATE_H_

// -- EOF

