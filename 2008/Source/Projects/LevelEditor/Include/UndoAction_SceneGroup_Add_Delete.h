
#ifndef __UNDO_ACTION_SCENE_GROUP_ADD_H_
#define __UNDO_ACTION_SCENE_GROUP_ADD_H_


#include "libEngine.h"
#include "libEditor.h"
#include "UndoManager.h"


class UndoAction_SceneGroup_Add_Delete : public UndoAction
{
public:
  UndoAction_SceneGroup_Add_Delete();
  virtual ~UndoAction_SceneGroup_Add_Delete();

  // Newly added node
  void SetAddNode(const String &path);

  // Deleted node
  void SetDeleteNode(const String &path);

  virtual void Undo();
  virtual void Redo();

private:
  String  m_AddPath;
  String  m_DeletePath;
};


#endif // __UNDO_ACTION_SCENE_GROUP_ADD_H_

// -- EOf

