
#ifndef __EDITOR_ACTION_STATIC_MESH_DELETE_H_
#define __EDITOR_ACTION_STATIC_MESH_DELETE_H_


#include "libEngine.h"
#include "libEditor.h"
#include "EditorAction.h"


class EditorAction_StaticMesh_Delete : public EditorAction
{
public:
  EditorAction_StaticMesh_Delete();
  virtual ~EditorAction_StaticMesh_Delete();

  virtual bool Init(const String &nodePath);

  virtual bool Complete();
  virtual void Discard();

  virtual void Update();

};


#endif // __EDITOR_ACTION_STATIC_MESH_DELETE_H_

// -- EOF

