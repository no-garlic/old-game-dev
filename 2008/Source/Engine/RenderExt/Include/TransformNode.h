// ----------------------------------------------------------------------------
// File: TransformNode.h
// Desc: Manages a node in the scenegraph
// Auth: Michael Petrou
// (C) Copyright: 2005
// ----------------------------------------------------------------------------
#ifndef __TRANSFORM_NODE_H_
#define __TRANSFORM_NODE_H_


// ----------------------------------------------------------------------------
// Standard includes
// ----------------------------------------------------------------------------
#include "libStandard.h"
#include "libRenderCore.h"
#include "libMaths.h"
#include "Node.h"


// ----------------------------------------------------------------------------
// Name: TransformNode  (class)
// Desc: A scenegraph node that manages transforms
// ----------------------------------------------------------------------------
class TransformNode : public Node
{
public:
  // --------------------------------------------------------------------------
  // Constructors and destructor
  // --------------------------------------------------------------------------
  TransformNode();
  explicit TransformNode(const String &name);
  virtual ~TransformNode();

  // --------------------------------------------------------------------------
  // The node type
  // --------------------------------------------------------------------------
  static const uint Type = TRANSFORM_NODE;

  // --------------------------------------------------------------------------
  // The transform matrix
  // --------------------------------------------------------------------------
  void SetTransform(const Matrix &matrix);
  const Matrix &GetTransform() const        { return m_Transform; }

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
  // Protected members
  // --------------------------------------------------------------------------
  Matrix    m_Transform;  // The local transform

}; // class TransformNode


#endif // __TRANSFORM_NODE_H_

// -- EOF
