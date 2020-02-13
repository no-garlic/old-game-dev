
#ifndef __EDITOR_SCENE_PANEL_H_
#define __EDITOR_SCENE_PANEL_H_


#include "libEngine.h"
#include "libEditor.h"
#include "StaticMeshNode.h"


class EditorScenePanel : public wxPanel
{
public:
  EditorScenePanel(wxWindow *pParent);
  virtual ~EditorScenePanel();

  TreeView *GetTreeView() { return m_pTreeView; }

  void Clear();

  void SetSelectedStaticMeshNode(StaticMeshNode *pNode) { m_pStaticMeshSel = pNode; }
  StaticMeshNode *GetSelectedStaticMeshNode() const     { return m_pStaticMeshSel;  }

protected:
  DECLARE_EVENT_TABLE();

  void OnItemChanged(wxTreeEvent &event);
  void OnItemRightClick(wxTreeEvent &event);

  void OnBeginDrag(wxTreeEvent &event);
  void OnEndDrag(wxTreeEvent &event);

  void OnBeginEdit(wxTreeEvent &event);
  void OnEndEdit(wxTreeEvent &event);

  void OnKeyDown(wxTreeEvent& event);

  void OnMenuCreateGroup(wxCommandEvent &event);
  void OnMenuCreateMesh(wxCommandEvent &event);

  void OnMenuRenderFlag(wxCommandEvent &event);
  void OnMenuPickableFlag(wxCommandEvent &event);
  void OnMenuFrozenFlag(wxCommandEvent &event);
  void OnMenuDeleteSelected(wxCommandEvent &event);

private:
  TreeView        *m_pTreeView;
  StaticMeshNode  *m_pStaticMeshSel;
  String           m_DragItemPath;

};


#endif // __EDITOR_SCENE_PANEL_H_

// -- EOf


