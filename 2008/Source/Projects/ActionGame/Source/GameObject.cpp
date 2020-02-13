
#include "GameObject.h"


// ----------------------------------------------------------------------------
// Static initialisers
// ----------------------------------------------------------------------------
IMPLEMENT_TYPE_INFO(GameObject);


GameObject::GameObject()
: Parent()
{
  REF_COUNT_CTOR(GameObject);

  m_WorldTransform  = MatrixIdentity;
  m_LocalTransform  = MatrixIdentity;
  m_ParentTransform = MatrixIdentity;
}


GameObject::~GameObject()
{
  REF_COUNT_DTOR(GameObject);
}


void GameObject::Update(float deltaTime)
{
}


void GameObject::UpdateWorldTransform()
{
  m_WorldTransform.Multiply(m_ParentTransform, m_LocalTransform);
}


ObjectGlobal &ObjectGlobal::GetInstance()
{
  if (!s_pInstance)
  {
    s_pInstance = new ObjectGlobal();
    atexit(&ObjectGlobal::DestroyInstance);
  }

  return *s_pInstance;
}


void ObjectGlobal::DestroyInstance()
{
  delete s_pInstance;
  s_pInstance = NULL;
}


ObjectGlobal::ObjectGlobal()
: m_Count (0)
{
}


ObjectGlobal::~ObjectGlobal()
{
#if !FINAL_RELEASE
  if (!m_Objects.empty())
  {
    LOG_ERROR << "Game Objects still exist!!" << ENDLOG;
  }
#endif
}


uint ObjectGlobal::Register(Object *pObject)
{
  if (m_FreeList.empty())
  {
    uint id = m_Objects.size();

    m_Objects.push_back(pObject);

    m_Count++;
    return id;
  }
  else
  {
    uint id = m_FreeList.front();
    m_FreeList.pop_front();

    m_Objects[id] = pObject;

    m_Count++;
    return id;
  }
}


void ObjectGlobal::UnRegister(uint id)
{
  m_Objects[id] = NULL;
  m_Count--;
  m_FreeList.push_back(id);
}


void ObjectGlobal::Compact()
{
  // Move objects from the end of the list to fill empty slots in 
  // the front of the list to save memory.
}


uint ObjectGlobal::Next(uint id)
{
  if (id == INVALID_OBJECT_ID || id == LAST_OBJECT_ID)
  {
    return INVALID_OBJECT_ID;
  }

  id++;
  ASSERT(id <= m_Objects.size(), "Index out of range");

  while (true)
  {
    if (id == m_Objects.size())
    {
      return LAST_OBJECT_ID;
    }

    if (m_Objects[id] != NULL)
    {
      return id;
    }

    id++;
  }

  return INVALID_OBJECT_ID;
}


uint ObjectGlobal::Prev(uint id)
{
  if (id == INVALID_OBJECT_ID || id == FIRST_OBJECT_ID)
  {
    return INVALID_OBJECT_ID;
  }

  id--;
  while (true)
  {
    if (m_Objects[id] != NULL)
    {
      return id;
    }

    if (id == FIRST_OBJECT_ID)
    {
      return INVALID_OBJECT_ID;
    }

    id--;
  }

  return INVALID_OBJECT_ID;
}


Object *ObjectGlobal::Get(uint id)
{
  if (id == INVALID_OBJECT_ID || id == LAST_OBJECT_ID)
  {
    return NULL;
  }

  ASSERT(id < m_Objects.size(), "Index out of range");

  return m_Objects[id];
}


ObjectIterator ObjectGlobal::Begin()
{
  if (m_Objects.empty())
  {
    return ObjectIterator(INVALID_OBJECT_ID);
  }
  else
  {
    return ObjectIterator(FIRST_OBJECT_ID);
  }
}


ObjectIterator ObjectGlobal::End()
{
  return LAST_OBJECT_ID;
}


// -- EOF

