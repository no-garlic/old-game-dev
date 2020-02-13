
#include "EditorInput_Keyboard.h"
#include "libEditor.h"
#include "Editor.h"
#include "EditorResource.h"


EditorInput_Keyboard::EditorInput_Keyboard()
{
}


EditorInput_Keyboard::~EditorInput_Keyboard()
{
}


/* //-----------------------------------------//
  ESCAPE          Unselect
  
  CTRL-DELETE     Delete Node
  
  CTRL-N          New Document
  CTRL-O          Open Document
  CTRL-S          Save Document
  
  CTRL-Z          Undo
  CTRL-Y          Redo
  
  CTRL-C          Copy
  CTRL-X          Cut
  CTRL-V          Paste

  P               Perspective Camera
  F               Front Camera
  K               Back Camera
  L               Left Camera
  R               Right Camera
  T               Top Camera
  B               Bottom Camera

  V               ViewMode Normal
  O               ViewMode Normal (WireOver)
  W               ViewMode Wireframe
  U               ViewMode Unlit
  N               ViewMode NoTex

  Z               Zoom Camera to Selection
*/ //------------------------------------------//


void EditorInput_Keyboard::Update()
{
  while (Input.HasKeyboardMessage())
  {
    KeyboardMessage msg = Input.PopKeyboardMessage();

    LOG_INFO << "Key: " << msg.param << " - " << msg.value << ENDLOG;

    if (msg.param == KEYPARAM_ESCAPE && msg.value == KEYVAL_DOWN)
    {
      TreeView *pTreeView = Editor.GetLeftPanel()->GetScenePanel()->GetTreeView();
      pTreeView->UnSelect();
    }
    else if (msg.param == KEYPARAM_DELETE && msg.value == KEYVAL_DOWN)
    {
      if (Input.GetKeyboardState(KEYPARAM_LCONTROL) == KEYVAL_DOWN || Input.GetKeyboardState(KEYPARAM_RCONTROL) == KEYVAL_DOWN) 
      {
        Editor.GetActionManager()->CreateAndCompleteAction(ActionManager::ACTION_DELETE_SELECTED);
      }
    }
    else if (msg.param == KEYPARAM_N && msg.value == KEYVAL_DOWN)
    {
      if (Input.GetKeyboardState(KEYPARAM_LCONTROL) == KEYVAL_DOWN || Input.GetKeyboardState(KEYPARAM_RCONTROL) == KEYVAL_DOWN) 
      {
        Editor.GetActionManager()->CreateAndCompleteAction(ActionManager::ACTION_DOCUMENT_NEW);
      }
      else
      {
        Editor.GetDocument()->SetViewMode(EditorDocument::VIEW_NOTEX);
      }
    }
    else if (msg.param == KEYPARAM_O && msg.value == KEYVAL_DOWN)
    {
      if (Input.GetKeyboardState(KEYPARAM_LCONTROL) == KEYVAL_DOWN || Input.GetKeyboardState(KEYPARAM_RCONTROL) == KEYVAL_DOWN) 
      {
        Editor.GetActionManager()->CreateAndCompleteAction(ActionManager::ACTION_DOCUMENT_OPEN);
      }
      else
      {
        Editor.GetDocument()->SetViewMode(EditorDocument::VIEW_NORMAL_WIREOVER);
      }
    }
    else if (msg.param == KEYPARAM_S && msg.value == KEYVAL_DOWN)
    {
      if (Input.GetKeyboardState(KEYPARAM_LCONTROL) == KEYVAL_DOWN || Input.GetKeyboardState(KEYPARAM_RCONTROL) == KEYVAL_DOWN) 
      {
        Editor.GetActionManager()->CreateAndCompleteAction(ActionManager::ACTION_DOCUMENT_SAVE);
      }
    }
    else if (msg.param == KEYPARAM_Z && msg.value == KEYVAL_DOWN)
    {
      if (Input.GetKeyboardState(KEYPARAM_LCONTROL) == KEYVAL_DOWN || Input.GetKeyboardState(KEYPARAM_RCONTROL) == KEYVAL_DOWN) 
      {
        Editor.GetActionManager()->CreateAndCompleteAction(ActionManager::ACTION_UNDO);
      }
      else
      {
        Editor.GetCameraManager()->Focus();
      }
    }
    else if (msg.param == KEYPARAM_Y && msg.value == KEYVAL_DOWN)
    {
      if (Input.GetKeyboardState(KEYPARAM_LCONTROL) == KEYVAL_DOWN || Input.GetKeyboardState(KEYPARAM_RCONTROL) == KEYVAL_DOWN) 
      {
        Editor.GetActionManager()->CreateAndCompleteAction(ActionManager::ACTION_REDO);
      }
    }
    else if (msg.param == KEYPARAM_C && msg.value == KEYVAL_DOWN)
    {
      if (Input.GetKeyboardState(KEYPARAM_LCONTROL) == KEYVAL_DOWN || Input.GetKeyboardState(KEYPARAM_RCONTROL) == KEYVAL_DOWN) 
      {
        Editor.GetActionManager()->CreateAndCompleteAction(ActionManager::ACTION_CLIPBOARD_COPY);
      }
    }
    else if (msg.param == KEYPARAM_X && msg.value == KEYVAL_DOWN)
    {
      if (Input.GetKeyboardState(KEYPARAM_LCONTROL) == KEYVAL_DOWN || Input.GetKeyboardState(KEYPARAM_RCONTROL) == KEYVAL_DOWN) 
      {
        Editor.GetActionManager()->CreateAndCompleteAction(ActionManager::ACTION_CLIPBOARD_CUT);
      }
    }
    else if (msg.param == KEYPARAM_V && msg.value == KEYVAL_DOWN)
    {
      if (Input.GetKeyboardState(KEYPARAM_LCONTROL) == KEYVAL_DOWN || Input.GetKeyboardState(KEYPARAM_RCONTROL) == KEYVAL_DOWN) 
      {
        Editor.GetActionManager()->CreateAndCompleteAction(ActionManager::ACTION_CLIPBOARD_PASTE);
      }
      else
      {
        Editor.GetDocument()->SetViewMode(EditorDocument::VIEW_NORMAL);
      }
    }
    else if (msg.param == KEYPARAM_P && msg.value == KEYVAL_DOWN)
    {
      Editor.GetCameraManager()->SetCurrentCamera(CAM_PERSPECTIVE);
    }
    else if (msg.param == KEYPARAM_F && msg.value == KEYVAL_DOWN)
    {
      Editor.GetCameraManager()->SetCurrentCamera(CAM_FRONT);
    }
    else if (msg.param == KEYPARAM_K && msg.value == KEYVAL_DOWN)
    {
      Editor.GetCameraManager()->SetCurrentCamera(CAM_BACK);
    }
    else if (msg.param == KEYPARAM_L && msg.value == KEYVAL_DOWN)
    {
      Editor.GetCameraManager()->SetCurrentCamera(CAM_LEFT);
    }
    else if (msg.param == KEYPARAM_R && msg.value == KEYVAL_DOWN)
    {
      Editor.GetCameraManager()->SetCurrentCamera(CAM_RIGHT);
    }
    else if (msg.param == KEYPARAM_T && msg.value == KEYVAL_DOWN)
    {
      Editor.GetCameraManager()->SetCurrentCamera(CAM_TOP);
    }
    else if (msg.param == KEYPARAM_B && msg.value == KEYVAL_DOWN)
    {
      Editor.GetCameraManager()->SetCurrentCamera(CAM_BOTTOM);
    }
    else if (msg.param == KEYPARAM_W && msg.value == KEYVAL_DOWN)
    {
      Editor.GetDocument()->SetViewMode(EditorDocument::VIEW_WIREFRAME);
    }
    else if (msg.param == KEYPARAM_U && msg.value == KEYVAL_DOWN)
    {
      Editor.GetDocument()->SetViewMode(EditorDocument::VIEW_UNLIT);
    }
  }
}

  
// -- EOF

