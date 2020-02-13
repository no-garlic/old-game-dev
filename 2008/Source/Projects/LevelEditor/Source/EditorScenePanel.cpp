
#include "EditorScenePanel.h"
#include "EditorResource.h"
#include "SceneGroupNode.h"
#include "ContentItemNode.h"
#include "EditorAction_StaticMesh_Flag.h"
#include "Editor.h"


BEGIN_EVENT_TABLE(EditorScenePanel, wxPanel)
  EVT_TREE_SEL_CHANGED(CTL_SCENE_TREE, EditorScenePanel::OnItemChanged)
  EVT_TREE_ITEM_RIGHT_CLICK(CTL_SCENE_TREE, EditorScenePanel::OnItemRightClick)
  EVT_TREE_BEGIN_DRAG(CTL_SCENE_TREE, EditorScenePanel::OnBeginDrag)
  EVT_TREE_END_DRAG(CTL_SCENE_TREE, EditorScenePanel::OnEndDrag)
  EVT_TREE_BEGIN_LABEL_EDIT(CTL_SCENE_TREE, EditorScenePanel::OnBeginEdit)
  EVT_TREE_END_LABEL_EDIT(CTL_SCENE_TREE, EditorScenePanel::OnEndEdit)
  EVT_TREE_KEY_DOWN(CTL_SCENE_TREE, EditorScenePanel::OnKeyDown)
  EVT_MENU(MNU_SCENE_NEW_GROUP, EditorScenePanel::OnMenuCreateGroup)
  EVT_MENU(MNU_SCENE_NEW_MESH, EditorScenePanel::OnMenuCreateMesh)
  EVT_MENU(MNU_RENDER_FLAG, EditorScenePanel::OnMenuRenderFlag)
  EVT_MENU(MNU_PICKABLE_FLAG, EditorScenePanel::OnMenuPickableFlag)
  EVT_MENU(MNU_FROZEN_FLAG, EditorScenePanel::OnMenuFrozenFlag)
  EVT_MENU(MNU_DELETE_SELECTED, EditorScenePanel::OnMenuDeleteSelected)
END_EVENT_TABLE()


EditorScenePanel::EditorScenePanel(wxWindow *pParent)
: wxPanel(pParent, EDT_SCENE_PANEL)
{
  // Create the tree view
  m_pTreeView = new TreeView(this, CTL_SCENE_TREE, wxPoint(0, 0), 
    pParent->GetSize(), wxBORDER_NONE | wxTR_HAS_BUTTONS | wxTR_LINES_AT_ROOT | wxTR_EDIT_LABELS);

  // Set the image list
  m_pTreeView->SetImageList(Editor.GetImageList());

  // Create the root node
  SceneGroupNode *pRootNode = m_pTreeView->AddRootNode<SceneGroupNode>("Scene");
  pRootNode->Create();
  m_pTreeView->Expand();

  // There is no selected static mesh node
  m_pStaticMeshSel = NULL;
}


EditorScenePanel::~EditorScenePanel()
{
}


void EditorScenePanel::Clear()
{
  // Clear the undo manager
  Editor.GetUndoManager()->Flush();

  // Disable the undo manager
  bool active = Editor.GetUndoManager()->IsActive();
  Editor.GetUndoManager()->SetActive(false);

  // Delete all nodes below the root node
  TreeNode *pRootNode = m_pTreeView->GetRootNode();
  pRootNode->DeleteAllChildren();

  // Reset the selected static mesh node
  m_pStaticMeshSel = NULL;

  // Reset the undo manager to it's previous state
  Editor.GetUndoManager()->SetActive(active);
}


void EditorScenePanel::OnItemRightClick(wxTreeEvent &event)
{
  // Get the mouse cursor position
  POINT pt;
  ::GetCursorPos(&pt);
  ::ScreenToClient((HWND) this->GetHWND(), &pt);
  
  // Call the OnRightClick method of the node
  wxTreeItemId itemId = event.GetItem();
  TreeNode *pNode = m_pTreeView->FindTreeNode(itemId);
  if (pNode)
  {
    pNode->OnRightClick(wxPoint(pt.x, pt.y));
  }
}


void EditorScenePanel::OnItemChanged(wxTreeEvent &event)
{
  // Get the old and new items from the tree view
  TreeNode *pNewNode = m_pTreeView->FindTreeNode(event.GetItem());
  TreeNode *pOldNode = m_pTreeView->FindTreeNode(event.GetOldItem());

  // CAll OnLeave for the old item
  if (pOldNode)
  {
    pOldNode->OnLeave();
  }

  // Call OnEnter for the new item
  if (pNewNode)
  {
    pNewNode->OnEnter();
  }
}


void EditorScenePanel::OnBeginDrag(wxTreeEvent &event)
{
  TreeNode *pNode = m_pTreeView->FindTreeNode(event.GetItem());

  if (pNode && pNode->GetType() == "StaticMeshNode")
  {
    if (pNode->GetChildrenCount() == 0)
    {
      event.Allow();      
      m_DragItemPath.clear();
      pNode->GetPath(m_DragItemPath);
    }
  }
}


void EditorScenePanel::OnEndDrag(wxTreeEvent &event)
{
  TreeNode *pNode = m_pTreeView->FindTreeNode(event.GetItem());

  if (pNode && pNode->GetType() == "StaticMeshNode")
  {
    pNode = pNode->GetParentNode();
  }

  if (pNode && pNode->GetType() == "SceneGroupNode")
  {
    String newPath;
    pNode->GetPath(newPath);

    String oldPath, oldName;
    SplitPath(m_DragItemPath, oldPath, oldName);

    newPath = newPath + "/" + oldName;

    if (Editor.GetActionManager()->CreateAction(ActionManager::ACTION_STATIC_MESH_RELOCATE, m_DragItemPath))
    {
      Editor.GetActionManager()->SetActionParameter("Path", newPath);
      if (Editor.GetActionManager()->CompleteAction())
      {
        return;
      }
    }

    DEBUG_BREAK;
  }
}


void EditorScenePanel::OnBeginEdit(wxTreeEvent &event)
{
}


void EditorScenePanel::OnEndEdit(wxTreeEvent &event)
{
  if (event.IsEditCancelled())
  {
    return;
  }

  String newName = String(event.GetLabel().c_str());
  if (newName.empty())
  {
    return;
  }

  TreeNode *pNode = m_pTreeView->GetSelectedNode();
  if (pNode)
  {
    // Get the node path
    String path;
    pNode->GetPath(path);

    // Run the Rename action
    if (Editor.GetActionManager()->CreateAction(ActionManager::ACTION_SCENE_GROUP_RENAME, path))
    {
      Editor.GetActionManager()->SetActionParameter("Name", newName);

      if (Editor.GetActionManager()->CompleteAction())
      {
        return;
      }
    }
  }

  // Failed
  DEBUG_BREAK;
}


void EditorScenePanel::OnKeyDown(wxTreeEvent& event)
{
  if (event.GetKeyCode() == WXK_F2)
  {
    TreeNode *pNode = m_pTreeView->GetSelectedNode();
    if (pNode)
    {
      pNode->Edit();
    }
  }
}


void EditorScenePanel::OnMenuCreateGroup(wxCommandEvent &event)
{
  TreeNode *pNode = m_pTreeView->GetSelectedNode();
  if (pNode)
  {
    // Get the parent node path
    String path;
    pNode->GetPath(path);

    // Create the fully qualified path for the new group node
    path = path + "/" + Editor.GetNextName("Group");

    // Run the Add Scene Node action
    if (!Editor.GetActionManager()->CreateAndCompleteAction(ActionManager::ACTION_SCENE_GROUP_ADD, path))
    {
      // Failed
    }
    else
    {
      TreeNode *pSelectedNode = Editor.GetLeftPanel()->GetScenePanel()->GetTreeView()->GetSelectedNode();
      if (pSelectedNode)
      {
        pSelectedNode->Edit();
      }
    }
  }
}


void EditorScenePanel::OnMenuCreateMesh(wxCommandEvent &event)
{
  TreeNode *pNode = m_pTreeView->GetSelectedNode();
  if (pNode)
  {
    // Get the node path
    String path;
    pNode->GetPath(path);

    EditorContentPanel *pContentPanel = Editor.GetLeftPanel()->GetContentPanel();
    TreeNode *pNode = pContentPanel->GetTreeView()->GetSelectedNode();

    if (pNode && pNode->GetType() == "ContentItemNode")
    {
      ContentItemNode *pContentItemNode = (ContentItemNode *) pNode;

      // Create the fully qualified path for the new mesh node
      path = path + "/" + Editor.GetNextName(pContentItemNode->GetText());

      // Run the Add Scene Node action
      if (!Editor.GetActionManager()->CreateAndCompleteAction(ActionManager::ACTION_STATIC_MESH_ADD, path))
      {
        // Failed
      }
      else
      {
        TreeNode *pSelectedNode = Editor.GetLeftPanel()->GetScenePanel()->GetTreeView()->GetSelectedNode();
        if (pSelectedNode)
        {
          pSelectedNode->Edit();
        }
      }
    }
  }
}


void EditorScenePanel::OnMenuRenderFlag(wxCommandEvent &event)
{
  TreeNode *pNode = m_pTreeView->GetSelectedNode();
  if (pNode)
  {
    // Get the node path
    String path;
    pNode->GetPath(path);

    if (pNode->GetType() == "StaticMeshNode")
    {
      if (!Editor.GetActionManager()->CreateAction(ActionManager::ACTION_STATIC_MESH_FLAG, path))
      {
        // Failed
      }

      Editor.GetActionManager()->SetActionParameter("Add", event.IsChecked());
      Editor.GetActionManager()->SetActionParameter("Flag", (uint)TREE_NODE_RENDERABLE);

      if (!Editor.GetActionManager()->CompleteAction())
      {
        // Failed
      }
    }

    else if (pNode->GetType() == "SceneGroupNode")
    {
    }
  }
}


void EditorScenePanel::OnMenuPickableFlag(wxCommandEvent &event)
{
  TreeNode *pNode = m_pTreeView->GetSelectedNode();
  if (pNode)
  {
    // Get the node path
    String path;
    pNode->GetPath(path);

    if (pNode->GetType() == "StaticMeshNode")
    {
      if (!Editor.GetActionManager()->CreateAction(ActionManager::ACTION_STATIC_MESH_FLAG, path))
      {
        // Failed
      }

      Editor.GetActionManager()->SetActionParameter("Add", event.IsChecked());
      Editor.GetActionManager()->SetActionParameter("Flag", (uint)TREE_NODE_PICKABLE);

      if (!Editor.GetActionManager()->CompleteAction())
      {
        // Failed
      }
    }

    else if (pNode->GetType() == "SceneGroupNode")
    {
    }
  }
}


void EditorScenePanel::OnMenuFrozenFlag(wxCommandEvent &event)
{
  TreeNode *pNode = m_pTreeView->GetSelectedNode();
  if (pNode)
  {
    // Get the node path
    String path;
    pNode->GetPath(path);

    if (pNode->GetType() == "StaticMeshNode")
    {
      if (!Editor.GetActionManager()->CreateAction(ActionManager::ACTION_STATIC_MESH_FLAG, path))
      {
        // Failed
      }

      Editor.GetActionManager()->SetActionParameter("Add", event.IsChecked());
      Editor.GetActionManager()->SetActionParameter("Flag", (uint)TREE_NODE_FROZEN);

      if (!Editor.GetActionManager()->CompleteAction())
      {
        // Failed
      }
    }

    else if (pNode->GetType() == "SceneGroupNode")
    {
    }
  }
}


void EditorScenePanel::OnMenuDeleteSelected(wxCommandEvent &event)
{
  Editor.GetActionManager()->CreateAndCompleteAction(ActionManager::ACTION_DELETE_SELECTED);
}


// -- EOF

