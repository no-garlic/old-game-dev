// ----------------------------------------------------------------------------
// File: Node.h
// Desc: Manages a node in the scenegraph
// Auth: Michael Petrou
// (C) Copyright: 2005
// ----------------------------------------------------------------------------
#ifndef __NODE_H_
#define __NODE_H_


// ----------------------------------------------------------------------------
// Standard includes
// ----------------------------------------------------------------------------
#include "libStandard.h"
#include "libRenderCore.h"
#include "libMaths.h"
#include "Mesh.h"


// ----------------------------------------------------------------------------
// Array of node pointers
// ----------------------------------------------------------------------------
class Node;
typedef Array<Node *> NodePtrArray;


// ----------------------------------------------------------------------------
// Node types (use bit mask to manage inheritance)
// ----------------------------------------------------------------------------
static const uint NODE            = 0x00000000;
static const uint MESH_NODE       = 0x00000001;
static const uint TRANSFORM_NODE  = 0x00000010;
static const uint SCENE_NODE      = 0x00000110;

// ----------------------------------------------------------------------------
// Node flags
// ----------------------------------------------------------------------------
static const uint CAST_SHADOWS_ENABLED    = 0x00000001;
static const uint CAST_SHADOWS_DISABLED   = 0x00000002;


// ----------------------------------------------------------------------------
// Name: Node  (class)
// Desc: A scenegraph node
// ----------------------------------------------------------------------------
class Node : private Unique
{
public:
  // --------------------------------------------------------------------------
  // Constructors and destructor
  // --------------------------------------------------------------------------
  Node();
  explicit Node(const String &name);
  ~Node();

  // --------------------------------------------------------------------------
  // The node type
  // --------------------------------------------------------------------------
  static const uint Type = NODE;
  bool IsOfType(uint type) const          { return (m_Type & type) != 0; }
  bool IsExactType(uint type) const       { return m_Type == type;       }
  uint GetType() const                    { return m_Type;               }

  // --------------------------------------------------------------------------
  // The node name
  // --------------------------------------------------------------------------
  void SetName(const String &name)        { m_Name = name; }
  const String &GetName() const           { return m_Name; }

  // --------------------------------------------------------------------------
  // The file handle
  // --------------------------------------------------------------------------
  const FileHandle &GetFileHandle() const { return m_FileHandle;  }

  // --------------------------------------------------------------------------
  // The node parent
  // --------------------------------------------------------------------------
  const Node *GetParent() const           { return m_pParentNode; }
  Node *GetParent()                       { return m_pParentNode; }

  // --------------------------------------------------------------------------
  // Save and load the scene file
  // --------------------------------------------------------------------------
  virtual bool Save(FileHandle handle) const;
  virtual bool Load(FileHandle handle);

  // --------------------------------------------------------------------------
  // Return value from AddChild() when the child is already parented
  // --------------------------------------------------------------------------
  static const uint INVALID_CHILD = (uint) -1;

  // --------------------------------------------------------------------------
  // The array of children
  // --------------------------------------------------------------------------
  uint GetChildCount() const              { return m_ChildArray.size(); }
  Node *GetChild(uint index)              { return m_ChildArray[index]; }
  const Node *GetChild(uint index) const  { return m_ChildArray[index]; }
  uint AddChild(Node *pNode);
  bool RemoveChild(Node *pNode);

  // --------------------------------------------------------------------------
  // Flags
  // --------------------------------------------------------------------------
  void SetFlags(uint flags);
  void AddFlags(uint flags);
  bool HasFlags(uint flags) const;
  void RemoveFlags(uint flags);
  uint GetFlags() const;

  // --------------------------------------------------------------------------
  // Bounding sphere
  // --------------------------------------------------------------------------
  virtual const Sphere &GetBSphere() const;

protected:
  // --------------------------------------------------------------------------
  // Protected methods
  // --------------------------------------------------------------------------
  virtual void SetBoundsDirty();
  virtual void RecalculateBSphere() const;

  // --------------------------------------------------------------------------
  // Loading and saving
  // --------------------------------------------------------------------------
  virtual bool LoadInternal(const ConfigSection &data);
  virtual bool SaveInternal(ConfigSection &data) const;

  // --------------------------------------------------------------------------
  // Protected members
  // --------------------------------------------------------------------------
  uint                m_Type;               // The node type
  String              m_Name;               // The node name
  NodePtrArray        m_ChildArray;         // The child array
  Node               *m_pParentNode;        // The parent node
  mutable Sphere      m_BoundingSphere;     // The bounding sphere
  mutable bool        m_BoundsDirty;        // Is the bounding sphere dirty
  uint                m_Flags;              // The node flags
  mutable FileHandle  m_FileHandle;         // The file handle

}; // class Node


#endif // __NODE_H_

// -- EOF