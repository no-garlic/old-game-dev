
#include "SceneGroupNode.h"
#include "EditorResource.h"
#include "StaticMeshNode.h"
#include "ContentItemNode.h"
#include "Editor.h"



SceneGroupNode::SceneGroupNode(wxTreeItemId id)
: TreeNode(id, "SceneGroupNode")
{
  m_BitField.Add(TREE_NODE_PICKABLE);
  m_BitField.Add(TREE_NODE_RENDERABLE);

  Editor.GetDocument()->SetDirty();
}


SceneGroupNode::~SceneGroupNode()
{
  Editor.GetDocument()->SetDirty();
}


void SceneGroupNode::OnEnter()
{
  // Called when the node is selected
}


void SceneGroupNode::OnLeave()
{
  // Called when the node is de-selected
}


void SceneGroupNode::Create()
{
  ImageList *pImageList = Editor.GetImageList();
  SetIconId(pImageList->GetIndex("icon_world"), wxTreeItemIcon_Normal);
  SetIconId(pImageList->GetIndex("icon_world_dynamic"), wxTreeItemIcon_Selected);
}


void SceneGroupNode::OnRightClick(const wxPoint &pos)
{
  wxMenu menu;
  menu.Append(MNU_SCENE_NEW_GROUP, "New Group");

  EditorContentPanel *pContentPanel = Editor.GetLeftPanel()->GetContentPanel();
  TreeNode *pNode = pContentPanel->GetTreeView()->GetSelectedNode();

  if (pNode)
  {
    if (pNode->GetType() == "ContentItemNode")
    {
      ContentItemNode *pContentItemNode = (ContentItemNode *) pNode;
      String name = "New Mesh: " + pNode->GetText();

      menu.AppendSeparator();
      menu.Append(MNU_SCENE_NEW_MESH, name.c_str());
    }
  }

  PopupMenu(&menu, pos);
}



// -- EOF

