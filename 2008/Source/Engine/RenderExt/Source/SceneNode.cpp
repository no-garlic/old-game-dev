// ----------------------------------------------------------------------------
// File: SceneNode.cpp
// Desc: Manages a node in the scenegraph
// Auth: Michael Petrou
// (C) Copyright: 2005
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// Includes
// ----------------------------------------------------------------------------
#include "SceneNode.h"
#include "MeshNode.h"
#include "TransformNode.h"


// ----------------------------------------------------------------------------
// Name: SceneNode::SceneNode
// Desc: Constructor
// ----------------------------------------------------------------------------
SceneNode::SceneNode()
: TransformNode()
{
  REF_COUNT_CTOR(SceneNode);

  m_Type = SceneNode::Type;
} // SceneNode


// ----------------------------------------------------------------------------
// Name: SceneNode::SceneNode
// Desc: Constructor
// Parm: const String &name - the node name
// ----------------------------------------------------------------------------
SceneNode::SceneNode(const String &name)
: TransformNode(name)
{
  REF_COUNT_CTOR(SceneNode);

  m_Type = SceneNode::Type;
} // SceneNode


// ----------------------------------------------------------------------------
// Name: SceneNode::~SceneNode
// Desc: Destructor
// ----------------------------------------------------------------------------
SceneNode::~SceneNode()
{
  REF_COUNT_DTOR(SceneNode);
} // ~SceneNode


// ----------------------------------------------------------------------------
// Name: SceneNode::Cull
// Desc: Cull the scene
// Parm: RenderList &renderList - the render list to add the render items to
// ----------------------------------------------------------------------------
void SceneNode::Cull(RenderList &renderList, const Frustum &frustum, bool shadowCastersOnly)
{
  // Reset the matrix stack
  m_MatrixStack.LoadIdentity();
  m_CullFlags.push(CAST_SHADOWS_ENABLED);

  // Recursively cull the node hierarchy
  CullTraverse(this, frustum, renderList, false, shadowCastersOnly);

  // Ensure the cull flags are emptied
  while (!m_CullFlags.empty())
    m_CullFlags.pop();
} // Cull


// ----------------------------------------------------------------------------
// Name: SceneNode::CullTraverse
// Desc: Recursive cull function
// Parm: Node *pNode             - the node to address
// Parm: const Frustum &frustum  - the view frustum
// Parm: RenderList &renderList  - the render list to add the render items to
// Parm: bool acceptAll          - do we accept all or test the bounds
// ----------------------------------------------------------------------------
void SceneNode::CullTraverse(Node *pNode, const Frustum &frustum, RenderList &renderList, bool acceptAll, bool shadowCastersOnly)
{
  // Get the flags
  uint nodeFlags = pNode->GetFlags();
  uint cullFlags = m_CullFlags.top();

  // Does the node have a transform
  bool hasTransform = pNode->IsOfType(TRANSFORM_NODE);
  bool hasGeometry  = pNode->IsOfType(MESH_NODE);
  bool hasFlags     = (nodeFlags != 0);

  if (hasFlags)
  {
    bool nodeShadowEnabled  = ((nodeFlags & CAST_SHADOWS_ENABLED)  != 0);
    bool nodeShadowDisabled = ((nodeFlags & CAST_SHADOWS_DISABLED) != 0);

    bool cullShadowEnabled  = ((cullFlags & CAST_SHADOWS_ENABLED)  != 0);
    bool cullShadowDisabled = ((cullFlags & CAST_SHADOWS_DISABLED) != 0);

    if (cullShadowDisabled && nodeShadowEnabled)
      m_CullFlags.push(CAST_SHADOWS_ENABLED);
    else if (cullShadowEnabled && nodeShadowDisabled)
      m_CullFlags.push(CAST_SHADOWS_DISABLED);
    else
      hasFlags = false;
  }

  // Push the matrix onto the stack
  if (hasTransform)
  {
    m_MatrixStack.Push();
    m_MatrixStack.MultMatrix(static_cast<TransformNode *>(pNode)->GetTransform());
  } // if

  // Get the matrix for this node
  const Matrix &matrix = m_MatrixStack.GetTop();

  // Flags for mesh operations
  bool addMeshes  = false;
  bool testMeshes = false;

  // Do we need to test for visibility
  if (acceptAll)
  {
    addMeshes = true;
  } // if
  else
  {
    // Test the bounding sphere against the frustum
    int testResult = frustum.Intersects(pNode->GetBSphere(), matrix);

    switch (testResult)
    {
    case Frustum::IN_FRUSTUM:
      addMeshes = true;
      break;

    case Frustum::PARTIAL:
      addMeshes  = true;
      testMeshes = true;
      break;
    };
  } // else

  // Add all meshes to the render list
  if (addMeshes && hasGeometry)
  {
    // Add the visible mesh lod's to the render list
    if (shadowCastersOnly == false || (m_CullFlags.top() != CAST_SHADOWS_DISABLED))
      static_cast<MeshNode *>(pNode)->AddToRenderList(frustum, m_MatrixStack.GetTop(), renderList, testMeshes);
  } // if

  // Traverse all children
  for (uint i = 0; i < pNode->GetChildCount(); i++)
    CullTraverse(pNode->GetChild(i), frustum, renderList, (addMeshes && !testMeshes), shadowCastersOnly);

  // Pop the matrix from the stack
  if (hasTransform)
    m_MatrixStack.Pop();

  // Pop the flags from the stack
  if (hasFlags)
    m_CullFlags.pop();
} // CullTraverse


// ----------------------------------------------------------------------------
// Name: SceneNode::LoadInternal
// Desc: Load the specific date for this node from the config data
// Parm: const ConfigSection &data - the config data to load from
// ----------------------------------------------------------------------------
bool SceneNode::LoadInternal(const ConfigSection &data)
{
  return TransformNode::LoadInternal(data);
}


// ----------------------------------------------------------------------------
// Name: SceneNode::SaveInternal
// Desc: Save the specific date for this node to the config data
// Parm: const ConfigSection &data - the config data to save to
// ----------------------------------------------------------------------------
bool SceneNode::SaveInternal(ConfigSection &data) const
{
  return TransformNode::SaveInternal(data);
}


// -- EOF


