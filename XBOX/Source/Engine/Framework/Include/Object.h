
#ifndef __OBJECT_H_
#define __OBJECT_H_


#include "libStandard.h"


// ----------------------------------------------------------------------------
// Forward declaration
// ----------------------------------------------------------------------------
class Object;
class ObjectGlobal;
class ObjectIterator;


// ----------------------------------------------------------------------------
// Object iterator defines
// ----------------------------------------------------------------------------
#define INVALID_OBJECT_ID   0xFFFFFFFF
#define LAST_OBJECT_ID      0xFFFFFFFE
#define FIRST_OBJECT_ID     0x00000000


// ----------------------------------------------------------------------------
// The global game object amnager instance
// ----------------------------------------------------------------------------
#define ObjectManager ObjectGlobal::GetInstance()


// ----------------------------------------------------------------------------
// Class Type Info for determining class types and sub types
// ----------------------------------------------------------------------------
class TypeInfo
{
public:
  inline TypeInfo(const TypeInfo *pParentTypeInfo, const char *pClassName)
    : m_pName(pClassName)
  {
    m_pParentTypeInfo = pParentTypeInfo;
  }

  const TypeInfo     *m_pParentTypeInfo;
  const char *const   m_pName;
};


// ----------------------------------------------------------------------------
// The macro must be the first thing in each class (header file)
// ----------------------------------------------------------------------------
#define DECLARE_TYPE_INFO(PARENTCLASS) \
  static TypeInfo s_TypeInfo; \
  typedef PARENTCLASS Parent; \
  virtual const TypeInfo *GetTypeInfo() const { return &s_TypeInfo; }


// ----------------------------------------------------------------------------
// The macro must be at the top the cpp file
// ----------------------------------------------------------------------------
#define IMPLEMENT_TYPE_INFO(CLASS) \
  TypeInfo CLASS::s_TypeInfo(&CLASS::Parent::s_TypeInfo, (#CLASS));


// ----------------------------------------------------------------------------
// Static cast that uses the type info to determine type compatibility
// ----------------------------------------------------------------------------
template<class TO, class FROM>
inline TO *dyn_cast(FROM * pFrom)
{
  if (pFrom)
  {
    const TypeInfo *pTypeInfo = pFrom->GetTypeInfo();
    for(;;)
    {
      if(pTypeInfo == &TO::s_TypeInfo)
      {
        return static_cast<TO *>(pFrom);
      }
      if (pTypeInfo->m_pParentTypeInfo == pTypeInfo)
        break;

      pTypeInfo = pTypeInfo->m_pParentTypeInfo;
    }
  }
  return NULL;
}


// ----------------------------------------------------------------------------
// Base object type
// ----------------------------------------------------------------------------
class Object
{
public:
  DECLARE_TYPE_INFO(Object);

  Object();
  virtual ~Object();

  uint GetId() const { return m_Id; }

private:
  Object(const Object &other);
  Object &operator=(const Object &other);

  uint m_Id;

};


class ObjectIterator
{
public:
  inline ObjectIterator(uint id = INVALID_OBJECT_ID);
  inline ~ObjectIterator();

  inline Object *Resolve();
  inline const Object *Resolve() const;

  inline Object &operator*();
  inline const Object &operator*() const;
  inline Object *operator->();
  inline const Object *operator->() const;

  inline void operator++();
  inline void operator--();

  inline bool IsValid() const;

  inline bool operator==(const ObjectIterator &other) const;
  inline ObjectIterator &operator=(const ObjectIterator &other);

private:
  uint m_Id;

};


class ObjectGlobal
{
public:
  // --------------------------------------------------------------------------
  // Static singleton accessor
  // --------------------------------------------------------------------------
  static ObjectGlobal &GetInstance();
  static void DestroyInstance();

  uint GetCount() const { return m_Count; }

  ObjectIterator Begin();
  ObjectIterator End();

  void Compact();

private:
  // --------------------------------------------------------------------------
  // Constructor and destructor
  // --------------------------------------------------------------------------
  ObjectGlobal();
  ~ObjectGlobal();

  friend class Object;
  friend class ObjectIterator;

  uint Register(Object *pObject);
  void UnRegister(uint id);

  uint Next(uint id);
  uint Prev(uint id);
  Object *Get(uint id);

  Array<Object *>       m_Objects;
  List<uint>            m_FreeList;
  uint                  m_Count;
  static ObjectGlobal  *s_pInstance;

};



ObjectIterator::ObjectIterator(uint id)
: m_Id  (id)
{
}


ObjectIterator::~ObjectIterator()
{
}


Object *ObjectIterator::Resolve()
{
  return ObjectManager.Get(m_Id);
}


void ObjectIterator::operator++()
{
  m_Id = ObjectManager.Next(m_Id);
}


void ObjectIterator::operator--()
{
  m_Id = ObjectManager.Prev(m_Id);
}


bool ObjectIterator::IsValid() const
{
  return m_Id != INVALID_OBJECT_ID;
}


bool ObjectIterator::operator==(const ObjectIterator &other) const
{
  return m_Id == other.m_Id;
}


ObjectIterator &ObjectIterator::operator=(const ObjectIterator &other)
{
  m_Id = other.m_Id;
  return *this;
}


inline Object &ObjectIterator::operator*()
{
  Object *pObject = ObjectManager.Get(m_Id);
  NULL_ASSERT(pObject);
  return *pObject;
}


inline const Object &ObjectIterator::operator*() const
{
  Object *pObject = ObjectManager.Get(m_Id);
  NULL_ASSERT(pObject);
  return *pObject;
}


inline Object *ObjectIterator::operator->()
{
  return ObjectManager.Get(m_Id);
}


inline const Object *ObjectIterator::operator->() const
{
  return ObjectManager.Get(m_Id);
}



#endif // __OBJECT_H_

// -- EOF

