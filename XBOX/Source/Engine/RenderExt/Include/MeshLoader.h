// ----------------------------------------------------------------------------
// File: MeshLoader.h
// Desc: Loads and caches meshes
// Auth: Michael Petrou
// (C) Copyright: 2006
// ----------------------------------------------------------------------------
#ifndef __MESH_LOADER_H_
#define __MESH_LOADER_H_


// ----------------------------------------------------------------------------
// Includes
// ----------------------------------------------------------------------------
#include "Mesh.h"
#include "IndexedMesh.h"


// ----------------------------------------------------------------------------
// Name: BaseMeshFunctor (struct)
// Desc: Base class Mesh functor allowing a Mesh to be loaded
// ----------------------------------------------------------------------------
struct BaseMeshFunctor
{
  virtual Mesh *operator()(FileHandle handle) const = 0;
}; // class BaseMeshFunctor


// ----------------------------------------------------------------------------
// Name: MeshFunctorTemplate  (struct)
// Desc: Templated scene Mesh functor that can create sceen Meshs of
//       a derived type (that is specified by the template argument).
// ----------------------------------------------------------------------------
template <class T>
struct MeshFunctorTemplate : public BaseMeshFunctor
{
  // --------------------------------------------------------------------------
  // Name: operator
  // Desc: Create a Mesh and load it from a file
  // Retn: Mesh * - the created Mesh, or null if hte Mesh failed to 
  //       load
  // --------------------------------------------------------------------------
  virtual Mesh *operator()(FileHandle handle) const 
  { 
    T *pMesh = new T();
    if (!pMesh->Load(handle))
      SafeDelete(pMesh);

    return pMesh;
  } // operator()

}; // struct MeshFunctorTemplate


// ----------------------------------------------------------------------------
// Typedef of a Mesh functor to create IndexedMesh instances
// ----------------------------------------------------------------------------
typedef MeshFunctorTemplate<IndexedMesh> IndexedMeshFunctor;


// ----------------------------------------------------------------------------
// Name: MeshLoader (class)
// Desc: Class to load Meshs
// ----------------------------------------------------------------------------
class MeshLoader
{
public:
  // --------------------------------------------------------------------------
  // Load the Mesh from disk
  // --------------------------------------------------------------------------
  static Mesh *LoadMesh(FileHandle handle);
  static Mesh *LoadMesh(FileHandle handle, const BaseMeshFunctor &type);

  // --------------------------------------------------------------------------
  // Release any Meshs with no external references
  // --------------------------------------------------------------------------
  static void GarbageCollect();

  // --------------------------------------------------------------------------
  // Get all Meshs
  // --------------------------------------------------------------------------
  static const Map<String, Mesh *> &GetAllMeshs();

private:
  // --------------------------------------------------------------------------
  // Private static members
  // --------------------------------------------------------------------------
  static Map<String, Mesh *> s_Mesh_map;

}; // class MeshLoader




#endif // __MESH_LOADER_H_

// -- EOF

