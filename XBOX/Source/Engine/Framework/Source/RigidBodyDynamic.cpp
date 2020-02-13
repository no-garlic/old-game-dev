
#include "RigidBodyDynamic.h"
#include "PhysicsManager.h"


#define CHECK_BODY_IS_INITIALISED              { if (m_BodyId == 0) \
                                               { ASSERT(0, "Physics Body is not initialised"); \
                                               return; } }

#define CHECK_BODY_IS_INITIALISED_RETURN_FALSE { if (m_BodyId == 0) \
                                               { ASSERT(0, "Physics Body is not initialised"); \
                                               return false; } }

#define CHECK_BODY_IS_INITIALISED_RETURN_ZERO  { if (m_BodyId == 0) \
                                               { ASSERT(0, "Physics Body is not initialised"); \
                                               return 0; } }

#define CHECK_GEOM_IS_INITIALISED              { if (m_GeomId == 0) \
                                               { ASSERT(0, "Physics Geom is not initialised"); \
                                               return; } }

#define CHECK_GEOM_IS_INITIALISED_RETURN_FALSE { if (m_GeomId == 0) \
                                               { ASSERT(0, "Physics Geom is not initialised"); \
                                               return false; } }

#define CHECK_GEOM_IS_INITIALISED_RETURN_ZERO  { if (m_GeomId == 0) \
                                               { ASSERT(0, "Physics Geom is not initialised"); \
                                               return 0; } }


RigidBodyDynamic::RigidBodyDynamic()
: RigidBody()
{
  m_IsStatic = false;
  m_GeomId   = 0;
  m_BodyId   = 0;
}


RigidBodyDynamic::~RigidBodyDynamic()
{
  if (m_GeomId)
    dGeomDestroy(m_GeomId);

  if (m_BodyId)
    dBodyDestroy(m_BodyId);
}


void RigidBodyDynamic::SetEnabled(bool enable)
{
  CHECK_GEOM_IS_INITIALISED;
  CHECK_BODY_IS_INITIALISED;

  if (enable != m_IsEnabled)
  {
    m_IsEnabled = enable;

    if (enable)
    {
      dGeomEnable(m_GeomId);
      dBodyEnable(m_BodyId);
    }
    else
    {
      dGeomDisable(m_GeomId);
      dBodyDisable(m_BodyId);
    }
  }
}


void RigidBodyDynamic::SetPosition(const Vec3 &position)
{
  CHECK_BODY_IS_INITIALISED;

  dBodySetPosition(m_BodyId, position.x, position.y, position.z);
}


void RigidBodyDynamic::GetPosition(Vec3 &position) const
{
  CHECK_BODY_IS_INITIALISED;

  const dReal *pVec = dBodyGetPosition(m_BodyId);
  NULL_ASSERT(pVec);

  position.x = pVec[0];
  position.y = pVec[1];
  position.z = pVec[2];
}


void RigidBodyDynamic::SetRotation(const Quat &rotation)
{
  CHECK_BODY_IS_INITIALISED;

  dQuaternion quat;
  quat[0] = rotation.w;
  quat[1] = rotation.x;
  quat[2] = rotation.y;
  quat[3] = rotation.z;

  dBodySetQuaternion(m_BodyId, quat);
}


void RigidBodyDynamic::GetRotation(Quat &rotation) const
{
  CHECK_BODY_IS_INITIALISED;

  const dReal *pQuat = dBodyGetQuaternion(m_BodyId);
  NULL_ASSERT(pQuat);

  rotation.w = pQuat[0];
  rotation.x = pQuat[1];
  rotation.y = pQuat[2];
  rotation.z = pQuat[3];
}


void RigidBodyDynamic::SetMatrix(const Matrix &matrix)
{
  CHECK_BODY_IS_INITIALISED;

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

  dBodySetPosition(m_BodyId, tAxis.x, tAxis.y, tAxis.z);
  dBodySetRotation(m_BodyId, m);
}


void RigidBodyDynamic::GetMatrix(Matrix &matrix) const
{
  CHECK_BODY_IS_INITIALISED;

  const dReal *pMatrix = dBodyGetRotation(m_BodyId);
  const dReal *pVec    = dBodyGetPosition(m_BodyId);

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


void RigidBodyDynamic::SetCollisionMask(ulong mask)
{
  CHECK_GEOM_IS_INITIALISED;

  dGeomSetCollideBits(m_GeomId, mask);
}


ulong RigidBodyDynamic::GetCollisionMask() const
{
  CHECK_GEOM_IS_INITIALISED_RETURN_ZERO;

  return dGeomGetCollideBits(m_GeomId);
}


void RigidBodyDynamic::SetCategoryMask(ulong mask)
{
  CHECK_GEOM_IS_INITIALISED;

  dGeomSetCategoryBits(m_GeomId, mask);
}


ulong RigidBodyDynamic::GetCategoryMask() const
{
  CHECK_GEOM_IS_INITIALISED_RETURN_ZERO;

  return dGeomGetCategoryBits(m_GeomId);
}


void RigidBodyDynamic::SetLinearVelocity(const Vec3 &velocity)
{
  CHECK_BODY_IS_INITIALISED;

  dBodySetLinearVel(m_BodyId, velocity.x, velocity.y, velocity.z);
}


void RigidBodyDynamic::SetAngularVelocity(const Vec3 &velocity)
{
  CHECK_BODY_IS_INITIALISED;

  dBodySetAngularVel(m_BodyId, velocity.x, velocity.y, velocity.z);
}


void RigidBodyDynamic::GetLinearVelocity(Vec3 &velocity) const
{
  CHECK_BODY_IS_INITIALISED;

  const dReal *pVec = dBodyGetLinearVel(m_BodyId);
  NULL_ASSERT(pVec);

  velocity.Set(pVec[0], pVec[1], pVec[2]);
}


void RigidBodyDynamic::GetAngularVelocity(Vec3 &velocity) const
{
  CHECK_BODY_IS_INITIALISED;

  const dReal *pVec = dBodyGetAngularVel(m_BodyId);
  NULL_ASSERT(pVec);

  velocity.Set(pVec[0], pVec[1], pVec[2]);
}



void RigidBodyDynamic::AddForce(const Vec3 &force)
{
  CHECK_BODY_IS_INITIALISED;

  dBodyAddForce(m_BodyId, force.x, force.y, force.z);
}


void RigidBodyDynamic::AddTorque(const Vec3 &torque)
{
  CHECK_BODY_IS_INITIALISED;

  dBodyAddTorque(m_BodyId, torque.x, torque.y, torque.z);
}


void RigidBodyDynamic::AddLocalForce(const Vec3 &force)
{
  CHECK_BODY_IS_INITIALISED;

  dBodyAddRelForce(m_BodyId, force.x, force.y, force.z);
}


void RigidBodyDynamic::AddLocalTorque(const Vec3 &torque)
{
  CHECK_BODY_IS_INITIALISED;

  dBodyAddRelTorque(m_BodyId, torque.x, torque.y, torque.z);
}


void RigidBodyDynamic::AddForceAtPosition(const Vec3 &force, const Vec3 &position)
{
  CHECK_BODY_IS_INITIALISED;

  dBodyAddForceAtPos(m_BodyId, force.x, force.y, force.z, position.x, position.y, position.z);
}


void RigidBodyDynamic::AddForceAtLocalPosition(const Vec3 &force, const Vec3 &position)
{
  CHECK_BODY_IS_INITIALISED;

  dBodyAddForceAtRelPos(m_BodyId, force.x, force.y, force.z, position.x, position.y, position.z);
}


void RigidBodyDynamic::AddLocalForceAtPos(const Vec3 &force, const Vec3 &position)
{
  CHECK_BODY_IS_INITIALISED;

  dBodyAddRelForceAtPos(m_BodyId, force.x, force.y, force.z, position.x, position.y, position.z);
}


void RigidBodyDynamic::AddLocalForceAtLocalPos(const Vec3 &force, const Vec3 &position)
{
  CHECK_BODY_IS_INITIALISED;

  dBodyAddRelForceAtRelPos(m_BodyId, force.x, force.y, force.z, position.x, position.y, position.z);
}


void RigidBodyDynamic::SetForce(const Vec3 &force)
{
  CHECK_BODY_IS_INITIALISED;

  dBodySetForce(m_BodyId, force.x, force.y, force.z);
}


void RigidBodyDynamic::SetTorque(const Vec3 &torque)
{
  CHECK_BODY_IS_INITIALISED;

  dBodySetTorque(m_BodyId, torque.x, torque.y, torque.z);
}


void RigidBodyDynamic::GetForce(Vec3 &force) const
{
  CHECK_BODY_IS_INITIALISED;

  const dReal *pVec = dBodyGetForce(m_BodyId);
  NULL_ASSERT(pVec);

  force.Set(pVec[0], pVec[1], pVec[2]);
}


void RigidBodyDynamic::GetTorque(Vec3 &torque) const
{
  CHECK_BODY_IS_INITIALISED;

  const dReal *pVec = dBodyGetTorque(m_BodyId);
  NULL_ASSERT(pVec);

  torque.Set(pVec[0], pVec[1], pVec[2]);
}


void RigidBodyDynamic::ConvertLocalPositonToWorldPosition(const Vec3 &localPosition, Vec3 &worldPosition) const
{
  CHECK_BODY_IS_INITIALISED;

  dVector3 result;
  dBodyGetRelPointPos(m_BodyId, localPosition.x, localPosition.y, localPosition.z, result);

  worldPosition.x = result[0];
  worldPosition.y = result[1];
  worldPosition.z = result[2];
}


void RigidBodyDynamic::ConvertWorldPositonToLocalPosition(const Vec3 &worldPosition, Vec3 &localPosition) const
{
  CHECK_BODY_IS_INITIALISED;

  dVector3 result;
  dBodyGetPosRelPoint(m_BodyId, worldPosition.x, worldPosition.y, worldPosition.z, result);

  localPosition.x = result[0];
  localPosition.y = result[1];
  localPosition.z = result[2];
}


void RigidBodyDynamic::ConvertLocalVectorToWorldVector(const Vec3 &localVector, Vec3 &worldVector) const
{
  CHECK_BODY_IS_INITIALISED;

  dVector3 result;
  dBodyVectorToWorld(m_BodyId, localVector.x, localVector.y, localVector.z, result);

  worldVector.x = result[0];
  worldVector.y = result[1];
  worldVector.z = result[2];
}


void RigidBodyDynamic::ConvertWorldVectorToLocalVector(const Vec3 &worldVector, Vec3 &localVector) const
{
  CHECK_BODY_IS_INITIALISED;

  dVector3 result;
  dBodyVectorFromWorld(m_BodyId, worldVector.x, worldVector.y, worldVector.z, result);

  localVector.x = result[0];
  localVector.y = result[1];
  localVector.z = result[2];
}


void RigidBodyDynamic::GetVelocityAtLocalPosition(const Vec3 &position, Vec3 &velocity) const
{
  CHECK_BODY_IS_INITIALISED;

  dVector3 result;
  dBodyGetRelPointVel(m_BodyId, position.x, position.y, position.z, result);

  velocity.x = result[0];
  velocity.y = result[1];
  velocity.z = result[2];
}


void RigidBodyDynamic::GetVelocityAtPosition(const Vec3 &position, Vec3 &velocity) const
{
  CHECK_BODY_IS_INITIALISED;

  dVector3 result;
  dBodyGetPointVel(m_BodyId, position.x, position.y, position.z, result);

  velocity.x = result[0];
  velocity.y = result[1];
  velocity.z = result[2];
}


void RigidBodyDynamic::SetAutoDisableUseWorldDefaults()
{
  CHECK_BODY_IS_INITIALISED;

  dBodySetAutoDisableDefaults(m_BodyId);
}


void RigidBodyDynamic::SetAutoDisableEnabled(bool enable)
{
  CHECK_BODY_IS_INITIALISED;

  dBodySetAutoDisableFlag(m_BodyId, enable ? 1 : 0);
}


bool RigidBodyDynamic::IsAutoDisableEnabled() const
{
  CHECK_BODY_IS_INITIALISED_RETURN_FALSE;

  if (dBodyGetAutoDisableFlag(m_BodyId) == 0)
    return false;

  return true;
}


void RigidBodyDynamic::SetAutoDisableLinearThreashold(float threashold)
{
  CHECK_BODY_IS_INITIALISED;

  dBodySetAutoDisableLinearThreshold(m_BodyId, threashold);
}


void RigidBodyDynamic::GetAutoDisableLinearThreashold(float &threashold) const
{
  CHECK_BODY_IS_INITIALISED;

  threashold = dBodyGetAutoDisableLinearThreshold(m_BodyId);
}


void RigidBodyDynamic::SetAutoDisableAngularThreashold(float threashold)
{
  CHECK_BODY_IS_INITIALISED;

  dBodySetAutoDisableAngularThreshold(m_BodyId, threashold);
}


void RigidBodyDynamic::GetAutoDisableAngularThreashold(float &threashold) const
{
  CHECK_BODY_IS_INITIALISED;

  threashold = dBodyGetAutoDisableAngularThreshold(m_BodyId);
}


void RigidBodyDynamic::SetAutoDisableStepCount(int numSteps)
{
  CHECK_BODY_IS_INITIALISED;

  dBodySetAutoDisableSteps(m_BodyId, numSteps);
}


void RigidBodyDynamic::GetAutoDisableStepCount(int &numSteps) const
{
  CHECK_BODY_IS_INITIALISED;

  numSteps = dBodyGetAutoDisableSteps(m_BodyId);
}


void RigidBodyDynamic::SetAutoDisableTime(float seconds)
{
  CHECK_BODY_IS_INITIALISED;

  dBodySetAutoDisableTime(m_BodyId, seconds);
}


void RigidBodyDynamic::GetAutoDisableTime(float &seconds) const
{
  CHECK_BODY_IS_INITIALISED;

  seconds = dBodyGetAutoDisableTime(m_BodyId);
}


void RigidBodyDynamic::SetGravityEnabled(bool enabled)
{
  CHECK_BODY_IS_INITIALISED;

  dBodySetGravityMode(m_BodyId, enabled ? 1 : 0);
}


bool RigidBodyDynamic::IsGravityEnabled() const
{
  CHECK_BODY_IS_INITIALISED_RETURN_FALSE;

  if (dBodyGetGravityMode(m_BodyId) == 0)
    return false;

  return true;
}


void RigidBodyDynamic::GetAABB(Box &aabb)
{
  CHECK_GEOM_IS_INITIALISED;

  dReal pAABB[6];
  dGeomGetAABB(m_GeomId, pAABB);

  aabb.MinPt.Set(pAABB[0], pAABB[2], pAABB[4]);
  aabb.MaxPt.Set(pAABB[1], pAABB[3], pAABB[5]);
}


// ============================================================================
// SPHERE
// ============================================================================


RigidBodyDynamicSphere::RigidBodyDynamicSphere()
: RigidBodyDynamic(),
  RigidBodySphere()
{
}


RigidBodyDynamicSphere::~RigidBodyDynamicSphere()
{
}


bool RigidBodyDynamicSphere::Init(const RigidBody::InitData *pInitData)
{
  ASSERT(pInitData->Type == RigidBody::RB_SPHERE, "Invalid Type");

  RigidBodySphere::SphereInitData *pSphereInitData = (RigidBodySphere::SphereInitData *) pInitData;

  return Init(pSphereInitData->Radius);
}


bool RigidBodyDynamicSphere::Init(float radius)
{
  m_GeomId = dCreateSphere(Physics.GetSpace(PhysicsManager::Actor), radius);
  m_BodyId = dBodyCreate(Physics.GetWorld());

  CHECK_GEOM_IS_INITIALISED_RETURN_FALSE;
  CHECK_BODY_IS_INITIALISED_RETURN_FALSE;
    
  dGeomSetBody(m_GeomId, m_BodyId);
  SetMassFromDensity(1.0f);

  SetCategoryMask(PhysicsManager::CAT_DYNAMIC);
  SetCollisionMask(PhysicsManager::CAT_ALL);

  return true;
}


void RigidBodyDynamicSphere::SetRadius(float radius)
{
  CHECK_GEOM_IS_INITIALISED;

  dGeomSphereSetRadius(m_GeomId, radius);
}


void RigidBodyDynamicSphere::GetRadius(float &radius) const
{
  CHECK_GEOM_IS_INITIALISED;

  radius = dGeomSphereGetRadius(m_GeomId);
}


void RigidBodyDynamicSphere::SetMassFromDensity(float density)
{
  CHECK_GEOM_IS_INITIALISED;
  CHECK_BODY_IS_INITIALISED;

  float radius = dGeomSphereGetRadius(m_GeomId);

  dMass m;
  dMassSetSphere(&m, density, radius);
  dBodySetMass(m_BodyId, &m);
}


void RigidBodyDynamicSphere::SetMass(float mass)
{
  CHECK_GEOM_IS_INITIALISED;
  CHECK_BODY_IS_INITIALISED;

  float radius = dGeomSphereGetRadius(m_GeomId);

  dMass m;
  dMassSetSphereTotal(&m, mass, radius);
  dBodySetMass(m_BodyId, &m);
}


void RigidBodyDynamicSphere::Render()
{
  Sphere s;
  GetRadius(s.radius);
  GetPosition(s.center);

  DEBUG_SPHERE(s, Color::Green, 1);
}


// ============================================================================
// BOX
// ============================================================================


RigidBodyDynamicBox::RigidBodyDynamicBox()
: RigidBodyDynamic(),
  RigidBodyBox()
{
}


RigidBodyDynamicBox::~RigidBodyDynamicBox()
{
}


bool RigidBodyDynamicBox::Init(const RigidBody::InitData *pInitData)
{
  ASSERT(pInitData->Type == RigidBody::RB_BOX, "Invalid Type");

  RigidBodyDynamicBox::BoxInitData *pBoxInitData = (RigidBodyDynamicBox::BoxInitData *) pInitData;

  return Init(pBoxInitData->Extents);
}


bool RigidBodyDynamicBox::Init(const Vec3 &extents)
{
  m_GeomId = dCreateBox(Physics.GetSpace(PhysicsManager::Actor), extents.x, extents.y, extents.z);
  m_BodyId = dBodyCreate(Physics.GetWorld());

  CHECK_GEOM_IS_INITIALISED_RETURN_FALSE;
  CHECK_BODY_IS_INITIALISED_RETURN_FALSE;
    
  dGeomSetBody(m_GeomId, m_BodyId);
  SetMassFromDensity(1.0f);

  SetCategoryMask(PhysicsManager::CAT_DYNAMIC);
  SetCollisionMask(PhysicsManager::CAT_ALL);

  return true;
}


void RigidBodyDynamicBox::SetExtents(const Vec3 &extents)
{
  CHECK_GEOM_IS_INITIALISED;

  dGeomBoxSetLengths(m_GeomId, extents.x, extents.y, extents.z);
}


void RigidBodyDynamicBox::GetExtents(Vec3 &extents) const
{
  CHECK_GEOM_IS_INITIALISED;

  dVector3 vec;
  dGeomBoxGetLengths(m_GeomId, vec);

  extents.x = vec[0];
  extents.y = vec[1];
  extents.z = vec[2];
}


void RigidBodyDynamicBox::SetMassFromDensity(float density)
{
  CHECK_BODY_IS_INITIALISED;
  CHECK_GEOM_IS_INITIALISED;

  dVector3 vec;
  dGeomBoxGetLengths(m_GeomId, vec);

  dMass m;
  dMassSetBox(&m, density, vec[0], vec[1], vec[2]);
  dBodySetMass(m_BodyId, &m);
}


void RigidBodyDynamicBox::SetMass(float mass)
{
  CHECK_BODY_IS_INITIALISED;
  CHECK_GEOM_IS_INITIALISED;

  dVector3 vec;
  dGeomBoxGetLengths(m_GeomId, vec);

  dMass m;
  dMassSetBoxTotal(&m, mass, vec[0], vec[1], vec[2]);
  dBodySetMass(m_BodyId, &m);
}


void RigidBodyDynamicBox::Render()
{
  CHECK_GEOM_IS_INITIALISED;

  Vec3 extents, origin;
  GetPosition(origin);
  GetExtents(extents);

  Box box;
  box.SetMin(origin - (extents * 0.5f));
  box.SetMax(origin + (extents * 0.5f));
  
  DEBUG_BOX(box, Color::Green, 1);
}


// ============================================================================
// CYLINDER
// ============================================================================


RigidBodyDynamicCylinder::RigidBodyDynamicCylinder()
: RigidBodyDynamic(),
  RigidBodyCylinder()
{
}


RigidBodyDynamicCylinder::~RigidBodyDynamicCylinder()
{
}


bool RigidBodyDynamicCylinder::Init(const RigidBody::InitData *pInitData)
{
  ASSERT(pInitData->Type == RigidBody::RB_CYLINDER, "Invalid Type");

  RigidBodyDynamicCylinder::CylinderInitData *pCylinderInitData = (RigidBodyDynamicCylinder::CylinderInitData *) pInitData;

  return Init(pCylinderInitData->Radius, pCylinderInitData->Length);
}


bool RigidBodyDynamicCylinder::Init(float radius, float length)
{
  m_GeomId = dCreateCylinder(Physics.GetSpace(PhysicsManager::Actor), radius, length);
  m_BodyId = dBodyCreate(Physics.GetWorld());

  CHECK_GEOM_IS_INITIALISED_RETURN_FALSE;
  CHECK_BODY_IS_INITIALISED_RETURN_FALSE;
    
  dGeomSetBody(m_GeomId, m_BodyId);
  SetMassFromDensity(1.0f);

  SetCategoryMask(PhysicsManager::CAT_DYNAMIC);
  SetCollisionMask(PhysicsManager::CAT_ALL);

  return true;
}


void RigidBodyDynamicCylinder::SetMatrix(const Matrix &matrix)
{
  //const float PI_DIV_2 = D3DX_PI * 0.5f;
  //Matrix rMat = Matrix::MakeNewRotationAxis(Vec3(1.0f, 0.0f, 0.0f), PI_DIV_2);

  Matrix m = matrix;
  m.PostMultiply(m_OrientationMatrix);

  RigidBodyDynamic::SetMatrix(m);
}


void RigidBodyDynamicCylinder::GetMatrix(Matrix &matrix) const
{
  //const float PI_DIV_2 = D3DX_PI * 0.5f;
  //Matrix rMat = Matrix::MakeNewRotationAxis(Vec3(1.0f, 0.0f, 0.0f), -PI_DIV_2);

  RigidBodyDynamic::GetMatrix(matrix);
  matrix.PostMultiply(m_OrientationMatrixInverse);
}


void RigidBodyDynamicCylinder::SetRotation(const Quat &rotation)
{
  ASSERT(0, "Not Tested");

  Quat q, r;

  r.RotationMatrix(m_OrientationMatrix);
  
  q = rotation;
  q.Multiply(r);

  RigidBodyDynamic::SetRotation(q);
}


void RigidBodyDynamicCylinder::GetRotation(Quat &rotation) const
{
  ASSERT(0, "Not Tested");

  Quat q, r;

  r.RotationMatrix(m_OrientationMatrixInverse);
  
  RigidBodyDynamic::GetRotation(q);

  q = rotation;
  r.Multiply(q);

  rotation = r;
}


void RigidBodyDynamicCylinder::SetRadius(float radius)
{
  CHECK_GEOM_IS_INITIALISED;

  float length;
  GetLength(length);

  dGeomCylinderSetParams(m_GeomId, radius, length);
}


void RigidBodyDynamicCylinder::SetLength(float length)
{
  CHECK_GEOM_IS_INITIALISED;

  float radius;
  GetRadius(radius);

  dGeomCylinderSetParams(m_GeomId, radius, length);
}


void RigidBodyDynamicCylinder::GetRadius(float &radius) const
{
  CHECK_GEOM_IS_INITIALISED;

  float length;
  dGeomCylinderGetParams(m_GeomId, &radius, &length);
}


void RigidBodyDynamicCylinder::GetLength(float &length) const
{
  CHECK_GEOM_IS_INITIALISED;

  float radius;
  dGeomCylinderGetParams(m_GeomId, &radius, &length);
}


void RigidBodyDynamicCylinder::SetMassFromDensity(float density)
{
  CHECK_BODY_IS_INITIALISED;
  CHECK_GEOM_IS_INITIALISED;

  float radius, length;
  dGeomCylinderGetParams(m_GeomId, &radius, &length);

  // Direction of the cylinder
  // 1 is x-axis, 2 is y-axis, 3 is z-axis
  // Setting this to z-axis because the geom defaults to z-axis
  int direction = 3;

  dMass m;
  dMassSetCylinder(&m, density, direction, radius, length);
  dBodySetMass(m_BodyId, &m);
}


void RigidBodyDynamicCylinder::SetMass(float mass)
{
  CHECK_BODY_IS_INITIALISED;
  CHECK_GEOM_IS_INITIALISED;

  float radius, length;
  dGeomCylinderGetParams(m_GeomId, &radius, &length);

  // Direction of the cylinder
  // 1 is x-axis, 2 is y-axis, 3 is z-axis
  // Setting this to z-axis because the geom defaults to z-axis
  int direction = 3;

  dMass m;
  dMassSetCylinderTotal(&m, mass, direction, radius, length);
  dBodySetMass(m_BodyId, &m);
}


void RigidBodyDynamicCylinder::Render()
{
  float radius, length;
  GetRadius(radius);
  GetLength(length);

  Matrix m;
  RigidBodyDynamic::GetMatrix(m);

  DEBUG_CYLINDER(m, Cylinder(radius, length), Color::Green, 1);
}


// ============================================================================
// CAPPED CYLINDER
// ============================================================================


RigidBodyDynamicCappedCylinder::RigidBodyDynamicCappedCylinder()
: RigidBodyDynamicCylinder()
{
}


RigidBodyDynamicCappedCylinder::~RigidBodyDynamicCappedCylinder()
{
}


bool RigidBodyDynamicCappedCylinder::Init(float radius, float length)
{
  m_GeomId = dCreateCCylinder(Physics.GetSpace(PhysicsManager::Actor), radius, length);
  m_BodyId = dBodyCreate(Physics.GetWorld());

  CHECK_GEOM_IS_INITIALISED_RETURN_FALSE;
  CHECK_BODY_IS_INITIALISED_RETURN_FALSE;
    
  dGeomSetBody(m_GeomId, m_BodyId);
  SetMassFromDensity(1.0f);

  SetCategoryMask(PhysicsManager::CAT_DYNAMIC);
  SetCollisionMask(PhysicsManager::CAT_ALL);

  return true;
}


void RigidBodyDynamicCappedCylinder::SetRadius(float radius)
{
  CHECK_GEOM_IS_INITIALISED;

  float length;
  GetLength(length);

  dGeomCCylinderSetParams(m_GeomId, radius, length);
}


void RigidBodyDynamicCappedCylinder::SetLength(float length)
{
  CHECK_GEOM_IS_INITIALISED;

  float radius;
  GetRadius(radius);

  dGeomCCylinderSetParams(m_GeomId, radius, length);
}


void RigidBodyDynamicCappedCylinder::GetRadius(float &radius) const
{
  CHECK_GEOM_IS_INITIALISED;

  float length;
  dGeomCCylinderGetParams(m_GeomId, &radius, &length);
}


void RigidBodyDynamicCappedCylinder::GetLength(float &length) const
{
  CHECK_GEOM_IS_INITIALISED;

  float radius;
  dGeomCCylinderGetParams(m_GeomId, &radius, &length);
}


void RigidBodyDynamicCappedCylinder::SetMassFromDensity(float density)
{
  CHECK_BODY_IS_INITIALISED;
  CHECK_GEOM_IS_INITIALISED;

  float radius, length;
  dGeomCCylinderGetParams(m_GeomId, &radius, &length);

  // Direction of the cylinder
  // 1 is x-axis, 2 is y-axis, 3 is z-axis
  // Setting this to z-axis because the geom defaults to z-axis
  int direction = 3;

  dMass m;
  dMassSetCappedCylinder(&m, density, direction, radius, length);
  dBodySetMass(m_BodyId, &m);
}


void RigidBodyDynamicCappedCylinder::SetMass(float mass)
{
  CHECK_BODY_IS_INITIALISED;
  CHECK_GEOM_IS_INITIALISED;

  float radius, length;
  dGeomCCylinderGetParams(m_GeomId, &radius, &length);

  // Direction of the cylinder
  // 1 is x-axis, 2 is y-axis, 3 is z-axis
  // Setting this to z-axis because the geom defaults to z-axis
  int direction = 3;

  dMass m;
  dMassSetCappedCylinderTotal(&m, mass, direction, radius, length);
  dBodySetMass(m_BodyId, &m);
}


void RigidBodyDynamicCappedCylinder::Render()
{
  // TODO
}


// ============================================================================
// MESH
// ============================================================================


RigidBodyDynamicIndexedMesh::RigidBodyDynamicIndexedMesh()
: RigidBodyDynamic(),
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


RigidBodyDynamicIndexedMesh::~RigidBodyDynamicIndexedMesh()
{
  // TODO -> cleanup
}


bool RigidBodyDynamicIndexedMesh::Init(const RigidBody::InitData *pInitData)
{
  ASSERT(pInitData->Type == RigidBody::RB_MESH, "Invalid Type");

  RigidBodyDynamicIndexedMesh::IndexedMeshInitData *pMeshInitData = (RigidBodyDynamicIndexedMesh::IndexedMeshInitData *) pInitData;

  return Init(pMeshInitData->pMesh);
}


bool RigidBodyDynamicIndexedMesh::Init(IndexedMesh *pMesh)
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


bool RigidBodyDynamicIndexedMesh::Create(const void *pVertices, int vertexStride, int vertexCount, 
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
  m_GeomId = dCreateTriMesh(Physics.GetSpace(PhysicsManager::Actor), triMeshId, NULL, NULL, NULL);
  m_BodyId = dBodyCreate(Physics.GetWorld());

  CHECK_GEOM_IS_INITIALISED_RETURN_FALSE;
  CHECK_BODY_IS_INITIALISED_RETURN_FALSE;
    
  dGeomSetBody(m_GeomId, m_BodyId);
  SetMassFromDensity(1.0f);

  SetCategoryMask(PhysicsManager::CAT_DYNAMIC);
  SetCollisionMask(PhysicsManager::CAT_ALL);

  return true;
}


void RigidBodyDynamicIndexedMesh::SetMassFromDensity(float density)
{
  CHECK_BODY_IS_INITIALISED;
  CHECK_GEOM_IS_INITIALISED;

  dMass m;
  dMassSetZero(&m);
  dMassSetTrimesh(&m, density, m_GeomId);

  // Reset the mass center point
  m.c[0] = 0.0f;
  m.c[1] = 0.0f;
  m.c[2] = 0.0f;
  m.c[3] = 0.0f;

  dBodySetMass(m_BodyId, &m);
}


void RigidBodyDynamicIndexedMesh::SetMass(float mass)
{
  CHECK_BODY_IS_INITIALISED;
  CHECK_GEOM_IS_INITIALISED;

  dMass m;
  dMassSetZero(&m);
  dMassSetTrimeshTotal(&m, mass, m_GeomId);

  // Reset the mass center point
  m.c[0] = 0.0f;
  m.c[1] = 0.0f;
  m.c[2] = 0.0f;
  m.c[3] = 0.0f;

  dBodySetMass(m_BodyId, &m);
}


void RigidBodyDynamicIndexedMesh::Render()
{
  Matrix m;
  GetMatrix(m);
  DEBUG_MESH(m, m_pDebugRenderVertexData, m_NumVertex, m_pDebugRenderIndexData, m_NumIndex, Color::Green, 1);
}


// -- EOF

