
#ifndef __RIGID_BODY_DYNAMIC_H_
#define __RIGID_BODY_DYNAMIC_H_


#include "libODE.h"
#include "RigidBody.h"
#include "RigidBodyTypes.h"


class RigidBodyDynamic : public RigidBody
{
public:
  RigidBodyDynamic();
  virtual ~RigidBodyDynamic();

  virtual bool Init(const InitData *pInitData) = 0;

  virtual void SetEnabled(bool enable);

  virtual void SetPosition(const Vec3 &position);
  virtual void GetPosition(Vec3 &position) const;

  virtual void SetRotation(const Quat &rotation);
  virtual void GetRotation(Quat &rotation) const;

  virtual void SetMatrix(const Matrix &matrix);
  virtual void GetMatrix(Matrix &matrix) const;

  virtual void SetCollisionMask(ulong mask);
  virtual ulong GetCollisionMask() const;

  virtual void SetCategoryMask(ulong mask);
  virtual ulong GetCategoryMask() const;

  void SetLinearVelocity(const Vec3 &velocity);
  void SetAngularVelocity(const Vec3 &velocity);

  void GetLinearVelocity(Vec3 &velocity) const;
  void GetAngularVelocity(Vec3 &velocity) const;

  void AddForce(const Vec3 &forceVec);
  void AddLocalForce(const Vec3 &forceVec);
  void AddForceAtPosition(const Vec3 &force, const Vec3 &position);
  void AddForceAtLocalPosition(const Vec3 &force, const Vec3 &position);
  void AddLocalForceAtPos(const Vec3 &force, const Vec3 &position);
  void AddLocalForceAtLocalPos(const Vec3 &force, const Vec3 &position);

  void AddTorque(const Vec3 &torqueVec);
  void AddLocalTorque(const Vec3 &torqueVec);

  void SetForce(const Vec3 &forceVec);
  void SetTorque(const Vec3 &torqueVec);

  void GetForce(Vec3 &forceVec) const;
  void GetTorque(Vec3 &torqueVec) const;

  void ConvertLocalPositonToWorldPosition(const Vec3 &localPosition, Vec3 &worldPosition) const;
  void ConvertWorldPositonToLocalPosition(const Vec3 &worldPosition, Vec3 &localPosition) const;

  void ConvertLocalVectorToWorldVector(const Vec3 &localVector, Vec3 &worldVector) const;
  void ConvertWorldVectorToLocalVector(const Vec3 &worldVector, Vec3 &localVector) const;

  void GetVelocityAtLocalPosition(const Vec3 &position, Vec3 &velocity) const;
  void GetVelocityAtPosition(const Vec3 &position, Vec3 &velocity) const;

  void SetAutoDisableUseWorldDefaults();
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

  void SetGravityEnabled(bool enabled);
  bool IsGravityEnabled() const;

  void GetAABB(Box &aabb);

  virtual void SetMassFromDensity(float density) = 0;
  virtual void SetMass(float mass) = 0;
  virtual void Render() = 0;

protected:
  dBodyID   m_BodyId;
  dGeomID   m_GeomId;

};


class RigidBodyDynamicSphere : public RigidBodyDynamic, public RigidBodySphere
{
public:
  RigidBodyDynamicSphere();
  virtual ~RigidBodyDynamicSphere();

  virtual bool Init(const RigidBody::InitData *pInitData);
  virtual bool Init(float radius);

  virtual void SetRadius(float radius);
  virtual void GetRadius(float &radius) const;

  virtual void SetMassFromDensity(float density);
  virtual void SetMass(float mass);

  virtual void Render();

protected:

};


class RigidBodyDynamicBox : public RigidBodyDynamic, public RigidBodyBox
{
public:
  RigidBodyDynamicBox();
  virtual ~RigidBodyDynamicBox();

  virtual bool Init(const RigidBody::InitData *pInitData);
  virtual bool Init(const Vec3 &extents);

  virtual void SetExtents(const Vec3 &extents);
  virtual void GetExtents(Vec3 &extents) const;

  virtual void SetMassFromDensity(float density);
  virtual void SetMass(float mass);

  virtual void Render();

protected:

};


class RigidBodyDynamicCylinder : public RigidBodyDynamic, public RigidBodyCylinder
{
public:
  RigidBodyDynamicCylinder();
  virtual ~RigidBodyDynamicCylinder();

  virtual bool Init(const RigidBody::InitData *pInitData);
  virtual bool Init(float radius, float length);

  virtual void SetMatrix(const Matrix &matrix);
  virtual void GetMatrix(Matrix &matrix) const;

  virtual void SetRotation(const Quat &rotation);
  virtual void GetRotation(Quat &rotation) const;

  virtual void SetRadius(float radius);
  virtual void SetLength(float length);
  virtual void GetRadius(float &radius) const;
  virtual void GetLength(float &length) const;

  virtual void SetMassFromDensity(float density);
  virtual void SetMass(float mass);

  virtual void Render();

protected:

};


class RigidBodyDynamicCappedCylinder : public RigidBodyDynamicCylinder
{
public:
  RigidBodyDynamicCappedCylinder();
  virtual ~RigidBodyDynamicCappedCylinder();

  virtual bool Init(float radius, float length);

  virtual void SetRadius(float radius);
  virtual void SetLength(float length);
  virtual void GetRadius(float &radius) const;
  virtual void GetLength(float &length) const;

  virtual void SetMassFromDensity(float density);
  virtual void SetMass(float mass);

  virtual void Render();

protected:

};


class RigidBodyDynamicIndexedMesh : public RigidBodyDynamic, public RigidBodyIndexedMesh
{
public:
  RigidBodyDynamicIndexedMesh();
  virtual ~RigidBodyDynamicIndexedMesh();

  virtual bool Init(const RigidBody::InitData *pInitData);
  virtual bool Init(IndexedMesh *pMesh);

  virtual void SetMassFromDensity(float density);
  virtual void SetMass(float mass);

  virtual void Render();

protected:
  bool Create(const void *pVertices, int vertexStride, int vertexCount, 
              const void *pIndices,  int indexStride,  int indexCount,
              const void *pNormals,  int normalStride);

  uint     m_NumVertex;
  uint     m_NumIndex;
  Vec3    *m_pPositionData;
  Vec3    *m_pNormalData;
  int     *m_pIndexData;
  VT_PN   *m_pDebugRenderVertexData;
  ushort  *m_pDebugRenderIndexData;

};





#endif // __RIGID_BODY_DYNAMIC_H_

// -- EOF

