
#ifndef __EDITOR_PANEL_LEFT_H_
#define __EDITOR_PANEL_LEFT_H_


#include "libEngine.h"
#include "libEditor.h"
#include "ToolPanel.h"
#include "EditorContentPanel.h"
#include "EditorScenePanel.h"


class EditorPanelLeft : public EditorPanel
{
public:
  EditorPanelLeft(EditorFrame *pParent);
  virtual ~EditorPanelLeft();

  EditorContentPanel  *GetContentPanel() { return m_pContentPanel; }
  EditorScenePanel    *GetScenePanel()   { return m_pScenePanel;   }

protected:
  virtual void UpdateControlLayout();

private:
  wxBookCtrl          *m_pBook;
  EditorContentPanel  *m_pContentPanel;
  EditorScenePanel    *m_pScenePanel;

};


#endif // __EDITOR_PANEL_LEFT_H_

// -- EOF

