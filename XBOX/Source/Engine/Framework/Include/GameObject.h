
#ifndef __GAME_OBJECT_H_
#define __GAME_OBJECT_H_


#include "libRenderExt.h"
#include "GameObjectInterfaceId.h"
#include "Object.h"


// ----------------------------------------------------------------------------
// Forward declaration
// ----------------------------------------------------------------------------
class GameObjectInterface;


// ----------------------------------------------------------------------------
// The base game objct class
// ----------------------------------------------------------------------------
class GameObject : public Object
{
public:
  DECLARE_TYPE_INFO(Object);

  GameObject();
  virtual ~GameObject();

  virtual bool Init() = 0;
  virtual void Shutdown();

  void SetName(const String &name) { m_Name = name; }
  const String &GetName() const    { return m_Name; }

  inline void SetParentTransform(const Matrix &matrix);
  inline void SetLocalTransform(const Matrix &matrix);

  const Matrix &GetWorldTransform() const  { return m_WorldTransform;  }
  const Matrix &GetLocalTransform() const  { return m_LocalTransform;  }
  const Matrix &GetParentTransform() const { return m_ParentTransform; }

  template <class T>
  inline T *GetInterface() { return dyn_cast<T>(m_pInterfaces[T::ID]); }

  template <class T>
  inline const T *GetInterface() const { return dyn_cast<T>(m_pInterfaces[T::ID]); }

  virtual void Update(float deltaTime);

protected:
  template <class T>
  inline bool CreateInterface();

  virtual void UpdateWorldTransform();

  String  m_Name;
  Matrix  m_WorldTransform;   // The world transform (combined parent and local)
  Matrix  m_LocalTransform;   // The local transform of this object
  Matrix  m_ParentTransform;  // The transform of the parent

  GameObjectInterface *m_pInterfaces[GOI_MAX];

};


template <class T>
inline bool GameObject::CreateInterface()
{
  ASSERT(T::ID < GOI_MAX, "Interface ID out of range");

  if (m_pInterfaces[T::ID] != NULL)
  {
    LOG_ERROR << "Cannot create multiple interfaces of the same type: " << T::ID << ENDLOG;
    return false;
  }

  T *pInterface = new T();
  pInterface->SetObject(this);

  if (!pInterface->Init())
  {
    delete pInterface;
    LOG_ERROR << "Failed to initialise the interface of type: " << T::ID << ENDLOG;
    return false;
  }
        
  m_pInterfaces[T::ID] = pInterface;
  return true;
}


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


