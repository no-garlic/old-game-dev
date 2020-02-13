
#ifndef __STATIC_MESH_UTILS_H_
#define __STATIC_MESH_UTILS_H_


#include "libEngine.h"
#include "libEditor.h"


class StaticMeshUtils
{
public:
  // Add a new static mesh node to the scene tree
  static bool AddNode(const String &path, 
                      const String &filename, 
                      const Vec3   &pos   = Vec3(0.0f, 0.0f, 0.0f), 
                      const Vec3   &rot   = Vec3(0.0f, 0.0f, 0.0f), 
                      const Vec3   &scale = Vec3(1.0f, 1.0f, 1.0f));

  // Delete a static mesh node from the scene tree
  static bool DeleteNode(const String &path);

  // Duplicate a static mesh node in the scene tree
  static bool DuplicateNode(const String &path, const String &destPath);

  // Move a static mesh in the scene
  static bool MoveNode(const String &path, const Vec3 &pos, const Vec3 &rot, const Vec3 &scale);

  // Relocate a static mesh in the tree view
  static bool RelocateNode(const String &srcPath, const String &dstPath);

};


#endif // __STATIC_MESH_UTILS_H_

// -- EOF

