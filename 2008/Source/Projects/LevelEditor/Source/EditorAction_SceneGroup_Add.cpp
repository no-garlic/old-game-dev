
#include "EditorAction_SceneGroup_Add.h"
#include "Editor.h"
#include "SceneGroupUtils.h"
#include "UndoAction_SceneGroup_Add_Delete.h"


EditorAction_SceneGroup_Add::EditorAction_SceneGroup_Add()
: EditorAction  ()
{
}


EditorAction_SceneGroup_Add::~EditorAction_SceneGroup_Add()
{
}


bool EditorAction_SceneGroup_Add::Init(const String &nodePath)
{
  if (SceneGroupUtils::AddNode(nodePath))
  {
    if (Editor.GetUndoManager()->IsActive())
    {
      UndoAction_SceneGroup_Add_Delete *pUndoAction = new UndoAction_SceneGroup_Add_Delete();
      pUndoAction->SetAddNode(nodePath);

      Editor.GetUndoManager()->Add(pUndoAction);
    }

    return true;
  }

  return false;
}


bool EditorAction_SceneGroup_Add::Complete()
{
  Editor.GetDocument()->SetDirty();
  return true;
}


void EditorAction_SceneGroup_Add::Discard()
{
}


void EditorAction_SceneGroup_Add::Update()
{
}


// -- EOF

