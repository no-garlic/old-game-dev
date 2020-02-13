
#ifndef __EDITOR_PANEL_BOTTOM_H_
#define __EDITOR_PANEL_BOTTOM_H_


#include "libEngine.h"
#include "libEditor.h"
#include "TransformPanel.h"


class EditorPanelBottom : public EditorPanel
{
public:
  EditorPanelBottom(EditorFrame *pParent);
  virtual ~EditorPanelBottom();

  void App();

  TransformPanel *GetTransformPanel() { return m_pTransformPanel; }

protected:
  virtual void UpdateControlLayout();

private:
  TransformPanel   *m_pTransformPanel;

};


#endif // __EDITOR_PANEL_BOTTOM_H_

// -- EOF
