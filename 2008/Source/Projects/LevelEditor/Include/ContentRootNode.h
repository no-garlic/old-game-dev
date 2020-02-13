
#ifndef __CONTENT_ROOT_NODE_H_
#define __CONTENT_ROOT_NODE_H_


#include "libEngine.h"
#include "libEditor.h"


class ContentRootNode : public TreeNode
{
public:
  explicit ContentRootNode(wxTreeItemId id);
  virtual ~ContentRootNode();

  // Create the tree of content
  void Create();

  // Called when the node is selected and deselected
  virtual void OnEnter();
  virtual void OnLeave();

};


#endif // __CONTENT_ROOT_NODE_H_

// -- EOF

