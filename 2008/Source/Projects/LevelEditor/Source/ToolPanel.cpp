
#include "Editor.h"
#include "ToolPanel.h"
#include "EditorResource.h"


ToolPanel::ToolPanel(const wxPoint &pos, const wxSize &size, UINT id, bool showBorder)
: EditorFrameToolbar(pos, size, id, showBorder)
{
  m_ToolAxis = TA_X;
  m_ToolType = TT_SELECT;
}


ToolPanel::~ToolPanel()
{
}


// Need to update icons, etc...


void ToolPanel::Init()
{
  BeginBuildToolbar(EDT_RIGHT_PANEL, wxVERTICAL);

  wxToolBar *pToolBar = GetToolBar();
  pToolBar->SetToolBitmapSize(wxSize(24, 24));

  FileHandle hTestSelect = Application.GetTextureDatabase()->FindFileHandle("Select.png");
  FileHandle hTestMove   = Application.GetTextureDatabase()->FindFileHandle("Move.png");
  FileHandle hTestRotate = Application.GetTextureDatabase()->FindFileHandle("Rotate.png");
  FileHandle hTestScale  = Application.GetTextureDatabase()->FindFileHandle("Scale.png");
  FileHandle hTestAxisX  = Application.GetTextureDatabase()->FindFileHandle("AxisX.png");
  FileHandle hTestAxisY  = Application.GetTextureDatabase()->FindFileHandle("AxisY.png");
  FileHandle hTestAxisZ  = Application.GetTextureDatabase()->FindFileHandle("AxisZ.png");
  FileHandle hTestAxisXY = Application.GetTextureDatabase()->FindFileHandle("AxisXY.png");
  FileHandle hTestAxisYZ = Application.GetTextureDatabase()->FindFileHandle("AxisYZ.png");
  FileHandle hTestAxisZX = Application.GetTextureDatabase()->FindFileHandle("AxisZX.png");

  AddRadioTool(TPB_SELECT,  hTestSelect, MakeCallback(&ToolPanel::OnToolEvent, this));
  AddRadioTool(TPB_MOVE,    hTestMove,   MakeCallback(&ToolPanel::OnToolEvent, this));
  AddRadioTool(TPB_ROTATE,  hTestRotate, MakeCallback(&ToolPanel::OnToolEvent, this));
  AddRadioTool(TPB_SCALE,   hTestScale,  MakeCallback(&ToolPanel::OnToolEvent, this));

  AddSeperator();

  AddRadioTool(TPB_X,  hTestAxisX,  MakeCallback(&ToolPanel::OnToolEvent, this));
  AddRadioTool(TPB_Y,  hTestAxisY,  MakeCallback(&ToolPanel::OnToolEvent, this));
  AddRadioTool(TPB_Z,  hTestAxisZ,  MakeCallback(&ToolPanel::OnToolEvent, this));
  AddRadioTool(TPB_XY, hTestAxisXY, MakeCallback(&ToolPanel::OnToolEvent, this));
  AddRadioTool(TPB_YZ, hTestAxisYZ, MakeCallback(&ToolPanel::OnToolEvent, this));
  AddRadioTool(TPB_ZX, hTestAxisZX, MakeCallback(&ToolPanel::OnToolEvent, this));

  EndBuildToolbar();
}


void ToolPanel::OnToolEvent(int id)
{
  switch (id)
  {
    case TPB_SELECT:  m_ToolType = TT_SELECT; break;
    case TPB_MOVE:    m_ToolType = TT_MOVE;   break;
    case TPB_ROTATE:  m_ToolType = TT_ROTATE; break;
    case TPB_SCALE:   m_ToolType = TT_SCALE;  break;
    case TPB_X:       m_ToolAxis = TA_X;      break;
    case TPB_Y:       m_ToolAxis = TA_Y;      break;
    case TPB_Z:       m_ToolAxis = TA_Z;      break;
    case TPB_XY:      m_ToolAxis = TA_XY;     break;
    case TPB_YZ:      m_ToolAxis = TA_YZ;     break;
    case TPB_ZX:      m_ToolAxis = TA_ZX;     break;
  }
}


void ToolPanel::UpdateIconState()
{
}


// -- EOF

