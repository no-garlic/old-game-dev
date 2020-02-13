// ----------------------------------------------------------------------------
// File: Node.cpp
// Desc: Manages a node in the scenegraph
// Auth: Michael Petrou
// (C) Copyright: 2005
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// Inlcudes
// ----------------------------------------------------------------------------
#include "Node.h"
#include "TransformNode.h"
#include "SceneNode.h"
#include "MeshNode.h"


// ----------------------------------------------------------------------------
// Name: Node::Node
// Desc: Constructor
// ----------------------------------------------------------------------------
Node::Node()
: m_pParentNode       (NULL),
  m_BoundsDirty       (true),
  m_Flags             (0)
{
  REF_COUNT_CTOR(Node);
  m_Type = Node::Type;
} // Node


// ----------------------------------------------------------------------------
// Name: Node::Node
// Desc: Constructor
// Parm: const String &name - the node name
// ----------------------------------------------------------------------------
Node::Node(const String &name)
: m_pParentNode       (NULL),
  m_BoundsDirty       (true),
  m_Flags             (0),
  m_Name              (name)
{
  REF_COUNT_CTOR(Node);
  m_Type = Node::Type;
} // Node
  

// ----------------------------------------------------------------------------
// Name: Node::~Node
// Desc: Destructor
// ----------------------------------------------------------------------------
Node::~Node()
{
  REF_COUNT_DTOR(Node);

  // Delete all child nodes
  NodePtrArray::iterator nodeIter(m_ChildArray.begin()), nodeEnd(m_ChildArray.end());
  for (; nodeIter != nodeEnd; ++nodeIter)
    delete (*nodeIter);
} // ~Node


// ----------------------------------------------------------------------------
// Name: Node::AddChild
// Desc: Add a child node to this node
// Parm: Node *pNode - the child node
// Retn: uint        - the index of the new child or INVALID_CHILD if the child 
//                     has already been parented.
// ----------------------------------------------------------------------------
uint Node::AddChild(Node *pNode)
{
  // Make sure the child is not already parented
  if (pNode->m_pParentNode)
    return Node::INVALID_CHILD;

  // Add the child to the array
  m_ChildArray.push_back(pNode);

  // Set the child parent
  pNode->m_pParentNode = this;

  // Recalculate the bounds
  SetBoundsDirty();

  // Return the index
  return m_ChildArray.size() - 1;
} // AddChild


// ----------------------------------------------------------------------------
// Name: Node::RemoveChild
// Desc: Remove a child node from this node
// Parm: Node *pNode - the child node to remove
// ----------------------------------------------------------------------------
bool Node::RemoveChild(Node *pNode)
{
  // Get an iterator for the node
  NodePtrArray::iterator iter(m_ChildArray.begin()), end(m_ChildArray.end());
  for (; iter != end; ++iter)
  {
    if ((*iter) == pNode)
    {
      (*iter)->m_pParentNode = NULL;
      m_ChildArray.erase(iter);

      // Recalculate the bounds
      SetBoundsDirty();
      return true;
    }
  }

  return false;
} // RemoveChild


// ----------------------------------------------------------------------------
// Set the bitmask with the flags
// ----------------------------------------------------------------------------
void Node::SetFlags(uint flags)
{
  m_Flags = flags;
}


// ----------------------------------------------------------------------------
// Add the flags to the bitmask
// ----------------------------------------------------------------------------
void Node::AddFlags(uint flags)
{
  m_Flags = m_Flags | flags;
}


// ----------------------------------------------------------------------------
// Cehck if the bitmask contains the flags
// ----------------------------------------------------------------------------
bool Node::HasFlags(uint flags) const
{
  return ((m_Flags & flags) != 0);
}


// ----------------------------------------------------------------------------
// Remove the flags from the bitmask
// ----------------------------------------------------------------------------
void Node::RemoveFlags(uint flags)
{
  m_Flags = (m_Flags & ~flags);
}


// ----------------------------------------------------------------------------
// Get the flags
// ----------------------------------------------------------------------------
uint Node::GetFlags() const
{
  return m_Flags;
}


// ----------------------------------------------------------------------------
// Name: Node::SetBoundsDirty
// Desc: Set the node bounds dirty
// ----------------------------------------------------------------------------
void Node::SetBoundsDirty()
{
  // Tell this node to recalculate it's bounds
  m_BoundsDirty = true;

  // Tell the parent node to recalculate it's bounds
  if (m_pParentNode)
    m_pParentNode->SetBoundsDirty();
} // SetBoundsDirty


// ----------------------------------------------------------------------------
// Name: Node::GetBSphere
// Desc: Get the bounding shpere
// Retn: const Sphere & - the sphere
// ----------------------------------------------------------------------------
const Sphere &Node::GetBSphere() const
{
  if (m_BoundsDirty)
    RecalculateBSphere();

  return m_BoundingSphere;
} // GetBSphere


// ----------------------------------------------------------------------------
// Name: Node::RecalculateBSphere
// Desc: Recalculate the bounding sphere
// ----------------------------------------------------------------------------
void Node::RecalculateBSphere() const
{
  // Reset the bounding shpere
  m_BoundingSphere.Reset();
  m_BoundsDirty = false;

  // Flag for first use
  bool firstSphere = true;

  // Process all children
  NodePtrArray::const_iterator nodeIter(m_ChildArray.begin()), nodeEnd(m_ChildArray.end());
  for (; nodeIter != nodeEnd; ++nodeIter)
  {
    // Get the bounding sphere and transform it if required
    const Node *pNode = *nodeIter;
    Sphere sphere = pNode->GetBSphere();

    if (firstSphere)
    {
      // If this is the first sphere, initialise our bounding sphere
      m_BoundingSphere = sphere;
      firstSphere = false;
    } // if
    else
    {
      // Maximize the bounding sphere to also include this sphere
      m_BoundingSphere.Maximize(sphere);
    } // else
  } // for

  if (IsOfType(TRANSFORM_NODE))
  {
    const Matrix &matrix = static_cast<const TransformNode *>(this)->GetTransform();
    m_BoundingSphere.TransformAndScale(matrix);
  } // if
} // RecalculateBSphere


// ----------------------------------------------------------------------------
// Name: Node::LoadInternal
// Desc: Load the specific date for this node from the config data
// Parm: const ConfigSection &data - the config data to load from
// ----------------------------------------------------------------------------
bool Node::LoadInternal(const ConfigSection &data)
{
  m_Name = data.Name;

  ConfigSectionMap::const_iterator iter(data.ChildSections.begin()), end(data.ChildSections.end());
  for (; iter != end; ++iter)
  {
    const ConfigSection &childData = iter->second;

    if (childData.Type == "SceneNode")
    {
      SceneNode *pNode = new SceneNode(childData.Name);
      AddChild(pNode);
      if (!pNode->LoadInternal(childData))
      {
        LOG_ERROR << "Failed to load the scene node: " << childData.Name << ENDLOG;
        return false;
      }
    }
    else if (childData.Type == "MeshNode")
    {
      MeshNode *pNode = new MeshNode(childData.Name);
      AddChild(pNode);
      if (!pNode->LoadInternal(childData))
      {
        LOG_ERROR << "Failed to load the mesh node: " << childData.Name << ENDLOG;
        return false;
      }
    }
    else if (childData.Type == "TransformNode")
    {
      TransformNode *pNode = new TransformNode(childData.Name);
      AddChild(pNode);
      if (!pNode->LoadInternal(childData))
      {
        LOG_ERROR << "Failed to load the transform node: " << childData.Name << ENDLOG;
        return false;
      }
    }
  }
  return true;
}


// ----------------------------------------------------------------------------
// Name: Node::SaveInternal
// Desc: Save the specific date for this node to the config data
// Parm: const ConfigSection &data - the config data to save to
// ----------------------------------------------------------------------------
bool Node::SaveInternal(ConfigSection &data) const
{
  data.Name = GetName();

  if (HasFlags(CAST_SHADOWS_ENABLED))
    data.Set("CastShadow", String("Enabled"));
  else if (HasFlags(CAST_SHADOWS_DISABLED))
    data.Set("CastShadow", String("Disabled"));
  else
    data.Set("CastShadow", String("Inherit"));

  String typeName;
  switch (m_Type)
  {
    case SceneNode::Type:
      typeName = "SceneNode";
      break;
    case MeshNode::Type:
      typeName = "MeshNode";
      break;
    case TransformNode::Type:
      typeName = "TransformNode";
      break;
    default:
      LOG_ERROR << "Unsupported node type: " << m_Type << ENDLOG;
      return false;
  }

  data.Name = m_Name;
  data.Type = typeName;

  NodePtrArray::const_iterator nodeIter(m_ChildArray.begin()), nodeEnd(m_ChildArray.end());
  for (; nodeIter != nodeEnd; ++nodeIter)
  {
    const Node *pNode = (*nodeIter);
    ConfigSection &childSection = data.AddSection("", pNode->GetName());
    if (!pNode->SaveInternal(childSection))
    {
      LOG_ERROR << "Failed to save the node: " << pNode->GetName() << ENDLOG;
      return false;
    }
  }

  return true;
}


// ----------------------------------------------------------------------------
// Name: Node::Load
// Desc: Load the node and all child nodes from a file
// Parm: FileHandle handle - the file to load from
// ----------------------------------------------------------------------------
bool Node::Load(FileHandle handle)
{
  ConfigFile cfg;

  m_FileHandle = handle;

  if (!cfg.Load(handle.GetAbsoluteFilename()))
  {
    LOG_ERROR << "Failed to load the file: " << handle.GetAbsoluteFilename() << ENDLOG;
    return false;
  }

  if (cfg.GetSections().size() != 1)
  {
    LOG_ERROR << "The scene file contains more than 1 root section" << ENDLOG;
    return false;
  }

  const ConfigSection &childData = cfg.GetSections().begin()->second;

  String shadowCmd = childData("CastShadow");
  if (StrICmp(shadowCmd, "enabled"))
    m_Flags = CAST_SHADOWS_ENABLED;
  else if (StrICmp(shadowCmd, "disabled"))
    m_Flags = CAST_SHADOWS_DISABLED;
  else
    m_Flags = 0;

  if (childData.Type == "SceneNode")
  {
    if (!IsOfType(SceneNode::Type))
    {
      LOG_ERROR << "Incompatible node type: a SceneNode was expected" << ENDLOG;
      return false;
    }
    return static_cast<SceneNode *>(this)->LoadInternal(childData);
  }
  else if (childData.Type == "MeshNode")
  {
    if (!IsOfType(MeshNode::Type))
    {
      LOG_ERROR << "Incompatible node type: a MeshNode was expected" << ENDLOG;
      return false;
    }
    return static_cast<MeshNode *>(this)->LoadInternal(childData);
  }
  else if (childData.Type == "TransformNode")
  {
    if (!IsOfType(TransformNode::Type))
    {
      LOG_ERROR << "Incompatible node type: a TransformNode was expected" << ENDLOG;
      return false;
    }
    return static_cast<TransformNode *>(this)->LoadInternal(childData);
  }

  LOG_ERROR << "Unknown node type: " << childData.Type << ENDLOG;
  return false;
}


// ----------------------------------------------------------------------------
// Name: Node::Save
// Desc: Save the node and all child nodes to a file
// Parm: FileHandle handle - the file to save to
// ----------------------------------------------------------------------------
bool Node::Save(FileHandle handle) const
{
  m_FileHandle = handle;

  String typeName;
  switch (m_Type)
  {
  case SceneNode::Type:
    typeName = "SceneNode";
    break;
  case MeshNode::Type:
    typeName = "MeshNode";
    break;
  case TransformNode::Type:
    typeName = "TransformNode";
    break;
  default:
    LOG_ERROR << "Unsupported node type: " << m_Type << ENDLOG;
    return false;
  }

  ConfigFile cfg;
  ConfigSection &section = cfg.AddSection(typeName, m_Name);

  if (!this->SaveInternal(section))
  {
    LOG_ERROR << "Failed to prepare the scenegraph for saving" << ENDLOG;
    return false;
  }

  if (!cfg.SaveAs(handle.GetAbsoluteFilename()))
  {
    LOG_ERROR << "Failed to save the scenegraph to the file: " << handle.GetAbsoluteFilename() << ENDLOG;
    return false;
  }

  return true;
}



// -- EOF

