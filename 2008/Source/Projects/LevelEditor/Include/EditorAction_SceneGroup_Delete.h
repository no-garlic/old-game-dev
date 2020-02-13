
#ifndef __EDITOR_ACTION_SCENE_GROUP_DELETE_H_
#define __EDITOR_ACTION_SCENE_GROUP_DELETE_H_


#include "libEngine.h"
#include "libEditor.h"
#include "EditorAction.h"


class EditorAction_SceneGroup_Delete : public EditorAction
{
public:
  EditorAction_SceneGroup_Delete();
  virtual ~EditorAction_SceneGroup_Delete();

  virtual bool Init(const String &nodePath);

  virtual bool Complete();
  virtual void Discard();

  virtual void Update();

};


#endif // __EDITOR_ACTION_SCENE_GROUP_DELETE_H_

// -- EOF

