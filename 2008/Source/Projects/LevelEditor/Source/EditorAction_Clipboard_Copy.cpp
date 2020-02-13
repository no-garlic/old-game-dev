
#include "EditorAction_Clipboard_Copy.h"
#include "Editor.h"


EditorAction_Clipboard_Copy::EditorAction_Clipboard_Copy()
: EditorAction  ()
{
}


EditorAction_Clipboard_Copy::~EditorAction_Clipboard_Copy()
{
}


bool EditorAction_Clipboard_Copy::Init(const String &nodePath)
{
  TreeNode *pNode = NULL;

  if (nodePath.empty())
    pNode = Editor.GetLeftPanel()->GetScenePanel()->GetTreeView()->GetSelectedNode();
  else
    pNode = Editor.GetLeftPanel()->GetScenePanel()->GetTreeView()->FindTreeNode(nodePath);

  if (!pNode)
  {
    Editor.GetActionManager()->GetClipboard().IsValid = false;
    return false;
  }

  Editor.GetActionManager()->GetClipboard().Path.clear();
  pNode->GetPath(Editor.GetActionManager()->GetClipboard().Path);
  Editor.GetActionManager()->GetClipboard().IsValid = true;
  Editor.GetActionManager()->GetClipboard().IsCut   = false;

  return true;
}


bool EditorAction_Clipboard_Copy::Complete()
{
  return true;
}


void EditorAction_Clipboard_Copy::Discard()
{
}


void EditorAction_Clipboard_Copy::Update()
{
}


// -- EOF

