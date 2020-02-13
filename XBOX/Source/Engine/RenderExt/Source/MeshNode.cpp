// ----------------------------------------------------------------------------
// File: MeshNode.cpp
// Desc: Manages a node in the scenegraph
// Auth: Michael Petrou
// (C) Copyright: 2005
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// Includes
// ----------------------------------------------------------------------------
#include "MeshNode.h"
#include "TransformNode.h"
#include "IndexedMesh.h"
#include "MeshLoader.h"


// ----------------------------------------------------------------------------
// Name: MeshNode::MeshNode
// Desc: Constructor
// ----------------------------------------------------------------------------
MeshNode::MeshNode()
: Node            (),
  m_NumLodMeshes  (0)
{
  REF_COUNT_CTOR(MeshNode);

  m_CurrentLod = 0;
  m_Type = MeshNode::Type;

  for (int lod = 0; lod < MAX_LOD; lod++)
    m_LODInfo[lod] = 0.0f;
} // MeshNode


// ----------------------------------------------------------------------------
// Name: MeshNode::MeshNode
// Desc: Constructor
// Parm: const String &name - the node name
// ----------------------------------------------------------------------------
MeshNode::MeshNode(const String &name)
: Node            (name),
  m_NumLodMeshes  (0)
{
  REF_COUNT_CTOR(MeshNode);

  m_CurrentLod = 0;
  m_Type = MeshNode::Type;

  for (int lod = 0; lod < MAX_LOD; lod++)
    m_LODInfo[lod] = 0.0f;
} // MeshNode


// ----------------------------------------------------------------------------
// Name: MeshNode::~MeshNode
// Desc: Destructor
// ----------------------------------------------------------------------------
MeshNode::~MeshNode()
{
  REF_COUNT_DTOR(MeshNode);

  for (int lod = 0; lod < MAX_LOD; lod++)
  {
    // Release our reference from the meshes
    MeshPtrArray::iterator meshIter(m_MeshArray[lod].begin()), meshEnd(m_MeshArray[lod].end());
    for (; meshIter != meshEnd; ++meshIter)
    {
      Mesh *pMesh = (*meshIter);
      pMesh->UnRef();
    }
    m_MeshArray[lod].clear();
  } // for
} // ~MeshNode


// ----------------------------------------------------------------------------
// Name: MeshNode::AddMesh
// Desc: Add a mesh
// Parm: Mesh *pMesh - the mesh to add
// Retn: uint        - the mesh index
// ----------------------------------------------------------------------------
uint MeshNode::AddMesh(Mesh *pMesh, int lod)
{
  // Add the mesh to the array
  m_MeshArray[lod].push_back(pMesh);
  pMesh->Ref();

  // Recalculate the bounding sphere
  if (lod == 0)
    SetBoundsDirty();
    //m_BoundsDirty = true;
  else
    m_NumLodMeshes++;

  // Return the index
  return m_MeshArray[lod].size() - 1;
} // AddMesh


// ----------------------------------------------------------------------------
// Name: MeshNode::RemoveMesh
// Desc: Remove a mesh
// Parm: uint index - the mesh index to remove
// ----------------------------------------------------------------------------
void MeshNode::RemoveMesh(uint index, int lod)
{
  // Get an iterator for the item
  MeshPtrArray::iterator iter(m_MeshArray[lod].begin());
  for (uint i = 0; i < index; i++)
    ++iter;

  // Get the mesh
  Mesh *pMesh = (*iter);

  // Remove the mesh from the vector
  m_MeshArray[lod].erase(iter);

  // Unref the mesh
  pMesh->UnRef();

  // Recalculate the bounding sphere
  if (lod == 0)
    SetBoundsDirty();
    //m_BoundsDirty = true;
  else
    m_NumLodMeshes--;
} // RemoveMesh


// ----------------------------------------------------------------------------
// Name: MeshNode::RecalculateBSphere
// Desc: Recalculate the bounding sphere
// ----------------------------------------------------------------------------
void MeshNode::RecalculateBSphere() const
{
  // Reset the bounding shpere
  m_BoundingSphere.Reset();
  m_BoundsDirty = false;

  // Flag for first use
  bool firstSphere = true;

  // Process all meshes
  MeshPtrArray::const_iterator meshIter(m_MeshArray[0].begin()), meshEnd(m_MeshArray[0].end());
  for (; meshIter != meshEnd; ++meshIter)
  {
    const Mesh *pMesh = (*meshIter);

    if (firstSphere)
    {
      // If this is the first sphere, initialise our bounding sphere
      m_BoundingSphere = pMesh->GetBSphere();
      firstSphere = false;
    } // if
    else
    {
      // Maximize the bounding sphere to also include this sphere
      m_BoundingSphere.Maximize(pMesh->GetBSphere());
    } // else
  } // for

  // Process all children
  NodePtrArray::const_iterator nodeIter(m_ChildArray.begin()), nodeEnd(m_ChildArray.end());
  for (; nodeIter != nodeEnd; ++nodeIter)
  {
    const Node *pNode = *nodeIter;

    // Get the bounding sphere and transform it if required
    Sphere sphere = pNode->GetBSphere();
    if (m_Type == TRANSFORM_NODE)
      sphere.center.TransformCoord(static_cast<const TransformNode *>(pNode)->GetTransform());

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
} // RecalculateBSphere


// ----------------------------------------------------------------------------
// Name: MeshNode::LoadInternal
// Desc: Load the specific date for this node from the config data
// Parm: const ConfigSection &data - the config data to load from
// ----------------------------------------------------------------------------
bool MeshNode::LoadInternal(const ConfigSection &data)
{
  for (uint i = 0; i < MAX_LOD; i++)
  {
    String lodStr("LOD");
    AppendInt(lodStr, i);
    m_LODInfo[i] = data(lodStr);
  }

  String shadowCmd = data("CastShadow");
  if (StrICmp(shadowCmd, "enabled"))
    m_Flags = CAST_SHADOWS_ENABLED;
  else if (StrICmp(shadowCmd, "disabled"))
    m_Flags = CAST_SHADOWS_DISABLED;
  else
    m_Flags = 0;

  ConfigSectionMap::const_iterator iter(data.ChildSections.begin()), end(data.ChildSections.end());
  for (; iter != end; ++iter)
  {
    const ConfigSection &meshData = iter->second;

    // Only process mesh sections
    if (meshData.Type != "Mesh")
      continue;

    // Get a file handle to the mesh
    FileHandle handle = Application.GetModelDatabase()->FindFileHandle(meshData("Filename"));
    if (!handle.Exists())
    {
      LOG_ERROR << "Failed to locate the file: " << handle.GetAbsoluteFilename() << ENDLOG;
      return false;
    }

    // Load the mesh from disk
    IndexedMesh *pMesh = (IndexedMesh *) MeshLoader::LoadMesh(handle);
    if (!pMesh)
    {
      LOG_ERROR << "Failed to load the mesh: " << handle.GetAbsoluteFilename() << ENDLOG;
      return false;
    }
    pMesh->SetName(meshData.Name);

    // Add the mesh to this node
    AddMesh(pMesh, meshData("LOD"));
  }

  // Process all other children
  return Node::LoadInternal(data);
}


// ----------------------------------------------------------------------------
// Name: MeshNode::SaveInternal
// Desc: Save the specific date for this node to the config data
// Parm: const ConfigSection &data - the config data to save to
// ----------------------------------------------------------------------------
bool MeshNode::SaveInternal(ConfigSection &data) const
{
  if (HasFlags(CAST_SHADOWS_ENABLED))
    data.Set("CastShadow", String("Enabled"));
  else if (HasFlags(CAST_SHADOWS_DISABLED))
    data.Set("CastShadow", String("Disabled"));
  else
    data.Set("CastShadow", String("Inherit"));

  for (uint i = 0; i < MAX_LOD; i++)
  {
    String lodStr("LOD");
    AppendInt(lodStr, i);
    data.Set(lodStr, m_LODInfo[i]);
  }

  for (int lod = 0; lod < MAX_LOD; lod++)
  {
    for (uint i = 0; i < GetMeshCount(lod); i++)
    {
      const Mesh *pMesh = GetMesh(i, lod);
      ConfigSection &meshData = data.AddSection("Mesh", pMesh->GetName());
      meshData.Set("Filename", pMesh->GetFileHandle().GetFilename());
      meshData.Set("LOD", lod);
    }
  }

  return Node::SaveInternal(data);
}


// ----------------------------------------------------------------------------
// Calculate and set the LOD for the given world matrix
// ----------------------------------------------------------------------------
void MeshNode::CalculateLOD(const Matrix &matrix)
{
  if (m_NumLodMeshes == 0)
    return;

  // Get the center of the mesh node in world space
  Vec3 worldSpaceCenter(matrix._41, matrix._42, matrix._43);
  worldSpaceCenter += GetBSphere().GetCenter();

  // Get the camera position in world space
  Vec3 worldSpaceCamera = Camera.GetPosition();

  // Get the squared distance from the camera to the center of the object
  float lengthSq = Vec3(worldSpaceCenter - worldSpaceCamera).LengthSq();

  // Get the squared radius of the bounding sphere
  float radiusSq = GetBSphere().GetRadius() * GetBSphere().GetRadius();

  // Get the squared distance from the camera to the nearest point of the node's bounds
  float distanceSq = Max<float>(0.0f, lengthSq - radiusSq);

  // Calculate the LOD
  for (int lod = 0; lod < MAX_LOD; lod++)
  {
    if (distanceSq < (m_LODInfo[lod] * m_LODInfo[lod]))
    {
      m_CurrentLod = Max<int>(0, lod);

      // TODO: Test for currentlod and newlod,and if newlod is 1 less than 
      // currentlod and distance is less than 10%, dont change (histerisis).
      return;
    }
  }
}


// ----------------------------------------------------------------------------
// Add the visible meshes to the render list
// Frustum: The view frustum
// Matrix: The world matrix
// RenderList: The render list to add the meshes to
// TestMeshes: Only test if the meshes are visible if this is true
// ----------------------------------------------------------------------------
void MeshNode::AddToRenderList(const Frustum &frustum, 
                               const Matrix &matrix, 
                               RenderList &renderList, 
                               bool testMeshes)
{
  if (m_NumLodMeshes > 0)
    CalculateLOD(matrix);

  for (uint i = 0; i < GetMeshCount(m_CurrentLod); i++)
  {
    Mesh *pMesh = GetMesh(i, m_CurrentLod);
    if (pMesh->IsEnabled())
    {
      if (!testMeshes || frustum.Intersects(pMesh->GetBSphere(), matrix) != Frustum::OUT_FRUSTUM)
      {
        renderList.Add(pMesh, matrix);
      } // if
    }
  } // for
}



// -- EOF



