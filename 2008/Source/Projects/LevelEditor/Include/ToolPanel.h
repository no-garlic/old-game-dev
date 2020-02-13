
#ifndef __TOOL_PANEL_H_
#define __TOOL_PANEL_H_


#include "libEngine.h"
#include "libEditor.h"


class ToolPanel : public EditorFrameToolbar
{
public:
  ToolPanel(const wxPoint &pos, const wxSize &size, UINT id, bool showBorder = false);
  virtual ~ToolPanel();

  void Init();

  void UpdateIconState();

  void OnToolEvent(int id);

  enum ToolAxis
  {
    TA_X,
    TA_Y,
    TA_Z,
    TA_XY,
    TA_YZ,
    TA_ZX
  };

  enum ToolType
  {
    TT_SELECT,
    TT_MOVE,
    TT_ROTATE,
    TT_SCALE
  };

  ToolAxis GetToolAxis() { return m_ToolAxis; }
  ToolType GetToolType() { return m_ToolType; }

protected:
  ToolAxis m_ToolAxis;
  ToolType m_ToolType;

};



#endif // __TOOL_PANEL_H_

// -- EOF

