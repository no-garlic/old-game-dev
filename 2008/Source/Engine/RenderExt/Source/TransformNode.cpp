// ----------------------------------------------------------------------------
// File: TransformNode.cpp
// Desc: Manages a node in the scenegraph
// Auth: Michael Petrou
// (C) Copyright: 2005
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// Includes
// ----------------------------------------------------------------------------
#include "TransformNode.h"


// ----------------------------------------------------------------------------
// Name: TransformNode::TransformNode
// Desc: Constructor
// ----------------------------------------------------------------------------
TransformNode::TransformNode()
: Node(),
  m_Transform (MatrixIdentity)
{
  REF_COUNT_CTOR(TransformNode);
  m_Type = TransformNode::Type;
} // TransformNode


// ----------------------------------------------------------------------------
// Name: TransformNode::TransformNode
// Desc: Constructor
// Parm: const String &name - the node name
// ----------------------------------------------------------------------------
TransformNode::TransformNode(const String &name)
: Node(name),
  m_Transform (MatrixIdentity)
{
  REF_COUNT_CTOR(TransformNode);
  m_Type = TransformNode::Type;
} // TransformNode


// ----------------------------------------------------------------------------
// Name: TransformNode::~TransformNode
// Desc: Destructor
// ----------------------------------------------------------------------------
TransformNode::~TransformNode()
{
  REF_COUNT_DTOR(TransformNode);
} // ~TransformNode


// ----------------------------------------------------------------------------
// Name: TransformNode::SetTransform
// Desc: Set the transform
// Parm: const Matrix &matrix - the transform matrix
// ----------------------------------------------------------------------------
void TransformNode::SetTransform(const Matrix &matrix)
{
  m_Transform   = matrix;
  m_BoundsDirty = true;
} // SetTransform


// ----------------------------------------------------------------------------
// Name: TransformNode::LoadInternal
// Desc: Load the specific date for this node from the config data
// Parm: const ConfigSection &data - the config data to load from
// ----------------------------------------------------------------------------
bool TransformNode::LoadInternal(const ConfigSection &data)
{
  Matrix matrix;
  if (!matrix.FromString(data("_M1"), 0) || !matrix.FromString(data("_M2"), 1) ||
    !matrix.FromString(data("_M3"), 2) || !matrix.FromString(data("_M4"), 3))
  {
    LOG_ERROR << "Failed to read the matrix for the transform node: " << data.Name << ENDLOG;
    return false;
  }

  String shadowCmd = data("CastShadow");
  if (StrICmp(shadowCmd, "enabled"))
    m_Flags = CAST_SHADOWS_ENABLED;
  else if (StrICmp(shadowCmd, "disabled"))
    m_Flags = CAST_SHADOWS_DISABLED;
  else
    m_Flags = 0;

  // Set the matrix
  SetTransform(matrix);

  // Process all other children
  return Node::LoadInternal(data);
}


// ----------------------------------------------------------------------------
// Name: TransformNode::SaveInternal
// Desc: Save the specific date for this node to the config data
// Parm: const ConfigSection &data - the config data to save to
// ----------------------------------------------------------------------------
bool TransformNode::SaveInternal(ConfigSection &data) const
{
  if (HasFlags(CAST_SHADOWS_ENABLED))
    data.Set("CastShadow", String("Enabled"));
  else if (HasFlags(CAST_SHADOWS_DISABLED))
    data.Set("CastShadow", String("Disabled"));
  else
    data.Set("CastShadow", String("Inherit"));

  data.Set("_M1", m_Transform.ToString(0));
  data.Set("_M2", m_Transform.ToString(1));
  data.Set("_M3", m_Transform.ToString(2));
  data.Set("_M4", m_Transform.ToString(3));

  return Node::SaveInternal(data);
}


// -- EOF



