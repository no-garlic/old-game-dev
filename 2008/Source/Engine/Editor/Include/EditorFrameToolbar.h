
#ifndef __EDITOR_FRAME_TOOLBAR_H_
#define __EDITOR_FRAME_TOOLBAR_H_


#include "libRenderExt.h"
#include "EditorFrame.h"
#include <wx/toolbar.h>


class EditorFrameToolbar : public EditorFrame
{
public:
  EditorFrameToolbar(const wxPoint &pos, const wxSize &size, UINT id, bool showBorder = false);
  virtual ~EditorFrameToolbar();

  void BeginBuildToolbar(wxWindowID id, long style);
  void AddTool(int id, FileHandle bitmap, const Callback<void, int> &cb);
  void AddRadioTool(int id, FileHandle bitmap, const Callback<void, int> &cb);
  void AddCheckTool(int id, FileHandle bitmap, const Callback<void, int> &cb);
  void AddSeperator();
  void EndBuildToolbar();

  void EnableTool(int id, bool enabled);
  bool GetToolState(int id);

protected:
  DECLARE_EVENT_TABLE();
  void OnToolEnter(wxCommandEvent& event);

private:
  wxToolBar                      *m_pToolBar;
  Map<int, Callback<void, int> *> m_Callbacks;

};


#endif // __EDITOR_FRAME_TOOLBAR_H_


// -- EOF

