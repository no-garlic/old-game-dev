// ----------------------------------------------------------------------------
// File: MeshNode.h
// Desc: Manages a node in the scenegraph
// Auth: Michael Petrou
// (C) Copyright: 2005
// ----------------------------------------------------------------------------
#ifndef __MESH_NODE_H_
#define __MESH_NODE_H_


// ----------------------------------------------------------------------------
// Standard includes
// ----------------------------------------------------------------------------
#include "libStandard.h"
#include "libRenderCore.h"
#include "libMaths.h"
#include "Node.h"
#include "RenderList.h"


// ----------------------------------------------------------------------------
// Maximum number of LOD's
// ----------------------------------------------------------------------------
#define MAX_LOD 3


// ----------------------------------------------------------------------------
// Name: MeshNode  (class)
// Desc: A scenegraph node that manages mehs rendering
// ----------------------------------------------------------------------------
class MeshNode : public Node
{
public:
  // --------------------------------------------------------------------------
  // Constructors and destructor
  // --------------------------------------------------------------------------
  MeshNode();
  explicit MeshNode(const String &name);
  virtual ~MeshNode();

  // --------------------------------------------------------------------------
  // The node type
  // --------------------------------------------------------------------------
  static const uint Type = MESH_NODE;

  // --------------------------------------------------------------------------
  // The array of meshes
  // --------------------------------------------------------------------------
  uint GetMeshCount(int lod = 0) const               { return m_MeshArray[lod].size();  }
  Mesh *GetMesh(uint index, int lod = 0)             { return m_MeshArray[lod][index];  }
  const Mesh *GetMesh(uint index, int lod = 0) const { return m_MeshArray[lod][index];  }
  uint AddMesh(Mesh *pMesh, int lod = 0);
  void RemoveMesh(uint index, int lod = 0);

  // --------------------------------------------------------------------------
  // Save and load the scene file
  // --------------------------------------------------------------------------
  bool Save(FileHandle handle) const  { return Node::Save(handle); }
  bool Load(FileHandle handle)        { return Node::Load(handle); }

  // --------------------------------------------------------------------------
  // Set the LOD info
  // --------------------------------------------------------------------------
  void SetLODInfo(int lod, float distance)  { m_LODInfo[lod] = distance; }
  float GetLODInfo(int lod)                 { return m_LODInfo[lod];     }
  
  // --------------------------------------------------------------------------
  // Get and set the current LOD
  // --------------------------------------------------------------------------
  void SetCurrentLOD(int lod)   { m_CurrentLod = lod; }
  int GetCurrentLOD() const     { return m_CurrentLod; }
  
  // --------------------------------------------------------------------------
  // Add the visible meshes to the render list
  // Frustum: The view frustum
  // Matrix: The world matrix
  // RenderList: The render list to add the meshes to
  // TestMeshes: Only test if the meshes are visible if this is true
  // --------------------------------------------------------------------------
  void AddToRenderList(const Frustum &frustum, const Matrix &matrix, 
    RenderList &renderList, bool testMeshes);

protected:
  // --------------------------------------------------------------------------
  // Calculate and set the LOD for the given world matrix
  // --------------------------------------------------------------------------
  void CalculateLOD(const Matrix &matrix);

  // --------------------------------------------------------------------------
  // Loading and saving
  // --------------------------------------------------------------------------
  friend class Node;  
  virtual bool LoadInternal(const ConfigSection &data);
  virtual bool SaveInternal(ConfigSection &data) const;

  // --------------------------------------------------------------------------
  // Protected methods
  // --------------------------------------------------------------------------
  virtual void RecalculateBSphere() const;

  // --------------------------------------------------------------------------
  // Protected members
  // --------------------------------------------------------------------------
  int             m_CurrentLod;         // The current LOD
  float           m_LODInfo[MAX_LOD];   // The distance sq where the lod's change
  MeshPtrArray    m_MeshArray[MAX_LOD]; // The mesh arrays
  uint            m_NumLodMeshes;       // The number of non level 0 meshes

}; // class MeshNode


#endif // __MESH_NODE_H_

// -- EOF
