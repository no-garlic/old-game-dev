
#include "RigidBodyStatic.h"
#include "PhysicsManager.h"


#define CHECK_GEOM_IS_INITIALISED              { if (m_GeomId == 0) \
                                               { ASSERT(0, "Physics Geom is not initialised"); \
                                               return; } }

#define CHECK_GEOM_IS_INITIALISED_RETURN_FALSE { if (m_GeomId == 0) \
                                               { ASSERT(0, "Physics Geom is not initialised"); \
                                               return false; } }

#define CHECK_GEOM_IS_INITIALISED_RETURN_ZERO  { if (m_GeomId == 0) \
                                               { ASSERT(0, "Physics Geom is not initialised"); \
                                               return 0; } }


RigidBodyStatic::RigidBodyStatic()
: RigidBody()
{
  m_IsStatic = true;
  m_GeomId   = 0;
}


RigidBodyStatic::~RigidBodyStatic()
{
  if (m_GeomId)
    dGeomDestroy(m_GeomId);
}


void RigidBodyStatic::SetEnabled(bool enable)
{
  CHECK_GEOM_IS_INITIALISED;

  if (enable != m_IsEnabled)
  {
    m_IsEnabled = enable;

    if (enable)
    {
      dGeomEnable(m_GeomId);
    }
    else
    {
      dGeomDisable(m_GeomId);
    }
  }
}


void RigidBodyStatic::SetPosition(const Vec3 &position)
{
  CHECK_GEOM_IS_INITIALISED;

  dGeomSetPosition(m_GeomId, position.x, position.y, position.z);
}


void RigidBodyStatic::GetPosition(Vec3 &position) const
{
  CHECK_GEOM_IS_INITIALISED;

  const dReal *pVec = dGeomGetPosition(m_GeomId);
  NULL_ASSERT(pVec);

  position.x = pVec[0];
  position.y = pVec[1];
  position.z = pVec[2];
}


void RigidBodyStatic::SetRotation(const Quat &rotation)
{
  CHECK_GEOM_IS_INITIALISED;

  dQuaternion quat;
  quat[0] = rotation.w;
  quat[1] = rotation.x;
  quat[2] = rotation.y;
  quat[3] = rotation.z;

  dGeomSetQuaternion(m_GeomId, quat);
}


void RigidBodyStatic::GetRotation(Quat &rotation) const
{
  CHECK_GEOM_IS_INITIALISED;

  dQuaternion q;
  dGeomGetQuaternion(m_GeomId, q);

  rotation.w = q[0];
  rotation.x = q[1];
  rotation.y = q[2];
  rotation.z = q[3];
}


void RigidBodyStatic::SetMatrix(const Matrix &matrix)
{
  CHECK_GEOM_IS_INITIALISED;

  // Ensure the matrix is unit scale (the input matrix is row major)
  ASSERT(matrix.IsUnitScale(), "The RigidBody matrix must be unit scale");

  // Get the position from the matrix
  Vec3 tAxis;
  matrix.GetTAxis(tAxis);

  // Create a rotation matrix (column major)
  dMatrix3 m;
  m[0]  = matrix._11;
  m[1]  = matrix._21;
  m[2]  = matrix._31;
  m[3]  = 0.0f;
  m[4]  = matrix._12;
  m[5]  = matrix._22;
  m[6]  = matrix._32;
  m[7]  = 0.0f;
  m[8]  = matrix._13;
  m[9]  = matrix._23;
  m[10] = matrix._33;
  m[11] = 0.0f;

  dGeomSetPosition(m_GeomId, tAxis.x, tAxis.y, tAxis.z);
  dGeomSetRotation(m_GeomId, m);
}


void RigidBodyStatic::GetMatrix(Matrix &matrix) const
{
  CHECK_GEOM_IS_INITIALISED;

  const dReal *pMatrix = dGeomGetRotation(m_GeomId);
  const dReal *pVec    = dGeomGetPosition(m_GeomId);

  NULL_ASSERT(pMatrix);
  NULL_ASSERT(pVec);

  // Construct a 4x4 matrix (row major)
  matrix._11 = pMatrix[0];
  matrix._21 = pMatrix[1];
  matrix._31 = pMatrix[2];
  matrix._41 = pVec[0];
  matrix._12 = pMatrix[4];
  matrix._22 = pMatrix[5];
  matrix._32 = pMatrix[6];
  matrix._42 = pVec[1];
  matrix._13 = pMatrix[8];
  matrix._23 = pMatrix[9];
  matrix._33 = pMatrix[10];
  matrix._43 = pVec[2];
  matrix._14 = 0.0f;
  matrix._24 = 0.0f;
  matrix._34 = 0.0f;
  matrix._44 = 1.0f;
}


void RigidBodyStatic::SetCollisionMask(ulong mask)
{
  CHECK_GEOM_IS_INITIALISED;

  dGeomSetCollideBits(m_GeomId, mask);
}


ulong RigidBodyStatic::GetCollisionMask() const
{
  CHECK_GEOM_IS_INITIALISED_RETURN_ZERO;

  return dGeomGetCollideBits(m_GeomId);
}


void RigidBodyStatic::SetCategoryMask(ulong mask)
{
  CHECK_GEOM_IS_INITIALISED;

  dGeomSetCategoryBits(m_GeomId, mask);
}


ulong RigidBodyStatic::GetCategoryMask() const
{
  CHECK_GEOM_IS_INITIALISED_RETURN_ZERO;

  return dGeomGetCategoryBits(m_GeomId);
}


// ============================================================================
// SPHERE
// ============================================================================


RigidBodyStaticSphere::RigidBodyStaticSphere()
: RigidBodyStatic(),
  RigidBodySphere()
{
}


RigidBodyStaticSphere::~RigidBodyStaticSphere()
{
}


bool RigidBodyStaticSphere::Init(const RigidBody::InitData *pInitData)
{
  ASSERT(pInitData->Type == RigidBody::RB_SPHERE, "Invalid Type");

  RigidBodySphere::SphereInitData *pSphereInitData = (RigidBodySphere::SphereInitData *) pInitData;

  return Init(pSphereInitData->Radius);
}


bool RigidBodyStaticSphere::Init(float radius)
{
  m_GeomId = dCreateSphere(Physics.GetSpace(PhysicsManager::Static), radius);

  CHECK_GEOM_IS_INITIALISED_RETURN_FALSE;

  SetCategoryMask(PhysicsManager::CAT_STATIC);
  SetCollisionMask(PhysicsManager::CAT_ALL);

  return true;
}


void RigidBodyStaticSphere::SetRadius(float radius)
{
  CHECK_GEOM_IS_INITIALISED;

  dGeomSphereSetRadius(m_GeomId, radius);
}


void RigidBodyStaticSphere::GetRadius(float &radius) const
{
  CHECK_GEOM_IS_INITIALISED;

  radius = dGeomSphereGetRadius(m_GeomId);
}


void RigidBodyStaticSphere::Render()
{
  Sphere s;
  GetRadius(s.radius);
  GetPosition(s.center);

  DEBUG_SPHERE(s, Color::Red, 1);
}


// ============================================================================
// BOX
// ============================================================================


RigidBodyStaticBox::RigidBodyStaticBox()
: RigidBodyStatic(),
  RigidBodyBox()
{
}


RigidBodyStaticBox::~RigidBodyStaticBox()
{
}


bool RigidBodyStaticBox::Init(const RigidBody::InitData *pInitData)
{
  ASSERT(pInitData->Type == RigidBody::RB_BOX, "Invalid Type");

  RigidBodyStaticBox::BoxInitData *pBoxInitData = (RigidBodyStaticBox::BoxInitData *) pInitData;

  return Init(pBoxInitData->Extents);
}


bool RigidBodyStaticBox::Init(const Vec3 &extents)
{
  m_GeomId = dCreateBox(Physics.GetSpace(PhysicsManager::Static), extents.x, extents.y, extents.z);

  CHECK_GEOM_IS_INITIALISED_RETURN_FALSE;

  SetCategoryMask(PhysicsManager::CAT_STATIC);
  SetCollisionMask(PhysicsManager::CAT_ALL);

  return true;
}


void RigidBodyStaticBox::SetExtents(const Vec3 &extents)
{
  CHECK_GEOM_IS_INITIALISED;

  dGeomBoxSetLengths(m_GeomId, extents.x, extents.y, extents.z);
}


void RigidBodyStaticBox::GetExtents(Vec3 &extents) const
{
  CHECK_GEOM_IS_INITIALISED;

  dVector3 vec;
  dGeomBoxGetLengths(m_GeomId, vec);

  extents.x = vec[0];
  extents.y = vec[1];
  extents.z = vec[2];
}


void RigidBodyStaticBox::Render()
{
  CHECK_GEOM_IS_INITIALISED;

  Vec3 extents, origin;
  GetPosition(origin);
  GetExtents(extents);

  Box box;
  box.SetMin(origin - (extents * 0.5f));
  box.SetMax(origin + (extents * 0.5f));
  
  DEBUG_BOX(box, Color::Red, 1);
}


// ============================================================================
// CYLINDER
// ============================================================================


RigidBodyStaticCylinder::RigidBodyStaticCylinder()
: RigidBodyStatic(),
  RigidBodyCylinder()
{
}


RigidBodyStaticCylinder::~RigidBodyStaticCylinder()
{
}


bool RigidBodyStaticCylinder::Init(const RigidBody::InitData *pInitData)
{
  ASSERT(pInitData->Type == RigidBody::RB_CYLINDER, "Invalid Type");

  RigidBodyStaticCylinder::CylinderInitData *pCylinderInitData = (RigidBodyStaticCylinder::CylinderInitData *) pInitData;

  return Init(pCylinderInitData->Radius, pCylinderInitData->Length);
}


bool RigidBodyStaticCylinder::Init(float radius, float length)
{
  m_GeomId = dCreateCylinder(Physics.GetSpace(PhysicsManager::Static), radius, length);

  CHECK_GEOM_IS_INITIALISED_RETURN_FALSE;

  SetCategoryMask(PhysicsManager::CAT_STATIC);
  SetCollisionMask(PhysicsManager::CAT_ALL);

  return true;
}


void RigidBodyStaticCylinder::SetMatrix(const Matrix &matrix)
{
  //const float PI_DIV_2 = D3DX_PI * 0.5f;
  //Matrix rMat = Matrix::MakeNewRotationAxis(Vec3(1.0f, 0.0f, 0.0f), PI_DIV_2);

  Matrix m = matrix;
  m.PostMultiply(m_OrientationMatrix);

  RigidBodyStatic::SetMatrix(m);
}


void RigidBodyStaticCylinder::GetMatrix(Matrix &matrix) const
{
  //const float PI_DIV_2 = D3DX_PI * 0.5f;
  //Matrix rMat = Matrix::MakeNewRotationAxis(Vec3(1.0f, 0.0f, 0.0f), -PI_DIV_2);

  RigidBodyStatic::GetMatrix(matrix);
  matrix.PostMultiply(m_OrientationMatrixInverse);
}


void RigidBodyStaticCylinder::SetRotation(const Quat &rotation)
{
  ASSERT(0, "Not Tested");

  Quat q, r;

  r.RotationMatrix(m_OrientationMatrix);
  
  q = rotation;
  q.Multiply(r);

  RigidBodyStatic::SetRotation(q);
}


void RigidBodyStaticCylinder::GetRotation(Quat &rotation) const
{
  ASSERT(0, "Not Tested");

  Quat q, r;

  r.RotationMatrix(m_OrientationMatrixInverse);
  
  RigidBodyStatic::GetRotation(q);

  q = rotation;
  r.Multiply(q);

  rotation = r;
}


void RigidBodyStaticCylinder::SetRadius(float radius)
{
  CHECK_GEOM_IS_INITIALISED;

  float length;
  GetLength(length);

  dGeomCylinderSetParams(m_GeomId, radius, length);
}


void RigidBodyStaticCylinder::SetLength(float length)
{
  CHECK_GEOM_IS_INITIALISED;

  float radius;
  GetRadius(radius);

  dGeomCylinderSetParams(m_GeomId, radius, length);
}


void RigidBodyStaticCylinder::GetRadius(float &radius) const
{
  CHECK_GEOM_IS_INITIALISED;

  float length;
  dGeomCylinderGetParams(m_GeomId, &radius, &length);
}


void RigidBodyStaticCylinder::GetLength(float &length) const
{
  CHECK_GEOM_IS_INITIALISED;

  float radius;
  dGeomCylinderGetParams(m_GeomId, &radius, &length);
}


void RigidBodyStaticCylinder::Render()
{
  float radius, length;
  GetRadius(radius);
  GetLength(length);

  Matrix m;
  GetMatrix(m);

  DEBUG_CYLINDER(m, Cylinder(radius, length), Color::Red, 1);
}


// ============================================================================
// CAPPED CYLINDER
// ============================================================================


RigidBodyStaticCappedCylinder::RigidBodyStaticCappedCylinder()
: RigidBodyStaticCylinder()
{
}


RigidBodyStaticCappedCylinder::~RigidBodyStaticCappedCylinder()
{
}


bool RigidBodyStaticCappedCylinder::Init(float radius, float length)
{
  m_GeomId = dCreateCCylinder(Physics.GetSpace(PhysicsManager::Static), radius, length);

  CHECK_GEOM_IS_INITIALISED_RETURN_FALSE;

  SetCategoryMask(PhysicsManager::CAT_STATIC);
  SetCollisionMask(PhysicsManager::CAT_ALL);

  return true;
}


void RigidBodyStaticCappedCylinder::SetRadius(float radius)
{
  CHECK_GEOM_IS_INITIALISED;

  float length;
  GetLength(length);

  dGeomCCylinderSetParams(m_GeomId, radius, length);
}


void RigidBodyStaticCappedCylinder::SetLength(float length)
{
  CHECK_GEOM_IS_INITIALISED;

  float radius;
  GetRadius(radius);

  dGeomCCylinderSetParams(m_GeomId, radius, length);
}


void RigidBodyStaticCappedCylinder::GetRadius(float &radius) const
{
  CHECK_GEOM_IS_INITIALISED;

  float length;
  dGeomCCylinderGetParams(m_GeomId, &radius, &length);
}


void RigidBodyStaticCappedCylinder::GetLength(float &length) const
{
  CHECK_GEOM_IS_INITIALISED;

  float radius;
  dGeomCCylinderGetParams(m_GeomId, &radius, &length);
}


void RigidBodyStaticCappedCylinder::Render()
{
  // TODO
}


// ============================================================================
// MESH
// ============================================================================


RigidBodyStaticIndexedMesh::RigidBodyStaticIndexedMesh()
: RigidBodyStatic(),
  RigidBodyIndexedMesh()
{
  m_NumVertex               = 0;
  m_NumIndex                = 0;
  m_pPositionData           = 0;
  m_pNormalData             = 0;
  m_pIndexData              = 0;
  m_pDebugRenderVertexData  = 0;
  m_pDebugRenderIndexData   = 0;
}


RigidBodyStaticIndexedMesh::~RigidBodyStaticIndexedMesh()
{
  // TODO -> cleanup
}


bool RigidBodyStaticIndexedMesh::Init(const RigidBody::InitData *pInitData)
{
  ASSERT(pInitData->Type == RigidBody::RB_MESH, "Invalid Type");

  RigidBodyStaticIndexedMesh::IndexedMeshInitData *pMeshInitData = (RigidBodyStaticIndexedMesh::IndexedMeshInitData *) pInitData;

  return Init(pMeshInitData->pMesh);
}


bool RigidBodyStaticIndexedMesh::Init(IndexedMesh *pMesh)
{
  NULL_ASSERT(pMesh);

  const VertexType *pVertexType = pMesh->GetVertexType();
  NULL_ASSERT(pVertexType);

  uint numVerts = pMesh->GetNumVerts();
  uint numIndex = pMesh->GetNumFaces() * 3;
  
  const uchar *pVertexData = (const uchar *) pMesh->GetVertexData();
  const void  *pIndexData  = (const void  *) pMesh->GetFaceData();

  int positionOffset = pVertexType->GetItemOffset(VI_Position);
  int normalOffset   = pVertexType->GetItemOffset(VI_Normal);
  int vertexStride   = pVertexType->GetSize();

  ASSERT(positionOffset >= 0, "Vertex data is missing position data");
  ASSERT(normalOffset   >= 0, "Vertex data is missing normal data");

  const uchar *pPositionData = pVertexData + positionOffset;
  const uchar *pNormalData   = pVertexData + normalOffset;

  return Create(pPositionData, vertexStride, numVerts, pIndexData, sizeof(ushort), numIndex, pNormalData, vertexStride);
}


bool RigidBodyStaticIndexedMesh::Create(const void *pVertices, int vertexStride, int vertexCount, 
                                        const void *pIndices,  int indexStride,  int indexCount, 
                                        const void *pNormals,  int normalStride)
{
  NULL_ASSERT(pVertices);
  NULL_ASSERT(pIndices);
  NULL_ASSERT(pNormals);
  NULL_ASSERT(vertexCount);
  NULL_ASSERT(indexCount);

  // Store the vertex and index count
  m_NumVertex = vertexCount;
  m_NumIndex  = indexCount;

  // Create a local copy of the data
  m_pPositionData           = new Vec3[m_NumVertex];
  m_pNormalData             = new Vec3[m_NumVertex];
  m_pIndexData              = new int[m_NumIndex];
  m_pDebugRenderVertexData  = new VT_PN[m_NumVertex];
  m_pDebugRenderIndexData   = new ushort[m_NumIndex];

  // Get pointers to the source data
  const uchar  *pSrcVerts = (uchar *)  pVertices;
  const uchar  *pSrcNorms = (uchar *)  pNormals;
  const ushort *pSrcIndex = (ushort *) pIndices;

  // Copy the position and normal data
  for (int i = 0; i < vertexCount; i++)
  {
    // Copy the collision data
    m_pPositionData[i] = (*((Vec3 *)(pSrcVerts)));
    m_pNormalData[i]   = (*((Vec3 *)(pSrcNorms)));

    // Copy the debug render data
    m_pDebugRenderVertexData[i].pos  = m_pPositionData[i];
    m_pDebugRenderVertexData[i].norm = m_pNormalData[i];

    // Increment the pointers
    pSrcNorms += normalStride;
    pSrcVerts += vertexStride;
  }

  // Copy the index data
  for (int i = 0; i < indexCount; i++)
  {
    ushort indexVal = pSrcIndex[i];
    m_pIndexData[i] = (int) indexVal;
    m_pDebugRenderIndexData[i] = indexVal;
  }

  // Create the tri mesh
  dTriMeshDataID triMeshId = dGeomTriMeshDataCreate();
  dGeomTriMeshDataBuildSingle1(triMeshId, m_pPositionData, sizeof(Vec3), m_NumVertex, 
    m_pIndexData, m_NumIndex, sizeof(int) * 3, m_pNormalData);

  // Create the geom and the body
  m_GeomId = dCreateTriMesh(Physics.GetSpace(PhysicsManager::Static), triMeshId, NULL, NULL, NULL);
  CHECK_GEOM_IS_INITIALISED_RETURN_FALSE;

  SetCategoryMask(PhysicsManager::CAT_STATIC);
  SetCollisionMask(PhysicsManager::CAT_ALL);

  return true;
}


void RigidBodyStaticIndexedMesh::Render()
{
  Matrix m;
  GetMatrix(m);
  DEBUG_MESH(m, m_pDebugRenderVertexData, m_NumVertex, m_pDebugRenderIndexData, m_NumIndex, Color::Red, 1);
}


// -- EOF

