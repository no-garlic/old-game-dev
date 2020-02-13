
#include "EditorAction_SceneGroup_Delete.h"
#include "Editor.h"
#include "SceneGroupUtils.h"
#include "UndoAction_SceneGroup_Add_Delete.h"


EditorAction_SceneGroup_Delete::EditorAction_SceneGroup_Delete()
: EditorAction  ()
{
}


EditorAction_SceneGroup_Delete::~EditorAction_SceneGroup_Delete()
{
}


bool EditorAction_SceneGroup_Delete::Init(const String &nodePath)
{
  if (SceneGroupUtils::DeleteNode(nodePath))
  {
    if (Editor.GetUndoManager()->IsActive())
    {
      UndoAction_SceneGroup_Add_Delete *pUndoAction = new UndoAction_SceneGroup_Add_Delete();
      pUndoAction->SetDeleteNode(nodePath);

      Editor.GetUndoManager()->Add(pUndoAction);
    }

    return true;
  }

  return false;
}


bool EditorAction_SceneGroup_Delete::Complete()
{
  Editor.GetDocument()->SetDirty();
  return true;
}


void EditorAction_SceneGroup_Delete::Discard()
{
}


void EditorAction_SceneGroup_Delete::Update()
{
}


// -- EOF

