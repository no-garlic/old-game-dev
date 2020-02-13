
#include "Editor.h"
#include "ToolBar.h"
#include "EditorResource.h"


ToolBar::ToolBar(const wxPoint &pos, const wxSize &size, UINT id, bool showBorder)
: EditorFrameToolbar(pos, size, id, showBorder)
{
}


ToolBar::~ToolBar()
{
}


// Need to update icons, etc...


void ToolBar::Init()
{
  BeginBuildToolbar(EDT_TOP_PANEL, wxHORIZONTAL);

  wxToolBar *pToolBar = GetToolBar();
  pToolBar->SetToolBitmapSize(wxSize(32, 32));

  FileHandle hNew   = Application.GetTextureDatabase()->FindFileHandle("New.png");
  FileHandle hOpen  = Application.GetTextureDatabase()->FindFileHandle("Open.png");
  FileHandle hSave  = Application.GetTextureDatabase()->FindFileHandle("Save.png");
  FileHandle hCut   = Application.GetTextureDatabase()->FindFileHandle("Cut.png");
  FileHandle hCopy  = Application.GetTextureDatabase()->FindFileHandle("Copy.png");
  FileHandle hPaste = Application.GetTextureDatabase()->FindFileHandle("Paste.png");
  FileHandle hUndo  = Application.GetTextureDatabase()->FindFileHandle("Undo.png");
  FileHandle hRedo  = Application.GetTextureDatabase()->FindFileHandle("Redo.png");
 
  AddTool(TBB_NEW,    hNew,   MakeCallback(&ToolBar::OnToolEvent, this));
  AddTool(TBB_OPEN,   hOpen,  MakeCallback(&ToolBar::OnToolEvent, this));
  AddTool(TBB_SAVE,   hSave,  MakeCallback(&ToolBar::OnToolEvent, this));

  AddSeperator();

  AddTool(TBB_CUT,    hCut,   MakeCallback(&ToolBar::OnToolEvent, this));
  AddTool(TBB_COPY,   hCopy,  MakeCallback(&ToolBar::OnToolEvent, this));
  AddTool(TBB_PASTE,  hPaste, MakeCallback(&ToolBar::OnToolEvent, this));

  AddSeperator();

  AddTool(TBB_UNDO,   hUndo,  MakeCallback(&ToolBar::OnToolEvent, this));
  AddTool(TBB_REDO,   hRedo,  MakeCallback(&ToolBar::OnToolEvent, this));

  // TESTING ------------------
  /*
  FileHandle hTestA = Application.GetTextureDatabase()->FindFileHandle("A.png");
  FileHandle hTestB = Application.GetTextureDatabase()->FindFileHandle("B.png");

  AddSeperator();

  AddTool(0,          hTestA, MakeCallback(&ToolBar::OnToolEvent, this));
  AddTool(1,          hTestB, MakeCallback(&ToolBar::OnToolEvent, this));
  */
  // TESTING ------------------

  EndBuildToolbar();
}


void ToolBar::OnToolEvent(int id)
{
  switch (id)
  {
  case TBB_NEW:
    Editor.GetActionManager()->CreateAndCompleteAction(ActionManager::ACTION_DOCUMENT_NEW);
    break;

  case TBB_OPEN:
    Editor.GetActionManager()->CreateAndCompleteAction(ActionManager::ACTION_DOCUMENT_OPEN);
    break;

  case TBB_SAVE:
    Editor.GetActionManager()->CreateAndCompleteAction(ActionManager::ACTION_DOCUMENT_SAVE);
    break;

  case TBB_CUT:
    Editor.GetActionManager()->CreateAndCompleteAction(ActionManager::ACTION_CLIPBOARD_CUT);
    break;

  case TBB_COPY:
    Editor.GetActionManager()->CreateAndCompleteAction(ActionManager::ACTION_CLIPBOARD_COPY);
    break;

  case TBB_PASTE:
    Editor.GetActionManager()->CreateAndCompleteAction(ActionManager::ACTION_CLIPBOARD_PASTE);
    break;

  case TBB_UNDO:
    Editor.GetActionManager()->CreateAndCompleteAction(ActionManager::ACTION_UNDO);
    break;

  case TBB_REDO:
    Editor.GetActionManager()->CreateAndCompleteAction(ActionManager::ACTION_REDO);
    break;
  }
}


void ToolBar::UpdateIconState()
{
}



// -- EOF

