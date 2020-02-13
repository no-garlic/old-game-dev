
#ifndef __EDITOR_ACTION_STATIC_MESH_RENAME_H_
#define __EDITOR_ACTION_STATIC_MESH_RENAME_H_


#include "libEngine.h"
#include "libEditor.h"
#include "EditorAction.h"


class EditorAction_StaticMesh_Rename : public EditorAction
{
public:
  EditorAction_StaticMesh_Rename();
  virtual ~EditorAction_StaticMesh_Rename();

  virtual bool Init(const String &nodePath);

  virtual void SetParameter(const String &paramName, const String &paramValue);

  virtual bool Complete();
  virtual void Discard();

  virtual void Update();

private:
  String m_Node;
  String m_Name;

};


#endif // __EDITOR_ACTION_STATIC_MESH_RENAME_H_

// -- EOF

