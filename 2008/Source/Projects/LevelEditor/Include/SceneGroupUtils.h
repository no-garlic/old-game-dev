
#ifndef __SCENE_GROUP_UTILS_H_
#define __SCENE_GROUP_UTILS_H_


#include "libEngine.h"
#include "libEditor.h"


class SceneGroupUtils
{
public:
  // Add a new scene group node to the scene tree
  static bool AddNode(const String &path);

  // Delete a scene group node from the scene tree
  static bool DeleteNode(const String &path);

};


#endif // __SCENE_GROUP_UTILS_H_

// -- EOF

