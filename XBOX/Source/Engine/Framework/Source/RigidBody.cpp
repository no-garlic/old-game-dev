
#include "RigidBody.h"
#include "PhysicsManager.h"


RigidBody::RigidBody()
{
  m_IsStatic  = true;
  m_IsEnabled = true;

  Physics.Register(this);
}


RigidBody::~RigidBody()
{
  Physics.UnRegister(this);
}


bool RigidBody::IsStatic() const
{
  return m_IsStatic;
}


bool RigidBody::IsEnabled() const
{
  return m_IsEnabled;
}


// -- EOF

