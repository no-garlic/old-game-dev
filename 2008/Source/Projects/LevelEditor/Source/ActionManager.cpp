
#include "ActionManager.h"
#include "Editor.h"

#include "EditorAction_Document_Close.h"
#include "EditorAction_Document_New.h"
#include "EditorAction_Document_Open.h"
#include "EditorAction_Document_Save.h"
#include "EditorAction_Document_SaveAs.h"
#include "EditorAction_Clipboard_Copy.h"
#include "EditorAction_Clipboard_Cut.h"
#include "EditorAction_Clipboard_Paste.h"
#include "EditorAction_StaticMesh_Add.h"
#include "EditorAction_StaticMesh_Delete.h"
#include "EditorAction_StaticMesh_Flag.h"
#include "EditorAction_StaticMesh_Rename.h"
#include "EditorAction_SceneGroup_Add.h"
#include "EditorAction_SceneGroup_Delete.h"
#include "EditorAction_SceneGroup_Rename.h"
#include "EditorAction_StaticMesh_Duplicate.h"
#include "EditorAction_StaticMesh_Move.h"
#include "EditorAction_StaticMesh_Rotate.h"
#include "EditorAction_StaticMesh_Scale.h"
#include "EditorAction_StaticMesh_SetTransform.h"
#include "EditorAction_StaticMesh_Relocate.h"
#include "EditorAction_Undo.h"
#include "EditorAction_Redo.h"
#include "EditorAction_DeleteSelected.h"
#include "EditorAction_Exit.h"


// Macro for creating editor actions to the CreateAction function
#define CREATE_EDITOR_ACTION(Type) { m_pCurrentAction = new Type();\
      if (!m_pCurrentAction->Init(nodePath))\
      {\
        delete m_pCurrentAction;\
        m_pCurrentAction = NULL;\
        return false;\
      }\
      return true; }\


ActionManager::ActionManager()
{
  m_Clipboard.IsValid = false;
  m_Clipboard.IsCut   = false;
  m_pCurrentAction    = NULL;
}


ActionManager::~ActionManager()
{
  delete m_pCurrentAction;
}


void ActionManager::Update()
{
  if (m_pCurrentAction)
  {
    m_pCurrentAction->Update();
  }
}


bool ActionManager::CreateAndCompleteAction(EditorActionType type, const String &nodePath)
{
  if (!CreateAction(type, nodePath))
  {
    return false;
  }

  if (!CompleteAction())
  {
    return false;
  }

  return true;
}


bool ActionManager::CreateAction(EditorActionType type, const String &nodePath)
{
  if (m_pCurrentAction)
  {
    return false;
  }

  switch (type)
  {
    case ACTION_SCENE_GROUP_ADD:          CREATE_EDITOR_ACTION(EditorAction_SceneGroup_Add);
    case ACTION_SCENE_GROUP_DELETE:       CREATE_EDITOR_ACTION(EditorAction_SceneGroup_Delete);
    case ACTION_SCENE_GROUP_RENAME:       CREATE_EDITOR_ACTION(EditorAction_SceneGroup_Rename);
    case ACTION_STATIC_MESH_ADD:          CREATE_EDITOR_ACTION(EditorAction_StaticMesh_Add);
    case ACTION_STATIC_MESH_DELETE:       CREATE_EDITOR_ACTION(EditorAction_StaticMesh_Delete);
    case ACTION_STATIC_MESH_FLAG:         CREATE_EDITOR_ACTION(EditorAction_StaticMesh_Flag);
    case ACTION_STATIC_MESH_DUPLICATE:    CREATE_EDITOR_ACTION(EditorAction_StaticMesh_Duplicate);
    case ACTION_STATIC_MESH_RENAME:       CREATE_EDITOR_ACTION(EditorAction_StaticMesh_Rename);
    case ACTION_STATIC_MESH_MOVE:         CREATE_EDITOR_ACTION(EditorAction_StaticMesh_Move);
    case ACTION_STATIC_MESH_ROTATE:       CREATE_EDITOR_ACTION(EditorAction_StaticMesh_Rotate);
    case ACTION_STATIC_MESH_SCALE:        CREATE_EDITOR_ACTION(EditorAction_StaticMesh_Scale);
    case ACTION_STATIC_MESH_TRANSFORM:    CREATE_EDITOR_ACTION(EditorAction_StaticMesh_SetTransform);
    case ACTION_STATIC_MESH_RELOCATE:     CREATE_EDITOR_ACTION(EditorAction_StaticMesh_Relocate);
    case ACTION_DOCUMENT_NEW:             CREATE_EDITOR_ACTION(EditorAction_Document_New);
    case ACTION_DOCUMENT_SAVE:            CREATE_EDITOR_ACTION(EditorAction_Document_Save);
    case ACTION_DOCUMENT_SAVEAS:          CREATE_EDITOR_ACTION(EditorAction_Document_SaveAs);
    case ACTION_DOCUMENT_OPEN:            CREATE_EDITOR_ACTION(EditorAction_Document_Open);
    case ACTION_DOCUMENT_CLOSE:           CREATE_EDITOR_ACTION(EditorAction_Document_Close);
    case ACTION_CLIPBOARD_CUT:            CREATE_EDITOR_ACTION(EditorAction_Clipboard_Cut);
    case ACTION_CLIPBOARD_COPY:           CREATE_EDITOR_ACTION(EditorAction_Clipboard_Copy);
    case ACTION_CLIPBOARD_PASTE:          CREATE_EDITOR_ACTION(EditorAction_Clipboard_Paste);
    case ACTION_UNDO:                     CREATE_EDITOR_ACTION(EditorAction_Undo);
    case ACTION_REDO:                     CREATE_EDITOR_ACTION(EditorAction_Redo);
    case ACTION_EXIT:                     CREATE_EDITOR_ACTION(EditorAction_Exit);
    case ACTION_DELETE_SELECTED:          CREATE_EDITOR_ACTION(EditorAction_DeleteSelected);
  }

  return false;
}


void ActionManager::SetActionParameter(const String &paramName, const String &paramValue)
{
  if (m_pCurrentAction)
  {
    m_pCurrentAction->SetParameter(paramName, paramValue);
  }
}


void ActionManager::SetActionParameter(const String &paramName, const Vec3   &paramValue)
{
  if (m_pCurrentAction)
  {
    m_pCurrentAction->SetParameter(paramName, paramValue);
  }
}


void ActionManager::SetActionParameter(const String &paramName, int    paramValue)
{
  if (m_pCurrentAction)
  {
    m_pCurrentAction->SetParameter(paramName, paramValue);
  }
}


void ActionManager::SetActionParameter(const String &paramName, uint   paramValue)
{
  if (m_pCurrentAction)
  {
    m_pCurrentAction->SetParameter(paramName, paramValue);
  }
}


void ActionManager::SetActionParameter(const String &paramName, float  paramValue)
{
  if (m_pCurrentAction)
  {
    m_pCurrentAction->SetParameter(paramName, paramValue);
  }
}


void ActionManager::SetActionParameter(const String &paramName, bool   paramValue)
{
  if (m_pCurrentAction)
  {
    m_pCurrentAction->SetParameter(paramName, paramValue);
  }
}


bool ActionManager::CompleteAction()
{
  if (m_pCurrentAction)
  {
    bool result = m_pCurrentAction->Complete();
    delete m_pCurrentAction;
    m_pCurrentAction = NULL;
    return result;
  }
  return false;
}


void ActionManager::DiscardAction()
{
  if (m_pCurrentAction)
  {
    m_pCurrentAction->Discard();
    delete m_pCurrentAction;
    m_pCurrentAction = NULL;
  }
}

// -- EOF

