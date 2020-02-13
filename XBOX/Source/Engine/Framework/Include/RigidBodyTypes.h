
#ifndef __RIGID_BODY_TYPES_H_
#define __RIGID_BODY_TYPES_H_


#include "RigidBody.h"


class RigidBodySphere
{
public:
  struct SphereInitData : public RigidBody::InitData
  {
    SphereInitData() 
    {
      Type    = RigidBody::RB_SPHERE; 
      Radius  = 0.0f;
    }

    float Radius;
  };

  virtual bool Init(float radius) = 0;
  virtual void SetRadius(float radius)  = 0;
  virtual void GetRadius(float &radius) const = 0;

};


class RigidBodyBox
{
public:
  struct BoxInitData : public RigidBody::InitData
  {
    BoxInitData() 
    {
      Type    = RigidBody::RB_BOX; 
      Extents = Vec3(0.0f, 0.0f, 0.0f);
    }

    Vec3 Extents;
  };

  virtual bool Init(const Vec3 &extents) = 0;
  virtual void SetExtents(const Vec3 &extents) = 0;
  virtual void GetExtents(Vec3 &extents) const = 0;

};


class RigidBodyCylinder
{
public:
  struct CylinderInitData : public RigidBody::InitData
  {
    CylinderInitData() 
    {
      Type    = RigidBody::RB_CYLINDER; 
      Radius  = 0.0f;
      Length  = 0.0f;
    }

    float Radius;
    float Length;
  };

  virtual void SetCylinderOrientationMatrix(const Matrix &matrix)
  {
    m_OrientationMatrix        = matrix;
    m_OrientationMatrixInverse = matrix;

    m_OrientationMatrixInverse.Inverse(matrix);
  }

  virtual void GetCylinderOrientationMatrix(Matrix &matrix) const
  {
    matrix = m_OrientationMatrix;
  }

  virtual void GetCylinderOrientationMatrixInverse(Matrix &matrix) const
  {
    matrix = m_OrientationMatrixInverse;
  }

  virtual bool Init(float radius, float length) = 0;
  virtual void SetRadius(float radius)   = 0;
  virtual void SetLength(float length)   = 0;
  virtual void GetRadius(float &radius) const = 0;
  virtual void GetLength(float &length) const = 0;

protected:
  Matrix m_OrientationMatrix;
  Matrix m_OrientationMatrixInverse;

};


class RigidBodyIndexedMesh
{
public:
  struct IndexedMeshInitData : public RigidBody::InitData
  {
    IndexedMeshInitData() 
    {
      Type    = RigidBody::RB_MESH;
      pMesh   = NULL;
    }

    IndexedMesh *pMesh;

  };

  virtual bool Init(IndexedMesh *pMesh) = 0;

};




#endif // __RIGID_BODY_TYPES_H_


// -- EOF

