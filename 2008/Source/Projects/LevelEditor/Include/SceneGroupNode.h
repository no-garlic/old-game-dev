
#ifndef __SCENE_GROUP_NODE_H_
#define __SCENE_GROUP_NODE_H_


#include "libEngine.h"
#include "libEditor.h"


class SceneGroupNode : public TreeNode
{
public:
  explicit SceneGroupNode(wxTreeItemId id);
  virtual ~SceneGroupNode();

  void Create();

  // Called when the node is selected and deselected
  virtual void OnEnter();
  virtual void OnLeave();

  // Called when the node is right clicked
  virtual void OnRightClick(const wxPoint &pos);

};


#endif // __SCENE_GROUP_NODE_H_

// -- EOF

