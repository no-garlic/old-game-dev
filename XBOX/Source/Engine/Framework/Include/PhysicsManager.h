
#ifndef __PHYSICS_MANAGER_H_
#define __PHYSICS_MANAGER_H_


#include "libODE.h"


class RigidBody;


#define Physics PhysicsManager::GetInstance()


class PhysicsManager : private Unique
{
public:
  static PhysicsManager &GetInstance();
  static void DestroyInstance();

  bool Init();  // flags for space type (simple, hash, quadtree, etc
  bool Shutdown();

  void Update(float deltaTime);

  void SetERP(float erp);
  void GetERP(float &erp) const;

  void SetCFM(float cfm);
  void GetCFM(float &cfm) const;

  void SetContactMaxCorrectingVelocity(const Vec3 &velocity);
  void GetContactMaxCorrectingVelocity(Vec3 &velocity) const;

  void SetContactSurfaceDepth(const float &depth);
  void GetContactSurfaceDepth(float &depth) const;

  void SetGravity(const Vec3 &gravity);

  void SetAutoDisableUseDefaults();
  void SetAutoDisableEnabled(bool enable);
  bool IsAutoDisableEnabled() const;

  void SetAutoDisableLinearThreashold(float threashold);
  void GetAutoDisableLinearThreashold(float &threashold) const;

  void SetAutoDisableAngularThreashold(float threashold);
  void GetAutoDisableAngularThreashold(float &threashold) const;

  void SetAutoDisableStepCount(int numSteps);
  void GetAutoDisableStepCount(int &numSteps) const;

  void SetAutoDisableTime(float seconds);
  void GetAutoDisableTime(float &seconds) const;

  void AddPlane(const Plane &plane);

  static void NearCallbackActors(void *pData, dGeomID o1, dGeomID o2);
  static void NearCallbackStatics(void *pData, dGeomID o1, dGeomID o2);

  inline dWorldID GetWorld() const { return m_WorldId; }

  enum SpaceId { Static, Actor };

  enum CategoryId
  {
    CAT_NONE      = (0x00000000),
    
    CAT_DYNAMIC   = (1<<0),
    CAT_STATIC    = (1<<1),
    CAT_RAYCAST   = (1<<2),

    CAT_ALL       = (0xffffffff)
  };

  inline dSpaceID GetSpace(SpaceId id) const
  {
    if (id == PhysicsManager::Static)
      return m_StaticSpaceId;
    else
      return m_ActorSpaceId;
  }

  struct Ray
  {
    Vec3  Position;
    Vec3  Direction;
    float Length;
  };

  struct RayHit
  {
    Vec3  Position;
    Vec3  Normal;
    float Distance;
  };

  enum CollideFlags
  {
    COLLIDE_STATIC_GEOM   = (1<<0),
    COLLIDE_DYNAMIC_GEOM  = (1<<1),

    COLLIDE_DEFAULT_FLAGS         = COLLIDE_STATIC_GEOM | COLLIDE_DYNAMIC_GEOM
  };

  // Cast a ray, return true if it hits anything
  bool CastRay(const PhysicsManager::Ray &ray);

  // Cast a ray and get the closest hit
  bool CastRay(const PhysicsManager::Ray &ray, RayHit &result, uint flags = COLLIDE_DEFAULT_FLAGS);

  // Test if the volume is penetrating
  bool IsBoxPenetrating(const Vec3 &extents, const Matrix &matrix, uint flags = COLLIDE_DEFAULT_FLAGS);
  bool IsSpherePenetrating(float radius, const Matrix &matrix, uint flags = COLLIDE_DEFAULT_FLAGS);
  bool IsCylinderPenetrating(float radius, float length, const Matrix &matrix, uint flags = COLLIDE_DEFAULT_FLAGS);
  bool IsCappedCylinderPenetrating(float radius, float length, const Matrix &matrix, uint flags = COLLIDE_DEFAULT_FLAGS);

  void Register(RigidBody *pRigidBody);
  void UnRegister(RigidBody *pRigidBody);

  void Render();

private:
  PhysicsManager();
  ~PhysicsManager();

  // Test if the volume is penetrating
  bool IsPenetrating(dGeomID geomId, const Matrix &matrix, uint flags);

private:
  static PhysicsManager   *s_pInstance;   // The singleton instance

  dWorldID                  m_WorldId;              // The world (for simulation)
  dSpaceID                  m_ActorSpaceId;         // The actor space (objects that move)
  dSpaceID                  m_StaticSpaceId;        // The static space (objects that dont move)
  Array<dGeomID>            m_Planes;               // World bounds planes
  dJointGroupID             m_CollisionJointGroup;  // Group of collision joints
  SortedSet<RigidBody *>    m_RigidBodies;          // All bodies 

};


#endif // __PHYSICS_MANAGER_H_

// -- EOF

