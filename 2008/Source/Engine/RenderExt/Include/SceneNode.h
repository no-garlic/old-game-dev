// ----------------------------------------------------------------------------
// File: SceneNode.h
// Desc: Manages a node in the scenegraph
// Auth: Michael Petrou
// (C) Copyright: 2005
// ----------------------------------------------------------------------------
#ifndef __SCENE_NODE_H_
#define __SCENE_NODE_H_


// ----------------------------------------------------------------------------
// Standard includes
// ----------------------------------------------------------------------------
#include "libStandard.h"
#include "libRenderCore.h"
#include "libMaths.h"
#include "TransformNode.h"
#include "RenderList.h"


// ----------------------------------------------------------------------------
// Name: SceneNode  (class)
// Desc: A scenegraph node that manages mehs rendering
// ----------------------------------------------------------------------------
class SceneNode : public TransformNode
{
public:
  // --------------------------------------------------------------------------
  // Constructors and destructor
  // --------------------------------------------------------------------------
  SceneNode();
  explicit SceneNode(const String &name);
  virtual ~SceneNode();

  // --------------------------------------------------------------------------
  // The node type
  // --------------------------------------------------------------------------
  static const uint Type = SCENE_NODE;

  // --------------------------------------------------------------------------
  // Traversals
  // --------------------------------------------------------------------------
  void Cull(RenderList &renderList, const Frustum &frustum, 
    bool shadowCastersOnly = false);

  // --------------------------------------------------------------------------
  // Save and load the scene file
  // --------------------------------------------------------------------------
  bool Save(FileHandle handle) const  { return Node::Save(handle); }
  bool Load(FileHandle handle)        { return Node::Load(handle); }

protected:
  // --------------------------------------------------------------------------
  // Loading and saving
  // --------------------------------------------------------------------------
  friend class Node;  
  virtual bool LoadInternal(const ConfigSection &data);
  virtual bool SaveInternal(ConfigSection &data) const;

  // --------------------------------------------------------------------------
  // Protected methods
  // --------------------------------------------------------------------------
  void CullTraverse(Node *pNode, const Frustum &frustum, 
    RenderList &renderList, bool acceptAll, bool shadowCastersOnly);
  bool SaveTraverse(Node *pNode, FILE *pFile);

  // --------------------------------------------------------------------------
  // Protected members
  // --------------------------------------------------------------------------
  MatrixStack   m_MatrixStack;
  Stack<uint>   m_CullFlags;

}; // class SceneNode


#endif // __SCENE_NODE_H_

// -- EOF
