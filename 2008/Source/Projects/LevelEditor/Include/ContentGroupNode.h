
#ifndef __CONTENT_GROUP_NODE_H_
#define __CONTENT_GROUP_NODE_H_


#include "libEngine.h"
#include "libEditor.h"


class ContentGroupNode : public TreeNode
{
public:
  explicit ContentGroupNode(wxTreeItemId id);
  virtual ~ContentGroupNode();

  // Create the tree of content
  void Create(const String &groupName);

  // Called when the node is selected and deselected
  virtual void OnEnter();
  virtual void OnLeave();

private:
  String    m_GroupName;

};


#endif // __CONTENT_GROUP_NODE_H_

// -- EOF

