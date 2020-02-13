
#ifndef __RIGID_BODY_STATIC_H_
#define __RIGID_BODY_STATIC_H_


#include "libODE.h"
#include "RigidBody.h"
#include "RigidBodyTypes.h"


class RigidBodyStatic : public RigidBody
{
public:
  RigidBodyStatic();
  virtual ~RigidBodyStatic();

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

  virtual void Render() = 0;

protected:
  dGeomID   m_GeomId;

};


class RigidBodyStaticSphere : public RigidBodyStatic, public RigidBodySphere
{
public:
  RigidBodyStaticSphere();
  virtual ~RigidBodyStaticSphere();

  virtual bool Init(const RigidBody::InitData *pInitData);
  virtual bool Init(float radius);

  virtual void SetRadius(float radius);
  virtual void GetRadius(float &radius) const;

  virtual void Render();

protected:

};


class RigidBodyStaticBox : public RigidBodyStatic, public RigidBodyBox
{
public:
  RigidBodyStaticBox();
  virtual ~RigidBodyStaticBox();

  virtual bool Init(const RigidBody::InitData *pInitData);
  virtual bool Init(const Vec3 &extents);

  virtual void SetExtents(const Vec3 &extents);
  virtual void GetExtents(Vec3 &extents) const;

  virtual void Render();

protected:

};


class RigidBodyStaticCylinder : public RigidBodyStatic, public RigidBodyCylinder
{
public:
  RigidBodyStaticCylinder();
  virtual ~RigidBodyStaticCylinder();

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

  virtual void Render();

protected:

};


class RigidBodyStaticCappedCylinder : public RigidBodyStaticCylinder
{
public:
  RigidBodyStaticCappedCylinder();
  virtual ~RigidBodyStaticCappedCylinder();

  virtual bool Init(float radius, float length);

  virtual void SetRadius(float radius);
  virtual void SetLength(float length);
  virtual void GetRadius(float &radius) const;
  virtual void GetLength(float &length) const;

  virtual void Render();

protected:

};


class RigidBodyStaticIndexedMesh : public RigidBodyStatic, public RigidBodyIndexedMesh
{
public:
  RigidBodyStaticIndexedMesh();
  virtual ~RigidBodyStaticIndexedMesh();

  virtual bool Init(const RigidBody::InitData *pInitData);
  virtual bool Init(IndexedMesh *pMesh);

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





#endif // __RIGID_BODY_STATIC_H_

// -- EOF

