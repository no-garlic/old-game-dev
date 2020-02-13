// ----------------------------------------------------------------------------
// File: XFileLoader.h
// Desc: Loads X files and creates an array of indexed meshes
// Auth: Michael Petrou
// (C) Copyright: 2006
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// Includes
// ----------------------------------------------------------------------------
#include "Render/XFileLoader.h"
#include "Render/IndexedMesh.h"


// ----------------------------------------------------------------------------
// Name: XFileLoader::XFileLoader
// Desc: Constructor
// ----------------------------------------------------------------------------
XFileLoader::XFileLoader()
: m_pFrameRoot  (NULL)
{
} // XFileLoader


// ----------------------------------------------------------------------------
// Name: XFileLoader::~XFileLoader
// Desc: Destructor
// ----------------------------------------------------------------------------
XFileLoader::~XFileLoader()
{
} // ~XFileLoader


// ----------------------------------------------------------------------------
// Name: XFileLoader::Load
// Desc: Load the X file
// Parm: FileHandle handle - the file handle
// Retn: bool              - true if loaded
// ----------------------------------------------------------------------------
bool XFileLoader::Load(const String &filename)
{
  CAllocateHierarchy allocateX(this);

  ulong options = D3DXMESH_MANAGED;

  HRESULT hr = D3DXLoadMeshHierarchyFromX(filename.c_str(), options, 
    ApplicationCentral.GetDevice(), &allocateX, NULL, &m_pFrameRoot, NULL);

  if (FAILED(hr))
  {
    LOG_ERROR << "Failed to load the X file: " << filename << ENDLOG;
    return false;
  } // if

  return true;
} // Load


void XFileLoader::FindFrames(LPD3DXFRAME pFrame, Array<Frame> &frames)
{
  // Loop through the frame's mesh container linked list
  for (LPD3DXMESHCONTAINER pMeshContainer = pFrame->pMeshContainer; 
       pMeshContainer;
       pMeshContainer = pMeshContainer->pNextMeshContainer)
  {
    XFileLoader::Frame newFrame;

    // Set the frames combined matrix
    D3DXFRAME_MATRIX  *pMtxFrame = (D3DXFRAME_MATRIX *) pFrame;
    newFrame.TransformMatrix = (Matrix) pMtxFrame->mtxCombined;

    // Set the frames mesh
    D3DXMESHCONTAINER_DERIVED *pContainer = (D3DXMESHCONTAINER_DERIVED *) pMeshContainer;
    newFrame.pMesh = pContainer->pMesh;

    // Add the frame
    frames.push_back(newFrame);
  } // for

  // Move onto next sibling frame
  if (pFrame->pFrameSibling)
    FindFrames(pFrame->pFrameSibling, frames);

  // Move onto first child frame 
  if (pFrame->pFrameFirstChild)
    FindFrames(pFrame->pFrameFirstChild, frames);
} // GetFrames


Array<XFileLoader::Frame> XFileLoader::GetFrames()
{
  Array<XFileLoader::Frame> frames;
  
  FindFrames(m_pFrameRoot, frames);

  return frames;
} // GetFrames


//-----------------------------------------------------------------------------
// Name: CAllocateHierarchy::CreateFrame
// Desc: Called by D3DX to inform us that we are required to allocate a new
//       frame in any way we wish to do so, and pass that pointer back.
//-----------------------------------------------------------------------------
HRESULT CAllocateHierarchy::CreateFrame(LPCTSTR Name, LPD3DXFRAME *ppNewFrame)
{
  D3DXFRAME_MATRIX * pNewFrame = NULL;

  // Clear out the passed frame (it may not be NULL)
  *ppNewFrame = NULL;

  // Allocate a new frame
  pNewFrame = new D3DXFRAME_MATRIX;

  // Clear out the frame
  ZeroMemory(pNewFrame, sizeof(D3DXFRAME_MATRIX));

  // Copy over, and default other values.
  if (Name) 
    pNewFrame->Name = _tcsdup(Name);

  // Default the matrix
  D3DXMatrixIdentity(&pNewFrame->TransformationMatrix);

  // Pass this new pointer back out
  *ppNewFrame = (D3DXFRAME*)pNewFrame;

  // Success!!
  return D3D_OK;
}

//-----------------------------------------------------------------------------
// Name: CAllocateHierarchy::CreateMeshContainer
// Desc: Called by D3DX to inform us that we are required to allocate a new
//       mesh container, and initialize it as we wish.
//-----------------------------------------------------------------------------
HRESULT CAllocateHierarchy::CreateMeshContainer(LPCTSTR Name, CONST D3DXMESHDATA * pMeshData, CONST D3DXMATERIAL * pMaterials,
                                                CONST D3DXEFFECTINSTANCE *pEffectInstances, DWORD NumMaterials, CONST DWORD *pAdjacency,
                                                LPD3DXSKININFO pSkinInfo, LPD3DXMESHCONTAINER *ppNewMeshContainer) 
{
  // We only support standard meshes (i.e. no patch or progressive meshes)
  if (pMeshData->Type != D3DXMESHTYPE_MESH)
    return E_FAIL;

  // Extract the standard mesh from the structure
  LPD3DXMESH pMesh = pMeshData->pMesh;

  // We require FVF compatible meshes only
  if (pMesh->GetFVF() == 0)
    return E_FAIL;

  // Allocate a mesh container structure
  D3DXMESHCONTAINER_DERIVED *pMeshContainer = new D3DXMESHCONTAINER_DERIVED;

  // Clear out the structure to begin with
  ZeroMemory(pMeshContainer, sizeof(D3DXMESHCONTAINER_DERIVED));

  // Copy over the name. We can't simply copy the pointer here because the memory
  // for the string belongs to the caller (D3DX)
  if (Name)
    pMeshContainer->Name = _tcsdup(Name);

  // Allocate a new CTriMesh
  IndexedMesh *pNewMesh = NULL;
  if (Name)
    pNewMesh = new IndexedMesh(Name);
  else
    pNewMesh = new IndexedMesh("");

  pMeshContainer->pMesh = pNewMesh;

  // Get the vertex declaration from the mesh
  D3DVERTEXELEMENT9 decl[MAX_FVF_DECL_SIZE];
  if (FAILED(pMesh->GetDeclaration(decl)))
  {
    LOG_ERROR << "Failed to get the vertex declaration" << ENDLOG;
    return E_FAIL;
  } // if

  // Build the vertex type
  if (!pNewMesh->BuildVertexType("", decl))
  {
    LOG_ERROR << "Failed to build the vertex type" << ENDLOG;
    return E_FAIL;
  } // if

  // Extract the data from the mesh
  uint vertex_size = pMesh->GetNumBytesPerVertex();
  uint num_verts   = pMesh->GetNumVertices();
  uint num_faces   = pMesh->GetNumFaces();
  uint face_size   = sizeof(ushort) * 3;

  // Lock the vertex buffer
  void *pvertex_data;
  if (FAILED(pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**) &pvertex_data)))
    return E_FAIL;

  // Copy the vertex data into the mesh
  pNewMesh->SetNumVerts(num_verts);
  memcpy(pNewMesh->GetVertexData(), pvertex_data, num_verts * vertex_size);

  // Unlock the vertex data
  if (FAILED(pMesh->UnlockVertexBuffer()))
    return E_FAIL;

  // Lock the index buffer
  void *pface_data;
  if (FAILED(pMesh->LockIndexBuffer(D3DLOCK_READONLY, (void**) &pface_data)))
    return E_FAIL;

  // Copy the index data into system memory
  pNewMesh->SetNumFaces(num_faces);
  memcpy((void *) pNewMesh->GetFaceData(), pface_data, num_faces * face_size);

  // Unlock the index data
  if (FAILED(pMesh->UnlockIndexBuffer()))
    return E_FAIL;

  // Make sure the number of subsets is the same as the number of attributes
  ulong attributeCount;
  if (FAILED(pMesh->GetAttributeTable(NULL, &attributeCount)))
    return E_FAIL;

  if (attributeCount != NumMaterials)
    return E_FAIL;

  // Get the attribute table
  D3DXATTRIBUTERANGE *pAttributeTable = new D3DXATTRIBUTERANGE[attributeCount];
  pMesh->GetAttributeTable(pAttributeTable, &attributeCount);

  // Add all materials to the subset array
  for (uint i = 0; i < NumMaterials; i++)
  {
    // Get the material and the effect
    const D3DXMATERIAL &d3dmat = pMaterials[i];
    const D3DXEFFECTINSTANCE &d3deffect = pEffectInstances[i];

    // Create the subset
    MeshSubset *pSubset = pNewMesh->AddSubset();

    // Set the color material
    pSubset->GetColorMaterial() = d3dmat.MatD3D;

    // Set the diffuse texture
    if (d3dmat.pTextureFilename)
    {
      // Get the file handle
      FileDatabase *pTextureDB = FileSystem("Texture");
      if (!pTextureDB)
        return E_FAIL;

      FileHandle textureHandle = pTextureDB->MakeFileHandle(d3dmat.pTextureFilename);

      // Load the texture
      Texture *pTex = TextureLoader::LoadTexture(textureHandle);
      if (!pTex)
        return E_FAIL;

      pSubset->GetTextureArray().SetDiffuse(pTex);
    } // if

    // Assign the effect if it exists
    if (d3deffect.pEffectFilename)
    {
      // Get the file handle
      FileDatabase *pMaterialDB = FileSystem("Material");
      if (!pMaterialDB)
        return E_FAIL;

      FileHandle materialHandle = pMaterialDB->MakeFileHandle(d3deffect.pEffectFilename);

      // Load the material
      Material *pMat = MaterialLoader::LoadEffect(materialHandle);
      if (!pMat)
        return E_FAIL;

      pSubset->SetMaterial(pMat);
    } // if
    else
    {
      const char *pEffectFilename = "notex.fx";

      // Get the file handle
      FileDatabase *pMaterialDB = FileSystem("Material");
      if (!pMaterialDB)
        return E_FAIL;

      FileHandle materialHandle = pMaterialDB->MakeFileHandle(pEffectFilename);

      // Load the material
      Material *pMat = MaterialLoader::LoadEffect(materialHandle);
      if (!pMat)
        return E_FAIL;

      pSubset->SetMaterial(pMat);
    } // else

    // Set the face range

    pSubset->SetFaceStart(pAttributeTable[i].FaceStart);
    pSubset->SetFaceCount(pAttributeTable[i].FaceCount);
  } // for

  // Delete the attribute table
  delete[] pAttributeTable;

  // Flag to mesh to be updated
  pNewMesh->SetDirty();

  // Set the new mesh container
  *ppNewMeshContainer = (D3DXMESHCONTAINER*)pMeshContainer;

  // Done
  return S_OK;
}


//-----------------------------------------------------------------------------
// Name: CAllocateHierarchy::DestroyFrame
// Desc: Called simply to destroy the specified frame.
//-----------------------------------------------------------------------------
HRESULT CAllocateHierarchy::DestroyFrame( LPD3DXFRAME pFrameToFree ) 
{
  D3DXFRAME_MATRIX * pMtxFrame = (D3DXFRAME_MATRIX*)pFrameToFree;

  // Validate Parameters
  if (!pMtxFrame)
    return D3D_OK;

  // Release data
  if (pMtxFrame->Name)
    free(pMtxFrame->Name);
  delete pMtxFrame;

  // Success!!
  return D3D_OK;
}

//-----------------------------------------------------------------------------
// Name: CAllocateHierarchy::DestroyMeshContainer
// Desc: Called simply to destroy the specified mesh container.
//-----------------------------------------------------------------------------
HRESULT CAllocateHierarchy::DestroyMeshContainer( LPD3DXMESHCONTAINER pContainerToFree ) 
{
  ULONG i;
  D3DXMESHCONTAINER_DERIVED * pContainer = (D3DXMESHCONTAINER_DERIVED*)pContainerToFree;

  // Validate Parameters
  if (!pContainer)
    return D3D_OK;

  // Release material data
  if (pContainer->pMaterials)
  {
    for (i = 0; i < pContainer->NumMaterials; ++i)
    {
      // Release the string data
      if (pContainer->pMaterials[i].pTextureFilename)
        free(pContainer->pMaterials[i].pTextureFilename);
    } // for

    // Destroy the array
    delete[] pContainer->pMaterials;
    pContainer->pMaterials = NULL;
  } // if

  if (pContainer->MeshData.pMesh)
    pContainer->MeshData.pMesh->Release();

  if (pContainer->Name)
    free(pContainer->Name);

  if (pContainer->pMesh)
    delete pContainer->pMesh;

  delete pContainer;

  return D3D_OK;
} // DestroyMeshContainer


// -- EOF

