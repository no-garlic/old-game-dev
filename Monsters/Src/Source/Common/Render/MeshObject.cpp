// ----------------------------------------------------------------------------
// File: MeshObject.cpp
// Desc: Manages an object that holds a number of meshes.
// Auth: Michael Petrou
// (C) Copyright: 2005
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// Inlcudes
// ----------------------------------------------------------------------------
#include "Render/MeshObject.h"
#include "Render/XFileLoader.h"


// ----------------------------------------------------------------------------
// Name: MeshNode::MeshNode
// Desc: Constructor
// ----------------------------------------------------------------------------
MeshNode::MeshNode()
: m_Matrix  (MatrixIdentity)
{
} // MeshNode


// ----------------------------------------------------------------------------
// Name: MeshNode::~MeshNode
// Desc: Destructor
// ----------------------------------------------------------------------------
MeshNode::~MeshNode()
{
  Array<MeshNode *>::iterator iter(m_ChildArray.begin()), end(m_ChildArray.end());
  for (; iter != end; ++iter)
    SafeUnRef(*iter);
} // ~MeshNode


// ----------------------------------------------------------------------------
// Name: MeshNode::AddMesh
// Desc: Add a mesh to the array
// Parm: Mesh *pMesh - the mesh to add
// Retn: uint        - the id of the new mesh
// ----------------------------------------------------------------------------
uint MeshNode::AddMesh(Mesh *pMesh)
{
  m_MeshArray.push_back(pMesh);
  pMesh->Ref();

  return m_MeshArray.size() - 1;
} // AddMesh


// ----------------------------------------------------------------------------
// Name: MeshNode::MeshCount
// Desc: Get the mesh count
// Retn: uint - the number of meshes
// ----------------------------------------------------------------------------
uint MeshNode::MeshCount() const
{
  return m_MeshArray.size();
} // MeshCount


// ----------------------------------------------------------------------------
// Name: MeshNode::GetMesh
// Desc: Get a mesh from the array
// Parm: uint id - the mesh id
// Retn: Mesh *  - the mesh
// ----------------------------------------------------------------------------
Mesh *MeshNode::GetMesh(uint id)
{
  return m_MeshArray[id];
} // GetMesh


// ----------------------------------------------------------------------------
// Name: MeshNode::GetMesh
// Desc: Get a mesh from the array
// Parm: uint id       - the mesh id
// Retn: const Mesh *  - the mesh
// ----------------------------------------------------------------------------
const Mesh *MeshNode::GetMesh(uint id) const
{
  return m_MeshArray[id];
} // GetMesh


// ----------------------------------------------------------------------------
// Name: MeshNode::AddChild
// Desc: Add a child to the array
// Parm: MeshNode *pNode - the child
// Retn: uint            - the child id
// ----------------------------------------------------------------------------
uint MeshNode::AddChild(MeshNode *pNode)
{
  m_ChildArray.push_back(pNode);
  pNode->Ref();
  return m_ChildArray.size() - 1;
} // AddChild


// ----------------------------------------------------------------------------
// Name: MeshNode::ChildCount
// Desc: Get the child count
// Retn: uint - the number of children
// ----------------------------------------------------------------------------
uint MeshNode::ChildCount() const
{
  return m_ChildArray.size();
} // ChildCount


// ----------------------------------------------------------------------------
// Name: MeshNode::GetChild
// Desc: Get a child from the array
// Parm: uint id          - the child id
// Retn: const MeshNode * - the child
// ----------------------------------------------------------------------------
const MeshNode *MeshNode::GetChild(uint id) const
{
  return m_ChildArray[id];
} // GetChild


// ----------------------------------------------------------------------------
// Name: MeshNode::GetChild
// Desc: Get a child from the array
// Parm: uint id          - the child id
// Retn: const MeshNode * - the child
// ----------------------------------------------------------------------------
MeshNode *MeshNode::GetChild(uint id)
{
  return m_ChildArray[id];
} // GetChild


// ----------------------------------------------------------------------------
// Name: MeshObject::MeshObject
// Desc: Constructor
// ----------------------------------------------------------------------------
MeshObject::MeshObject()
: m_SphereStatic  (false),
  m_SphereDirty   (true)
{
  m_pRootNode = new MeshNode();
  m_pRootNode->Ref();
} // MeshObject


// ----------------------------------------------------------------------------
// Name: MeshObject::~MeshObject
// Desc: Destructor
// ----------------------------------------------------------------------------
MeshObject::~MeshObject()
{
  m_pRootNode->UnRef();
} // ~MeshObject


// ----------------------------------------------------------------------------
// Name: MeshObject__AddNode
// Desc: Create a child node for the supplied frame
// Parm: MeshNode *pParentNode - the parent node
// Parm: LPD3DXFRAME pFrame    - the frame
// ----------------------------------------------------------------------------
void MeshObject__AddNode(MeshNode *pParentNode, LPD3DXFRAME pFrame)
{
  // Create a new node
  MeshNode *pNode = new MeshNode();

  // Set the node matrix
  pNode->SetMatrix((Matrix) pFrame->TransformationMatrix);
  
  // Set the node name
  if (pFrame->Name)
    pNode->SetName(String((const char *)pFrame->Name));

  // Add the node as a child
  pParentNode->AddChild(pNode);

  // Loop through the frame's mesh container linked list
  for (LPD3DXMESHCONTAINER pMeshContainer = pFrame->pMeshContainer; 
       pMeshContainer;
       pMeshContainer = pMeshContainer->pNextMeshContainer)
  {
    // Add the mesh
    D3DXMESHCONTAINER_DERIVED *pContainer = (D3DXMESHCONTAINER_DERIVED *) pMeshContainer;
    pNode->AddMesh(pContainer->pMesh);
  } // for

  // Add siblings to the parent node
  if (pFrame->pFrameSibling)
    MeshObject__AddNode(pParentNode, pFrame->pFrameSibling);

  // Add children to the new node
  if (pFrame->pFrameFirstChild)
    MeshObject__AddNode(pNode, pFrame->pFrameFirstChild);
} // MeshObject__AddNode


// ----------------------------------------------------------------------------
// Name: MeshObject::ImportFromX
// Desc: Import the object from the X file
// Parm: const String &filename - the filename
// Retn: bool                   - true if imported sucessfully
// ----------------------------------------------------------------------------
bool MeshObject::ImportFromX(const String &filename)
{
  // Load the X file
  XFileLoader loader;
  if (!loader.Load(filename))
    return false;

  // Get the root frame
  LPD3DXFRAME pRootFrame = loader.GetRootFrame();
  if (!pRootFrame)
    return false;

  // Create the mesh hierarchy
  MeshObject__AddNode(m_pRootNode, pRootFrame);

  // Done
  return true;
} // ImportFromX


// ----------------------------------------------------------------------------
// Name: MeshObject::DebugPrint
// Desc: Print the mesh name
// Parm: uint offset - the offset
// ----------------------------------------------------------------------------
void MeshNode::DebugPrint(uint offset) const
{
  String str;
  AppendInt(str, offset);
  str += m_Name;

  LOG << str << ENDLOG;

  Array<MeshNode *>::const_iterator iter(m_ChildArray.begin()), end(m_ChildArray.end());
  for (; iter != end; ++iter)
    (*iter)->DebugPrint(offset + 2);
} // DebugPrint


// ----------------------------------------------------------------------------
// Name: MeshObject::DebugPrint
// Desc: Print the mesh hierarchy
// ----------------------------------------------------------------------------
void MeshObject::DebugPrint() const
{
  m_pRootNode->DebugPrint(0);
} // DebugPrint


// ----------------------------------------------------------------------------
// Name: MeshObject__CalculateSphere
// Desc: Recursively calculate the bounding shpere for a mesh node hierarchy
// Parm: MeshNode *pNode - the node to start
// Parm: Sphere &sphere  - the sphere to maximize
// ----------------------------------------------------------------------------
void MeshObject__CalculateSphere(MeshNode *pNode, Sphere &sphere)
{
  // Get the matrix offset
  Vec3 matrixOffset(pNode->GetMatrix()._41, pNode->GetMatrix()._42, pNode->GetMatrix()._43);

  // Iterate through all meshes
  for (uint i = 0; i < pNode->MeshCount(); i++)
  {
    // Get the mesh sphere
    Mesh *pMesh       = pNode->GetMesh(i);
    Sphere meshSphere = pMesh->GetBSphere();

    // Add the matrix offset
    meshSphere.center.Add(matrixOffset);
 
    // Maximize the sphere
    sphere.Maximize(meshSphere);
  } // for

  // Check all children
  for (uint i = 0; i < pNode->ChildCount(); i++)
    MeshObject__CalculateSphere(pNode->GetChild(i), sphere);

} // MeshObject__CalculareSphere


// ----------------------------------------------------------------------------
// Name: MeshObject::GetBSphere
// Desc: Get the bounding sphere
// Retn: const Sphere & - the sphere
// ----------------------------------------------------------------------------
const Sphere &MeshObject::GetBSphere() const
{
  if (m_SphereDirty || !m_SphereStatic)
  {
    if (m_pRootNode)
    {
      m_Sphere.center.Set(0.0f, 0.0f, 0.0f);
      m_Sphere.radius = 0.0f;

      MeshObject__CalculateSphere(m_pRootNode, m_Sphere);
    } // if

    m_SphereDirty = false;
  } // if

  return m_Sphere;
} // GetBSphere

// ----------------------------------------------------------------------------
// Name: MeshObject::IntersectsBSphere
// Desc: Tests if the ray intersects the bounding sphere
// Parm: const Ray &ray - the ray
// Retn: bool           - true if it intersects
// ----------------------------------------------------------------------------
bool MeshObject::IntersectsBSphere(const Ray &ray) const
{
  return m_Sphere.TestCollision(ray);
} // IntersectsBSphere


// ----------------------------------------------------------------------------
// Name: MeshObject::IsVisible
// Desc: Tests if the bounding sphere is within the frustum
// Parm: const Matrix &world_matrix - the world matrix
// Parm: const Frustum &frustum     - the frustum
// Retn: bool                       - true if visible
// ----------------------------------------------------------------------------
bool MeshObject::IsVisible(const Matrix &world_matrix, const Frustum &frustum) const
{
  if (frustum.Intersects(GetBSphere(), world_matrix) != Frustum::OUT_FRUSTUM)
    return true;

  return false;
} // IsVisible


// -- EOF

