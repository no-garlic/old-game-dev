
#ifndef __EDITOR_CONTENT_PANEL_H_
#define __EDITOR_CONTENT_PANEL_H_


#include "libEngine.h"
#include "libEditor.h"


class EditorContentPanel : public wxPanel
{
public:
  EditorContentPanel(wxWindow *pParent);
  virtual ~EditorContentPanel();

  TreeView *GetTreeView() { return m_pTreeView; }

  void RefreshData();

protected:
  DECLARE_EVENT_TABLE();

  void OnItemChanged(wxTreeEvent &event);
  void OnItemRightClick(wxTreeEvent &event);

private:
  TreeView  *m_pTreeView;

};


#endif // __EDITOR_CONTENT_PANEL_H_

// -- EOf


