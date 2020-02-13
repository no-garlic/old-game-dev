
#ifndef __TOOL_BAR_H_
#define __TOOL_BAR_H_


#include "libEngine.h"
#include "libEditor.h"


class ToolBar : public EditorFrameToolbar
{
public:
  ToolBar(const wxPoint &pos, const wxSize &size, UINT id, bool showBorder = false);
  virtual ~ToolBar();

  void Init();

  void UpdateIconState();

  void OnToolEvent(int id);

protected:

};



#endif // __TOOL_BAR_H_

// -- EOF

