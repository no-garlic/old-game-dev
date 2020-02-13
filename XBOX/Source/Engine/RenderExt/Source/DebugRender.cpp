// ----------------------------------------------------------------------------
// File: DebugRender.h
// Desc: Provides some debugging functions to easily draw 3d primatives
// Auth: Michael Petrou
// (C) Copyright: 2006
// ----------------------------------------------------------------------------
#include "DebugRender.h"


// ----------------------------------------------------------------------------
// Static initialiser
// ----------------------------------------------------------------------------
DebugRenderManager *DebugRenderManager::s_pInstance = NULL;


DebugRenderManager::DebugRenderManager()
{
  m_pMaterial   = NULL;
  m_Initialised = false;
  m_Count       = 0;
  m_pSphere     = NULL;
  m_pBox        = NULL;
  m_pCylinder   = NULL;
  m_pQuad       = NULL;
}


DebugRenderManager::~DebugRenderManager()
{
  SafeRelease(m_pSphere);
  SafeRelease(m_pBox);
  SafeRelease(m_pCylinder);
  delete m_pQuad;
}


DebugRenderManager &DebugRenderManager::GetInstance()
{
  if (!s_pInstance)
  {
    s_pInstance = new DebugRenderManager();
    atexit(&DebugRenderManager::DestroyInstance);
  } // if

  return *s_pInstance;
}


void DebugRenderManager::DestroyInstance()
{
  delete s_pInstance;
  s_pInstance = NULL;
}


bool DebugRenderManager::Init()
{
  if (m_Initialised)
    return false;

  m_pMaterial = MaterialCache::GetMaterial("DebugMaterial");
  if (!m_pMaterial)
  {
    LOG_ERROR << "Failed to get the DebugMaterial from the MaterialCache" << ENDLOG;
    return false;
  }

  if (FAILED(D3DXCreateSphere(Application.GetDevice(), 1.0f, 16, 16, &m_pSphere, NULL)))
  {
    LOG_ERROR << "Failed to create the debug sphere" << ENDLOG;
    return false;
  }

  if (FAILED(D3DXCreateBox(Application.GetDevice(), 1.0f, 1.0f, 1.0f, &m_pBox, NULL)))
  {
    LOG_ERROR << "Failed to create the debug box" << ENDLOG;
    return false;
  }

  const VertexType *pVertexType = VertexTypeCache::GetVertexType("VertexType_PN");
  if (!pVertexType)
  {
    LOG_ERROR << "Failed ot find the vertex type: VertexType_PN for the debug render line" << ENDLOG;
    return false;
  }

  m_pQuad = new IndexedMesh("DebugLine", pVertexType);
  m_pQuad->SetVertexBufferDynamic(true);
  m_pQuad->SetNumFaces(2);
  m_pQuad->GetFaceData()[0].Assign(0, 1, 2);
  m_pQuad->GetFaceData()[1].Assign(0, 2, 3);
  m_pQuad->SetNumVerts(4);
  m_pQuad->SetDirty();

  MeshSubset *pSubset = m_pQuad->AddSubset();
  pSubset->SetFaceStart(0);
  pSubset->SetFaceCount(2);
  pSubset->SetMaterial(m_pMaterial);

  m_Initialised = true;
  return true;
}


void DebugRenderManager::AddSphere(const Sphere &sphere, const Color &color, int frames)
{
  DebugRenderManager::DebugItemInfo<Sphere> info;

  info.item   = sphere;
  info.frames = frames;
  info.color  = color;

  m_SphereInfo.insert(m_SphereInfo.end(), info);
  m_Count++;
}


void DebugRenderManager::AddBox(const Box &box, const Color &color, int frames)
{
  DebugRenderManager::DebugItemInfo<Box> info;

  info.item   = box;
  info.frames = frames;
  info.color  = color;

  m_BoxInfo.insert(m_BoxInfo.end(), info);
  m_Count++;
}


void DebugRenderManager::AddLine(const LineSegment &lineSegment, const Color &color, int frames)
{
  DebugRenderManager::DebugItemInfo<LineSegment> info;

  info.item   = lineSegment;
  info.frames = frames;
  info.color  = color;

  m_LineInfo.insert(m_LineInfo.end(), info);
  m_Count++;
}


void DebugRenderManager::AddCylinder(const Matrix &m, const Cylinder &cylinder, const Color &color, int frames)
{
  DebugRenderManager::DebugItemInfo<DebugRenderManager::DebugCylinder> info;

  info.item.m_Cylinder  = cylinder;
  info.item.m_Matrix    = m;
  info.frames           = frames;
  info.color            = color;

  m_CylinderInfo.insert(m_CylinderInfo.end(), info);
  m_Count++;
}


void DebugRenderManager::AddPlane(const Plane &plane, const Color &color, int frames)
{
  DebugRenderManager::DebugItemInfo<Plane> info;

  info.item   = plane;
  info.frames = frames;
  info.color  = color;

  m_PlaneInfo.insert(m_PlaneInfo.end(), info);
  m_Count++;
}


void DebugRenderManager::AddMesh(const Matrix &m, VT_PN *pVertexData, uint numVertex, ushort *pIndexData, uint numIndex, const Color &color, uint frames)
{
  DebugRenderManager::DebugItemInfo<DebugRenderManager::DebugMesh> info;
  DebugRenderManager::DebugMesh mesh;

  mesh.m_Matrix     = m;
  mesh.m_pVertex    = pVertexData;
  mesh.m_pIndex     = pIndexData;
  mesh.m_NumVertex  = numVertex;
  mesh.m_NumIndex   = numIndex;

  info.item   = mesh;
  info.frames = frames;
  info.color  = color;

  m_MeshInfo.insert(m_MeshInfo.end(), info);
  m_Count++;
}


void DebugRenderManager::Render()
{
  ASSERT(m_Initialised, "The DebugRenderManager has not been initialsied");
  if (!m_Initialised)
    return;

  // Dont draw if there is nothing to draw
  if (m_Count == 0)
    return;

  NULL_ASSERT(m_pMaterial);

  // Begin rendering with the material
  m_pMaterial->Begin();
  m_pMaterial->BeginPass(0);

  // Render the objects
  RenderSpheres();
  RenderBoxes();
  RenderLines();
  RenderCylinders();
  RenderPlanes();
  RenderMeshes();

  // Finish rendering with the material
  m_pMaterial->EndPass();
  m_pMaterial->End();
}


void DebugRenderManager::RenderSpheres()
{
  // Empty texture and light arrays
  TextureArray textures;
  LightArray   lights;

  // Render all spheres
  List<DebugRenderManager::DebugItemInfo<Sphere> >::iterator iter(m_SphereInfo.begin()), end(m_SphereInfo.end());
  for (; iter != end; ++iter)
  {
    DebugRenderManager::DebugItemInfo<Sphere> &info = *iter;

    // Create a matrix with the scale and transformation
    Matrix m = Matrix::MakeNewScaling(info.item.radius, info.item.radius, info.item.radius);
    m.SetTAxis(info.item.center);
    m.PostMultiply(Matrix::MakeNewRotationYawPitchRoll(0.0f, D3DX_PI * 0.5f, 0.0f));

    // Create the color material
    D3DMATERIAL material;
    material.Ambient  = info.color;
    material.Diffuse  = info.color;
    material.Emissive = info.color;
    material.Power    = 1.0f;
    material.Specular = info.color;

    // Prepare the material
    m_pMaterial->Prepare(m, material, textures, lights); 

    // Render the mesh
    m_pSphere->DrawSubset(0);

    // Decrement the frames
    info.frames--;

    // Check if the info has expired
    if (info.frames == 0)
    {
      iter = m_SphereInfo.erase(iter);
      m_Count--;

      if (iter == end)
        break;
    }
  }
}


void DebugRenderManager::RenderBoxes()
{
  // Empty texture and light arrays
  TextureArray textures;
  LightArray   lights;

  // Render all boxes
  List<DebugRenderManager::DebugItemInfo<Box> >::iterator iter(m_BoxInfo.begin()), end(m_BoxInfo.end());
  for (; iter != end; ++iter)
  {
    DebugRenderManager::DebugItemInfo<Box> &info = *iter;

    // Create a matrix with the scale and transformation
    Matrix m = Matrix::MakeNewScaling(info.item.GetWidth(), info.item.GetHeight(), info.item.GetDepth());
    m.SetTAxis(info.item.GetCenter());

    // Create the color material
    D3DMATERIAL material;
    material.Ambient  = info.color;
    material.Diffuse  = info.color;
    material.Emissive = info.color;
    material.Power    = 1.0f;
    material.Specular = info.color;

    // Prepare the material
    m_pMaterial->Prepare(m, material, textures, lights); 

    // Render the mesh
    m_pBox->DrawSubset(0);

    // Decrement the frames
    info.frames--;

    // Check if the info has expired
    if (info.frames == 0)
    {
      iter = m_BoxInfo.erase(iter);
      m_Count--;

      if (iter == end)
        break;
    }
  }
}


void DebugRenderManager::RenderLines()
{
  // Empty texture and light arrays
  TextureArray textures;
  LightArray   lights;

  // Render all boxes
  List<DebugRenderManager::DebugItemInfo<LineSegment> >::iterator iter(m_LineInfo.begin()), end(m_LineInfo.end());
  for (; iter != end; ++iter)
  {
    DebugRenderManager::DebugItemInfo<LineSegment> &info = *iter;

    VT_PN *pVerts = (VT_PN *) m_pQuad->GetVertexData();

    pVerts[0].pos = info.item.GetStartPoint();
    pVerts[1].pos = info.item.GetStartPoint();
    pVerts[2].pos = info.item.GetEndPoint();
    pVerts[3].pos = info.item.GetEndPoint();

    pVerts[0].norm = Vec3(0.0f, 1.0f, 0.0f);
    pVerts[1].norm = Vec3(0.0f, 1.0f, 0.0f);
    pVerts[2].norm = Vec3(0.0f, 1.0f, 0.0f);
    pVerts[3].norm = Vec3(0.0f, 1.0f, 0.0f);

    m_pQuad->SetDirty(true);

    // Create the color material
    D3DMATERIAL material;
    material.Ambient  = info.color;
    material.Diffuse  = info.color;
    material.Emissive = info.color;
    material.Power    = 1.0f;
    material.Specular = info.color;

    // Prepare the material
    m_pMaterial->Prepare(MatrixIdentity, material, textures, lights); 

    // Render the mesh
    m_pQuad->RenderSubset(0);

    // Decrement the frames
    info.frames--;

    // Check if the info has expired
    if (info.frames == 0)
    {
      iter = m_LineInfo.erase(iter);
      m_Count--;

      if (iter == end)
        break;
    }
  }
}


void DebugRenderManager::RenderPlanes()
{
  // Empty texture and light arrays
  TextureArray textures;
  LightArray   lights;

  // Render all boxes
  List<DebugRenderManager::DebugItemInfo<Plane> >::iterator iter(m_PlaneInfo.begin()), end(m_PlaneInfo.end());
  for (; iter != end; ++iter)
  {
    DebugRenderManager::DebugItemInfo<Plane> &info = *iter;

    // Get the frustum planes
    const Plane *pFrustumPlanes = Camera.GetFrustum().GetPlanes();

    // Get the near and far plane
    Plane nearPlane = pFrustumPlanes[Frustum::FRONT];
    Plane farPlane  = pFrustumPlanes[Frustum::BACK];

    // Get the line along the near and far plane where the planes intersect
    Line nearLine = nearPlane.Intersect(info.item);
    Line farLine  = farPlane.Intersect(info.item);

    Plane leftPlane   = pFrustumPlanes[Frustum::LEFT];
    Plane rightPlane  = pFrustumPlanes[Frustum::RIGHT];
    Plane topPlane    = pFrustumPlanes[Frustum::TOP];
    Plane bottomPlane = pFrustumPlanes[Frustum::BOTTOM];

    Vec3 leftPtFront, rightPtFront, leftPtBack, rightPtBack;

    if (!leftPlane.Intersect(true, nearLine, leftPtFront))
      bottomPlane.Intersect(true, nearLine, leftPtFront);
    if (!rightPlane.Intersect(true, nearLine, rightPtFront))
      topPlane.Intersect(true, nearLine, leftPtFront);
    if (!leftPlane.Intersect(true, farLine, leftPtBack))
      bottomPlane.Intersect(true, farLine, leftPtBack);
    if (!rightPlane.Intersect(true, farLine, rightPtBack))
      topPlane.Intersect(true, farLine, rightPtBack);

    VT_PN *pVerts = (VT_PN *) m_pQuad->GetVertexData();

    pVerts[0].pos = leftPtFront;
    pVerts[1].pos = rightPtFront;
    pVerts[2].pos = rightPtBack;
    pVerts[3].pos = leftPtBack;

    pVerts[0].norm = info.item.GetNormal();
    pVerts[1].norm = info.item.GetNormal();
    pVerts[2].norm = info.item.GetNormal();
    pVerts[3].norm = info.item.GetNormal();

    m_pQuad->SetDirty(true);

    // Create the color material
    D3DMATERIAL material;
    material.Ambient  = info.color;
    material.Diffuse  = info.color;
    material.Emissive = info.color;
    material.Power    = 1.0f;
    material.Specular = info.color;

    // Prepare the material
    m_pMaterial->Prepare(MatrixIdentity, material, textures, lights); 

    // Render the mesh
    RenderState.Set(D3DRS_FILLMODE, D3DFILL_SOLID);
    m_pQuad->RenderSubset(0);
    RenderState.Set(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

    // Decrement the frames
    info.frames--;

    // Check if the info has expired
    if (info.frames == 0)
    {
      iter = m_PlaneInfo.erase(iter);
      m_Count--;

      if (iter == end)
        break;
    }
  }
}


// TODO ******** Needs optimisation
//
void DebugRenderManager::RenderCylinders()
{
  // Empty texture and light arrays
  TextureArray textures;
  LightArray   lights;

  // Render all boxes
  List<DebugRenderManager::DebugItemInfo<DebugRenderManager::DebugCylinder> >::iterator iter(m_CylinderInfo.begin()), end(m_CylinderInfo.end());
  for (; iter != end; ++iter)
  {
    DebugRenderManager::DebugItemInfo<DebugRenderManager::DebugCylinder> &info = *iter;

    if (FAILED(D3DXCreateCylinder(Application.GetDevice(), info.item.m_Cylinder.GetRadius(), info.item.m_Cylinder.GetRadius(), info.item.m_Cylinder.GetLength(), 12, 1, &m_pCylinder, NULL)))
      return;
    if (!m_pCylinder)
      return;

    // Create the color material
    D3DMATERIAL material;
    material.Ambient  = info.color;
    material.Diffuse  = info.color;
    material.Emissive = info.color;
    material.Power    = 1.0f;
    material.Specular = info.color;

    // Prepare the material
    m_pMaterial->Prepare(info.item.m_Matrix, material, textures, lights); 

    // Render the mesh
    m_pCylinder->DrawSubset(0);

    // Free the cylinder
    SafeRelease(m_pCylinder);
    m_pCylinder = NULL;

    // Decrement the frames
    info.frames--;

    // Check if the info has expired
    if (info.frames == 0)
    {
      iter = m_CylinderInfo.erase(iter);
      m_Count--;

      if (iter == end)
        break;
    }
  }
}


void DebugRenderManager::RenderMeshes()
{
  // Empty texture and light arrays
  TextureArray textures;
  LightArray   lights;

  // Render all meshes
  List<DebugRenderManager::DebugItemInfo<DebugRenderManager::DebugMesh> >::iterator iter(m_MeshInfo.begin()), end(m_MeshInfo.end());
  for (; iter != end; ++iter)
  {
    DebugRenderManager::DebugItemInfo<DebugRenderManager::DebugMesh> &info = *iter;
    DebugRenderManager::DebugMesh &mesh = info.item;

    // Create the color material
    D3DMATERIAL material;
    material.Ambient  = info.color;
    material.Diffuse  = info.color;
    material.Emissive = info.color;
    material.Power    = 1.0f;
    material.Specular = info.color;

    // Prepare the material
    m_pMaterial->Prepare(mesh.m_Matrix, material, textures, lights); 

    float f = -1.0f;
    DWORD d = FLOAT_TO_DWORD(f);
    RenderState.Set(D3DRS_SLOPESCALEDEPTHBIAS, d);

    // Render the mesh
    Application.GetDevice()->DrawIndexedPrimitiveUP(
      D3DPT_TRIANGLELIST, 
      0, 
      mesh.m_NumVertex, 
      mesh.m_NumIndex / 3, 
      mesh.m_pIndex, 
      D3DFMT_INDEX16, 
      mesh.m_pVertex, 
      sizeof(VT_PN));

    RenderState.SetDefault(D3DRS_SLOPESCALEDEPTHBIAS);

    // Decrement the frames
    info.frames--;

    // Check if the info has expired
    if (info.frames == 0)
    {
      iter = m_MeshInfo.erase(iter);
      m_Count--;

      if (iter == end)
        break;
    }
  }
}



// -- EOF



