
#include "EditorInput_Mouse.h"
#include "libEditor.h"
#include "Editor.h"
#include "StaticMeshNode.h"


EditorInput_Mouse::EditorInput_Mouse()
{
  m_CursorPos.x = ~0;
  m_CursorPos.y = ~0;
}


EditorInput_Mouse::~EditorInput_Mouse()
{
}


void EditorInput_Mouse::Update()
{
  while (Input.HasMouseMessage())
  {
    MouseMessage msg = Input.PopMouseMessage();

    if (Editor.IsMouseOverViewport())
    {
      if (Input.GetKeyboardState(KEYPARAM_LALT) == KEYVAL_DOWN || Input.GetKeyboardState(KEYPARAM_RALT) == KEYVAL_DOWN)
      {
        Editor.GetCameraManager()->OnMouseMessage(msg);
      }
      else if (msg.param == MOUSEPARAM_BUTTON_0 && msg.value == MOUSEVAL_BUTTON_DOWN)
      {
        GetCursorPos(&m_CursorPos);

        StaticMeshNode *pMeshNode = NULL;

        // Find and select the mesh under the mouse
        TreeNode *pNode = Editor.GetDocument()->Pick();
        if (pNode && pNode->GetType() == "StaticMeshNode")
        {
          // Select the node (should call the callback and highlight the mesh)
          pNode->Select(true);
          pMeshNode = (StaticMeshNode*) pNode;
          Editor.GetLeftPanel()->GetScenePanel()->SetSelectedStaticMeshNode(pMeshNode);
        }

        if (!pMeshNode)
        {
          pMeshNode = Editor.GetLeftPanel()->GetScenePanel()->GetSelectedStaticMeshNode();
        }

        if (pMeshNode)
        {
          if (!Editor.GetActionManager()->HasCurrentAction())
          {
            Ray ray = Camera.GetMouseRay3D();

            Sphere s = pMeshNode->GetMesh()->GetBSphere();
            s.center += pMeshNode->GetMatrix().GetTAxis();
            s.radius *= pMeshNode->GetMatrix().GetScaleMax();

            if (ray.TestCollision(s))
            {
              String path;
              pMeshNode->GetPath(path);

              switch (Editor.GetToolPanel()->GetToolType())
              {
              case ToolPanel::TT_MOVE:
                Editor.GetActionManager()->CreateAction(ActionManager::ACTION_STATIC_MESH_MOVE, path);
                break;
              case ToolPanel::TT_ROTATE:
                Editor.GetActionManager()->CreateAction(ActionManager::ACTION_STATIC_MESH_ROTATE, path);
                break;
              case ToolPanel::TT_SCALE:
                Editor.GetActionManager()->CreateAction(ActionManager::ACTION_STATIC_MESH_SCALE, path);
                break;
              }
            }
          }
        }
      }
      else if (msg.param == MOUSEPARAM_BUTTON_0 && msg.value == MOUSEVAL_BUTTON_UP)
      {
        POINT pt;
        GetCursorPos(&pt);

        if ((pt.x == m_CursorPos.x && pt.y == m_CursorPos.y) || !Editor.GetActionManager()->HasCurrentAction())
        {
          // The mouse never moved, so revert the action if it was created
          if (Editor.GetActionManager()->HasCurrentAction())
          {
            Editor.GetActionManager()->DiscardAction();
          }

          // Find the mesh under the mouse
          TreeNode *pNode = Editor.GetDocument()->Pick();
          if (!pNode)
          {
            // Unselect the node
            TreeView *pTreeView = Editor.GetLeftPanel()->GetScenePanel()->GetTreeView();
            pTreeView->UnSelect();
          }
        }
        else
        {
          // The mouse was released in a different place to where it was pressed so commit the action
          if (Editor.GetActionManager()->HasCurrentAction())
          {
            Editor.GetActionManager()->CompleteAction();
          }
        }
      }
    }
    else
    {
      // The mouse has left the viewport, so cancel the action
      if (Editor.GetActionManager()->HasCurrentAction())
      {
        Editor.GetActionManager()->DiscardAction();
      }
    }
  }
}

  
// -- EOF

