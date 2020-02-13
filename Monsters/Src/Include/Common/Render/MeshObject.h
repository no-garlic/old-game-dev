// ----------------------------------------------------------------------------
// File: MeshObject.h
// Desc: Manages an object that holds a number of meshes.
// Auth: Michael Petrou
// (C) Copyright: 2005
// ----------------------------------------------------------------------------
#ifndef __MESH_OBJECT_H
#define __MESH_OBJECT_H


// ----------------------------------------------------------------------------
// Standard includes
// ----------------------------------------------------------------------------
#include "Kernel/KernelInc.h"
#include "Engine/EngineInc.h"
#include "Maths/MathInc.h"
#include "Render/Material.h"
#include "Render/Mesh.h"


// ----------------------------------------------------------------------------
// Name: MeshNode (class)
// Desc: A node class that holds a mesh, it's offset matrix, and it's children
// ----------------------------------------------------------------------------
class MeshNode : public RefCounted, private Unique
{
public:
  // --------------------------------------------------------------------------
  // Constructor and destructor
  // --------------------------------------------------------------------------
  MeshNode();
  virtual ~MeshNode();

  // --------------------------------------------------------------------------
  // Manage the matrix
  // --------------------------------------------------------------------------
  void SetMatrix(const Matrix &matrix) { m_Matrix = matrix; }
  const Matrix &GetMatrix() const      { return m_Matrix;   }

  // --------------------------------------------------------------------------
  // Manage the name
  // --------------------------------------------------------------------------
  void SetName(const String &name)    { m_Name = name;      }
  const String &GetName() const       { return m_Name;      }

  // --------------------------------------------------------------------------
  // Manage the mesh
  // --------------------------------------------------------------------------
  uint AddMesh(Mesh *pMesh);
  uint MeshCount() const;
  Mesh *GetMesh(uint id);
  const Mesh *GetMesh(uint id) const;

  // --------------------------------------------------------------------------
  // Manage the hierarchy
  // --------------------------------------------------------------------------
  uint AddChild(MeshNode *pNode);
  uint ChildCount() const;
  const MeshNode *GetChild(uint id) const;
  MeshNode *GetChild(uint id);

  // --------------------------------------------------------------------------
  // Debug print
  // --------------------------------------------------------------------------
  void DebugPrint(uint offset) const;

private:
  // --------------------------------------------------------------------------
  // Private members
  // --------------------------------------------------------------------------
  Array<MeshNode *>   m_ChildArray;
  Array<Mesh     *>   m_MeshArray;
  Matrix              m_Matrix;
  String              m_Name;

}; // class MeshNode


// ----------------------------------------------------------------------------
// Name: MeshObject (class)
// Desc: Manage a hierarchy of mesh nodes
// ----------------------------------------------------------------------------
class MeshObject
{
public:
  // --------------------------------------------------------------------------
  // Constructor and destructor
  // --------------------------------------------------------------------------
  MeshObject();
  ~MeshObject();

  // --------------------------------------------------------------------------
  // Get the root node
  // --------------------------------------------------------------------------
  inline MeshNode *GetRootNode()              { return m_pRootNode; }
  inline const MeshNode *GetRootNode() const  { return m_pRootNode; }

  // --------------------------------------------------------------------------
  // Name: GetBSphere
  // Desc: Gets the bounding sphere of this mesh
  // Retn: const Sphere & - the sphere
  // --------------------------------------------------------------------------
  const Sphere &GetBSphere() const;

  // --------------------------------------------------------------------------
  // Name: IntersectsBSphere
  // Desc: Tests for a collision between the provided ray (which must be already
  //       transformed into model space) and this object's bounding sphere.
  // Parm: const Ray &ray - the ray in object space
  // Retn: bool           - true if the ray intersects with the bounding sphere
  // --------------------------------------------------------------------------
  bool IntersectsBSphere(const Ray &ray) const;

  // --------------------------------------------------------------------------
  // Name: SetBSphereStatic
  // Desc: Sets the bounding sphere to be static or dynamic
  // Parm: bool isStatic - the static flag
  // --------------------------------------------------------------------------
  void SetBSphereStatic(bool isStatic)        { m_SphereStatic = isStatic; }
  
  // --------------------------------------------------------------------------
  // Name: SetBSphereDirty
  // Desc: Set the bounding sphere to be dirty
  // Parm: bool isDirty - the dirty flag
  // --------------------------------------------------------------------------
  void SetBSphereDirty(bool isDirty)          { m_SphereDirty  = isDirty;  }

  // --------------------------------------------------------------------------
  // Name: IsVisible
  // Desc: Tests if the object is within the frustum
  // Parm: const Matrix &world_matrix - the world matrix
  // Parm: const Frustum &frustum   - the view frustum
  // Retn: bool                     - true if the object is within the frustum 
  // --------------------------------------------------------------------------
  bool IsVisible(const Matrix &world_matrix, const Frustum &frustum) const;

  // --------------------------------------------------------------------------
  // Import the mesh from the  X file
  // --------------------------------------------------------------------------
  bool ImportFromX(const String &filename);

  // --------------------------------------------------------------------------
  // Debug print
  // --------------------------------------------------------------------------
  void DebugPrint() const;

private:
  // --------------------------------------------------------------------------
  // Private members
  // --------------------------------------------------------------------------
  MeshNode       *m_pRootNode;
  mutable Sphere  m_Sphere;
  mutable bool    m_SphereDirty;
  bool            m_SphereStatic;

}; // MEshObject


#endif // __MESH_OBJECT_H

// -- EOF

