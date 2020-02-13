
#include "PhysicsManager.h"
#include "RigidBodyTypes.h"
#include "RigidBody.h"


PhysicsManager *PhysicsManager::s_pInstance = NULL;


PhysicsManager &PhysicsManager::GetInstance()
{
  if (!s_pInstance)
  {
    s_pInstance = new PhysicsManager();
    atexit(&PhysicsManager::DestroyInstance);
  }

  return *s_pInstance;
}


void PhysicsManager::DestroyInstance()
{
  delete s_pInstance;
  s_pInstance = NULL;
}


PhysicsManager::PhysicsManager()
{
  m_WorldId             = 0;
  m_ActorSpaceId        = 0;
  m_StaticSpaceId       = 0;
  m_CollisionJointGroup = 0;
}


PhysicsManager::~PhysicsManager()
{
  // TODO
}


bool PhysicsManager::Init()
{
  dInitODE();

  // Create the dynamics world
  m_WorldId = dWorldCreate();
  if (m_WorldId == 0)
    return false;

  // Set the world defaults
  dWorldSetERP(m_WorldId, 0.3f);
  dWorldSetCFM(m_WorldId, 1e-5f);
  dWorldSetGravity(m_WorldId, 0.0f, -29.81f, 0.0f);

  // Create the actor space
  m_ActorSpaceId = dHashSpaceCreate(0);
  NULL_ASSERT(m_ActorSpaceId);
  dHashSpaceSetLevels(m_ActorSpaceId, 2, 7);

  // Create the static space
  m_StaticSpaceId = dHashSpaceCreate(0);
  NULL_ASSERT(m_StaticSpaceId);
  dHashSpaceSetLevels(m_StaticSpaceId, 2, 7);

  // Create the collision contact joint group
  m_CollisionJointGroup = dJointGroupCreate(0);
  if (m_CollisionJointGroup == 0)
    return false;
  
  return true;
}


bool PhysicsManager::Shutdown()
{
  for (uint i = 0; i < m_Planes.size(); i++)
  {
    dGeomDestroy(m_Planes[i]);
  }

  dWorldDestroy(m_WorldId);
  dSpaceDestroy(m_ActorSpaceId);
  dSpaceDestroy(m_StaticSpaceId);

  dJointGroupDestroy(m_CollisionJointGroup);

  dCloseODE();

  return true;
}


void PhysicsManager::Update(float deltaTime)
{
  ASSERT(m_ActorSpaceId && m_StaticSpaceId && m_WorldId, "Physics Manager is not initialised");

  void *pCollisionGroupId = &m_CollisionJointGroup;

  dSpaceCollide(m_ActorSpaceId, pCollisionGroupId, NearCallbackActors);
  dSpaceCollide2((dGeomID)m_ActorSpaceId, (dGeomID)m_StaticSpaceId, pCollisionGroupId, NearCallbackStatics);

  dWorldQuickStep(m_WorldId, deltaTime);
  //dWorldStep(m_WorldId, deltaTime);
  dJointGroupEmpty(m_CollisionJointGroup);
}


void PhysicsManager::Register(RigidBody *pRigidBody)
{
  m_RigidBodies.insert(pRigidBody);
}


void PhysicsManager::UnRegister(RigidBody *pRigidBody)
{
  SortedSet<RigidBody *>::iterator iter = m_RigidBodies.find(pRigidBody);
  if (iter != m_RigidBodies.end())
  {
    m_RigidBodies.erase(iter);
  }
}


void PhysicsManager::Render()
{
  SortedSet<RigidBody *>::iterator iter(m_RigidBodies.begin()), end(m_RigidBodies.end());
  for (; iter != end; ++iter)
  {
    (*iter)->Render();
  }
}


void PhysicsManager::SetGravity(const Vec3 &gravity)
{
  ASSERT(m_WorldId, "Physics Manager is not initialised")
  dWorldSetGravity(m_WorldId, gravity.x, gravity.y, gravity.z);
}


void PhysicsManager::AddPlane(const Plane &plane)
{
  //ASSERT(m_StaticSpaceId, "Physics Manager is not initialised")
  //dGeomID planeId = dCreatePlane(m_StaticSpaceId, plane.a, plane.b, plane.c, plane.d);
  //m_Planes.push_back(planeId);

  ASSERT(m_ActorSpaceId, "Physics Manager is not initialised")
  dGeomID planeId = dCreatePlane(m_ActorSpaceId, plane.a, plane.b, plane.c, plane.d);
  m_Planes.push_back(planeId);

  dGeomSetCategoryBits(planeId, PhysicsManager::CAT_NONE);
  dGeomSetCollideBits(planeId,  PhysicsManager::CAT_DYNAMIC);
}

void PhysicsManager::NearCallbackActors(void *pData, dGeomID o1, dGeomID o2)
{
  if (!(o1 && o2))
  {
    ASSERT(o1 && o2, "CollisionCallback with null geometry");
    return;
  }

	// Ignore collisions between bodies that are connected by the same joint
	dBodyID Body1 = NULL, Body2 = NULL;

	if (o1) Body1 = dGeomGetBody (o1);
	if (o2) Body2 = dGeomGetBody (o2);

	if (Body1 && Body2 && dAreConnected (Body1, Body2))
		return;

	const int iContacts = 50; // ODE_MAX_CONTACTS?
	dContact contact[iContacts];

	int iCount = dCollide (o1, o2, iContacts, &contact[0].geom, sizeof (dContact));

	if (iCount)
	{
		int iMax = min (iCount, iContacts);
		for (int iContact = 0; iContact < iMax; iContact++)
		{
			contact[iContact].surface.mode        = dContactBounce; 
			contact[iContact].surface.mu          = 10.0f; // m_pApplication->m_Preferences.m_rGroundFriction;
			contact[iContact].surface.bounce      = 0.0f;  // m_pApplication->m_Preferences.m_rGroundBounce;
			contact[iContact].surface.bounce_vel  = 0.0f;
			contact[iContact].surface.slip1       = 0.1f;
			contact[iContact].surface.slip2       = 0.1f;
			contact[iContact].surface.soft_erp    = 0.5f; // 0.5;
			contact[iContact].surface.soft_cfm    = 0.3f; // 0.3;

      dJointGroupID collisionGroupId = *((dJointGroupID*)pData);
			dJointID ContactJoint = dJointCreateContact(Physics.GetWorld(), collisionGroupId, &contact[iContact]);
			dJointAttach(ContactJoint, Body1, Body2);
		}
	}
}


void PhysicsManager::NearCallbackStatics(void *pData, dGeomID o1, dGeomID o2)
{
  if (!(o1 && o2))
  {
    ASSERT(o1 && o2, "CollisionCallback with null geometry");
    return;
  }

	// Ignore collisions between bodies that are connected by the same joint
	dBodyID Body1 = NULL, Body2 = NULL;

	if (o1) Body1 = dGeomGetBody (o1);
	if (o2) Body2 = dGeomGetBody (o2);

	if (Body1 && Body2 && dAreConnected (Body1, Body2))
		return;

	const int iContacts = 50; // ODE_MAX_CONTACTS?
	dContact contact[iContacts];

	int iCount = dCollide (o1, o2, iContacts, &contact[0].geom, sizeof (dContact));

	if (iCount)
	{
		int iMax = min (iCount, iContacts);
		for (int iContact = 0; iContact < iMax; iContact++)
		{
			contact[iContact].surface.mode        = dContactBounce; 
			contact[iContact].surface.mu          = 10.0f; // m_pApplication->m_Preferences.m_rGroundFriction;
			contact[iContact].surface.bounce      = 0.0f;  // m_pApplication->m_Preferences.m_rGroundBounce;
			contact[iContact].surface.bounce_vel  = 0.0f;
			contact[iContact].surface.slip1       = 0.1f;
			contact[iContact].surface.slip2       = 0.1f;
			contact[iContact].surface.soft_erp    = 0.5f; // 0.5;
			contact[iContact].surface.soft_cfm    = 0.3f; // 0.3;

      dJointGroupID collisionGroupId = *((dJointGroupID*)pData);
			dJointID ContactJoint = dJointCreateContact(Physics.GetWorld(), collisionGroupId, &contact[iContact]);
			dJointAttach(ContactJoint, Body1, Body2);
		}
	}
}


// Cast a ray, return true if it hits anything
bool PhysicsManager::CastRay(const PhysicsManager::Ray &ray)
{
  ASSERT(m_ActorSpaceId && m_StaticSpaceId && m_WorldId, "Physics Manager is not initialised");

  dGeomID rayId = dCreateRay(m_StaticSpaceId, ray.Length);

  dGeomSetCategoryBits(rayId, PhysicsManager::CAT_RAYCAST);
  dGeomSetCollideBits(rayId, PhysicsManager::CAT_RAYCAST);

  dGeomRaySet(rayId, ray.Position.x, ray.Position.y, ray.Position.z, ray.Direction.x, ray.Direction.y, ray.Direction.z);
  dGeomRaySetClosestHit(rayId, 1);
  dGeomRaySetParams(rayId, 0, 1);

	const int iContacts = 50; // ODE_MAX_CONTACTS?
	dContact contact[iContacts];

  if (dCollide(rayId, (dGeomID) m_StaticSpaceId, 50, &contact[0].geom, sizeof(dContact)) > 0)
  {
    dGeomDestroy(rayId);
    return true;
  }

  if (dCollide(rayId, (dGeomID)m_ActorSpaceId,  50, &contact[0].geom, sizeof(dContact)) > 0)
  {
    dGeomDestroy(rayId);
    return true;
  }

  dGeomDestroy(rayId);
  return false;
}


// Cast a ray and get the closest hit
bool PhysicsManager::CastRay(const PhysicsManager::Ray &ray, RayHit &result, uint flags)
{
  bool hasHit = false;
  float hitDistanceSq = 0.0f;

  ASSERT(m_ActorSpaceId && m_StaticSpaceId && m_WorldId, "Physics Manager is not initialised");

  dGeomID rayId = dCreateRay(m_StaticSpaceId, ray.Length);
  dGeomSetCategoryBits(rayId, PhysicsManager::CAT_RAYCAST);
  dGeomSetCollideBits(rayId, PhysicsManager::CAT_RAYCAST);

  dGeomRaySet(rayId, ray.Position.x, ray.Position.y, ray.Position.z, ray.Direction.x, ray.Direction.y, ray.Direction.z);
  dGeomRaySetClosestHit(rayId, 1);
  dGeomRaySetParams(rayId, 0, 1);

	const int iContacts = 50; // ODE_MAX_CONTACTS?
	dContact contact[iContacts];

  for (uint i = 0; i < 2; i++)
  {
    if (i == 0 && (flags & PhysicsManager::COLLIDE_STATIC_GEOM) ||
        i == 1 && (flags & PhysicsManager::COLLIDE_DYNAMIC_GEOM))
    {
      dGeomID spaceToTest = (dGeomID) (i == 0 ? m_StaticSpaceId : m_ActorSpaceId);

      int count = dCollide(rayId, spaceToTest, 50, &contact[0].geom, sizeof(dContact));
      if (count)
      {
        for (int hit = 0; hit < count; hit++)
        {
          dContactGeom &contactGeom = contact[hit].geom;

          RayHit hitPos;

          hitPos.Position.Set(contactGeom.pos[0], contactGeom.pos[1], contactGeom.pos[2]);
          hitPos.Normal.Set(contactGeom.normal[0], contactGeom.normal[1], contactGeom.normal[2]);

          float distanceSq = Vec3(ray.Position - hitPos.Position).LengthSq();

          if (!hasHit || distanceSq < hitDistanceSq)
          {
            hasHit = true;
            hitDistanceSq = distanceSq;
            
            result = hitPos;
            result.Distance = sqrtf(hitDistanceSq);
          }
        }       
      }
    }
  }

  dGeomDestroy(rayId);
  return hasHit;
}


// Test if the volume is penetrating
bool PhysicsManager::IsBoxPenetrating(const Vec3 &extents, const Matrix &matrix, uint flags)
{
  dGeomID geomId = dCreateBox(0, extents.x, extents.y, extents.z);
  return IsPenetrating(geomId, matrix, flags);
}


// Test if the volume is penetrating
bool PhysicsManager::IsSpherePenetrating(float radius, const Matrix &matrix, uint flags)
{
  dGeomID geomId = dCreateSphere(0, radius);
  return IsPenetrating(geomId, matrix, flags);
}


// Test if the volume is penetrating
bool PhysicsManager::IsCylinderPenetrating(float radius, float length, const Matrix &matrix, uint flags)
{
  dGeomID geomId = dCreateCylinder(0, radius, length);
  return IsPenetrating(geomId, matrix, flags);
}


// Test if the volume is penetrating
bool PhysicsManager::IsCappedCylinderPenetrating(float radius, float length, const Matrix &matrix, uint flags)
{
  dGeomID geomId = dCreateCCylinder(0, radius, length);
  return IsPenetrating(geomId, matrix, flags);
}


// Test if the volume is penetrating
bool PhysicsManager::IsPenetrating(dGeomID geomId, const Matrix &matrix, uint flags)
{
  ASSERT(m_ActorSpaceId && m_StaticSpaceId && m_WorldId, "Physics Manager is not initialised");

  dGeomSetCategoryBits(geomId, PhysicsManager::CAT_NONE);
  dGeomSetCollideBits(geomId, PhysicsManager::CAT_STATIC | PhysicsManager::CAT_DYNAMIC);

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

  dGeomSetPosition(geomId, tAxis.x, tAxis.y, tAxis.z);
  dGeomSetRotation(geomId, m);

	const int iContacts = 50; // ODE_MAX_CONTACTS?
	dContact contact[iContacts];

  for (uint i = 0; i < 2; i++)
  {
    if (i == 0 && (flags & PhysicsManager::COLLIDE_STATIC_GEOM) ||
        i == 1 && (flags & PhysicsManager::COLLIDE_DYNAMIC_GEOM))
    {
      dGeomID spaceToTest = (dGeomID) (i == 0 ? m_StaticSpaceId : m_ActorSpaceId);

      if (dCollide(geomId, spaceToTest, 50, &contact[0].geom, sizeof(dContact)))
      {
        dGeomDestroy(geomId);
        return true;
      }
    }
  }

  dGeomDestroy(geomId);
  return false;
}



// -- EOF

