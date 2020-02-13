
#ifndef __GAME_OBJECT_H_
#define __GAME_OBJECT_H_


#include "libEngine.h"


// ----------------------------------------------------------------------------
// The base game objct class
// ----------------------------------------------------------------------------
class GameObject : public Object, private Unique
{
public:
  DECLARE_TYPE_INFO(Object);

  GameObject();
  virtual ~GameObject();

  void SetName(const String &name) { m_Name = name; }
  const String &GetName() const    { return m_Name; }

  inline void SetParentTransform(const Matrix &matrix);
  inline void SetLocalTransform(const Matrix &matrix);

  const Matrix &GetWorldTransform() const  { return m_WorldTransform;  }
  const Matrix &GetLocalTransform() const  { return m_LocalTransform;  }
  const Matrix &GetParentTransform() const { return m_ParentTransform; }

  virtual void Update(float deltaTime);

protected:
  virtual void UpdateWorldTransform();

  String  m_Name;
  Matrix  m_WorldTransform;   // The world transform (combined parent and local)
  Matrix  m_LocalTransform;   // The local transform of this object
  Matrix  m_ParentTransform;  // The transform of the parent

};


void GameObject::SetParentTransform(const Matrix &matrix)
{
  m_ParentTransform = matrix;
  UpdateWorldTransform();
}


void GameObject::SetLocalTransform(const Matrix &matrix)
{
  m_LocalTransform = matrix;
  UpdateWorldTransform();
}


#endif // __GAME_OBJECT_H_

// -- EOF


