
#ifndef __EDITOR_ACTION_STATIC_MESH_RELOCATE_H_
#define __EDITOR_ACTION_STATIC_MESH_RELOCATE_H_


#include "libEngine.h"
#include "libEditor.h"
#include "EditorAction.h"


class EditorAction_StaticMesh_Relocate : public EditorAction
{
public:
  EditorAction_StaticMesh_Relocate();
  virtual ~EditorAction_StaticMesh_Relocate();

  virtual bool Init(const String &nodePath);

  virtual void SetParameter(const String &paramName, const String &paramValue);

  virtual bool Complete();
  virtual void Discard();

  virtual void Update();

private:
  String  m_SrcPath;
  String  m_DstPath;

};


#endif // __EDITOR_ACTION_STATIC_MESH_RELOCATE_H_

// -- EOF

