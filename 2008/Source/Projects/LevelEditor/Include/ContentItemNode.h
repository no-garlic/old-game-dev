
#ifndef __CONTENT_ITEM_NODE_H_
#define __CONTENT_ITEM_NODE_H_


#include "libEngine.h"
#include "libEditor.h"


class ContentItemNode : public TreeNode
{
public:
  explicit ContentItemNode(wxTreeItemId id);
  virtual ~ContentItemNode();

  // Create the tree of content
  void Create(const String &meshName, const String &fileName);

  // Called when the node is selected and deselected
  virtual void OnEnter();
  virtual void OnLeave();

  const String &GetMeshName() const { return m_MeshName; }
  const String &GetFileName() const { return m_FileName; }

private:
  String    m_MeshName;
  String    m_FileName;

};


#endif // __CONTENT_ITEM_NODE_H_

// -- EOF

