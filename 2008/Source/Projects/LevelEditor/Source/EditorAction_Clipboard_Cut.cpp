
#include "EditorAction_Clipboard_Cut.h"
#include "Editor.h"


EditorAction_Clipboard_Cut::EditorAction_Clipboard_Cut()
: EditorAction  ()
{
}


EditorAction_Clipboard_Cut::~EditorAction_Clipboard_Cut()
{
}


bool EditorAction_Clipboard_Cut::Init(const String &nodePath)
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
  Editor.GetActionManager()->GetClipboard().IsCut   = true;

  return true;
}


bool EditorAction_Clipboard_Cut::Complete()
{
  return true;
}


void EditorAction_Clipboard_Cut::Discard()
{
}


void EditorAction_Clipboard_Cut::Update()
{
}


// -- EOF

