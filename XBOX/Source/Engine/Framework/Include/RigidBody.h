
#ifndef __RIGID_BODY_H_
#define __RIGID_BODY_H_


#include "libODE.h"


class RigidBody : private Unique
{
public:
  RigidBody();
  virtual ~RigidBody();

  enum RigidBodyType
  {
    RB_SPHERE,
    RB_BOX,
    RB_CYLINDER,
    RB_MESH
  };

  struct InitData {int Type; };
  virtual bool Init(const InitData *pInitData) = 0;

  virtual void SetEnabled(bool enable) = 0;
  virtual bool IsEnabled() const;

  virtual bool IsStatic() const;

  virtual void SetPosition(const Vec3 &position) = 0;
  virtual void GetPosition(Vec3 &position) const = 0;

  virtual void SetRotation(const Quat &rotation) = 0;
  virtual void GetRotation(Quat &rotation) const = 0;

  virtual void SetMatrix(const Matrix &matrix) = 0;
  virtual void GetMatrix(Matrix &matrix) const = 0;

  virtual void SetCollisionMask(ulong mask) = 0;
  virtual ulong GetCollisionMask() const = 0;

  virtual void SetCategoryMask(ulong mask) = 0;
  virtual ulong GetCategoryMask() const = 0;

  virtual void Render() = 0;

protected:
  bool      m_IsEnabled;
  bool      m_IsStatic;

};


#endif // __RIGID_BODY_H_

// -- EOF

