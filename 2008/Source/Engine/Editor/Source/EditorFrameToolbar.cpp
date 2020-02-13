
#include "EditorFrameToolbar.h"
#include <wx\image.h>


BEGIN_EVENT_TABLE(EditorFrameToolbar, EditorFrame)
  EVT_TOOL(wxID_ANY, EditorFrameToolbar::OnToolEnter)
END_EVENT_TABLE()


EditorFrameToolbar::EditorFrameToolbar(const wxPoint &pos, const wxSize &size, UINT id, bool showBorder)
: EditorFrame(pos, size, id, showBorder)
{
  m_pToolBar = NULL;
}


EditorFrameToolbar::~EditorFrameToolbar()
{
  Map<int, Callback<void, int> *>::iterator iter(m_Callbacks.begin()), end(m_Callbacks.end());
  for (; iter != end; ++iter)
  {
    delete iter->second;
  }
}


void EditorFrameToolbar::BeginBuildToolbar(wxWindowID id, long style)
{
  ASSERT(m_pToolBar == NULL, "Cannot build the toolbar twice");
  m_pToolBar = CreateToolBar(style, id);
}


void EditorFrameToolbar::AddTool(int id, FileHandle bitmap, const Callback<void, int> &cb)
{
  NULL_ASSERT(m_pToolBar);

  wxImage image;
  image.LoadFile(bitmap.GetAbsoluteFilename().c_str());
  // ??? image.SetMaskColour(0, 255, 255);
  wxBitmap bmp(image);

  m_pToolBar->AddTool(id, wxEmptyString, bmp);
  m_Callbacks[id] = cb.Clone();
}


void EditorFrameToolbar::AddRadioTool(int id, FileHandle bitmap, const Callback<void, int> &cb)
{
  NULL_ASSERT(m_pToolBar);

  wxImage image;
  image.LoadFile(bitmap.GetAbsoluteFilename().c_str());
  wxBitmap bmp(image);

  m_pToolBar->AddRadioTool(id, wxEmptyString, bmp);
  m_Callbacks[id] = cb.Clone();
}


void EditorFrameToolbar::AddCheckTool(int id, FileHandle bitmap, const Callback<void, int> &cb)
{
  NULL_ASSERT(m_pToolBar);

  wxImage image;
  image.LoadFile(bitmap.GetAbsoluteFilename().c_str());
  // ?? image.SetMaskColour(0, 255, 255);
  wxBitmap bmp(image);

  m_pToolBar->AddCheckTool(id, wxEmptyString, bmp);
  m_Callbacks[id] = cb.Clone();
}


void EditorFrameToolbar::AddSeperator()
{
  NULL_ASSERT(m_pToolBar);
  m_pToolBar->AddSeparator();
}


void EditorFrameToolbar::EndBuildToolbar()
{
  NULL_ASSERT(m_pToolBar);
  m_pToolBar->Realize();
}


void EditorFrameToolbar::OnToolEnter(wxCommandEvent& event)
{
  int id = event.GetId();

  Callback<void, int> *pCb = m_Callbacks[id];
  NULL_ASSERT(pCb);

  (*pCb)(id);
}


void EditorFrameToolbar::EnableTool(int id, bool enabled)
{
  NULL_ASSERT(m_pToolBar);
  m_pToolBar->EnableTool(id, enabled);
}


bool EditorFrameToolbar::GetToolState(int id)
{
  NULL_ASSERT(m_pToolBar);
  return m_pToolBar->GetToolState(id);
}


// -- EOF


