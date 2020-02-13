// ----------------------------------------------------------------------------
// File: MeshLoader.h
// Desc: Loads and caches meshes
// Auth: Michael Petrou
// (C) Copyright: 2006
// ----------------------------------------------------------------------------
#include "MeshLoader.h"


// ----------------------------------------------------------------------------
// Static initialisation
// ----------------------------------------------------------------------------
Map<String, Mesh *> MeshLoader::s_Mesh_map;


// ----------------------------------------------------------------------------
// Name: MeshLoader::LoadMesh
// Desc: Load a Mesh or retrieve it from the cache
// Parm: FileHandle handle - the file handle
// Retn: Mesh *         - the Mesh
// ----------------------------------------------------------------------------
Mesh *MeshLoader::LoadMesh(FileHandle handle)
{
  return LoadMesh(handle, IndexedMeshFunctor());
} // LoadMesh


// ----------------------------------------------------------------------------
// Name: MeshLoader::LoadMesh
// Desc: Load a Mesh or get it from the cache
// Parm: FileHandle handle                - the file handle
// Parm: const BaseMeshFunctor &type   - the creation functor
// Retn: Mesh *                        - the Mesh
// ----------------------------------------------------------------------------
Mesh *MeshLoader::LoadMesh(FileHandle handle, const BaseMeshFunctor &type)
{
  Map<String, Mesh *>::iterator iter = s_Mesh_map.find(handle.GetAbsoluteFilename());
  if (iter != s_Mesh_map.end())
    return iter->second;

  Mesh *pMesh = type(handle);
  if (!pMesh)
    return NULL;

  s_Mesh_map.insert(MakePair(handle.GetAbsoluteFilename(), pMesh));
  SafeRef(pMesh);

  return pMesh;
} // LoadMesh


// ----------------------------------------------------------------------------
// Name: MeshLoader::GarbageCollect
// Desc: Release any Meshs with no external references
// ----------------------------------------------------------------------------
void MeshLoader::GarbageCollect()
{
  Map<String, Mesh *>::iterator iter(s_Mesh_map.begin()), end(s_Mesh_map.end());
  while (iter != end)
  {
    Mesh *pMesh = iter->second;
    if (pMesh->GetRefCount() == 1)
    {
      iter = s_Mesh_map.erase(iter);
      SafeUnRef(pMesh);
    } // if
    else
    {
      ++iter;
    } // else
  } // if
} // GarbageCollect


// ----------------------------------------------------------------------------
// Name: MeshLoader::GetAllMeshs
// Desc: Get all Meshs
// Retn: const Map<String, Mesh *> & - the Mesh array
// ----------------------------------------------------------------------------
const Map<String, Mesh *> &MeshLoader::GetAllMeshs()
{
  return s_Mesh_map;
} // GetAllMeshs


// -- EOF






