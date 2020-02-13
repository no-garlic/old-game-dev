// ----------------------------------------------------------------------------
// File: StdMemory.h
// Desc: Memory routines
// Auth: Michael Petrou
// (C) Copyright: 2006
// ----------------------------------------------------------------------------
#ifndef _STD_MEMORY_H_
#define _STD_MEMORY_H_


// ----------------------------------------------------------------------------
// Includes
// ----------------------------------------------------------------------------
#include "stdType.h"


// ----------------------------------------------------------------------------
// The ASSERT function macro, which may be made to either log an error or show
// a message dialog.
// ----------------------------------------------------------------------------
#ifdef _DEBUG
#include <crtdbg.h>

#ifdef ASSERT
#undef ASSERT
#endif // ASSERT

#define NULL_ASSERT(x) ASSERT(x, "##x is NULL")
#define DEBUG_BREAK ASSERT(NULL, "Debug Break")
#define CHECK(check, statement) { if (!(check)) { DEBUG_BREAK; statement; } }

#ifdef NO_ASSERT
#define ASSERT(expression, msg)
#elif defined ASSERT_DIALOG
#define ASSERT(expression, msg) if (!(expression)) { Assert::FailDialog(#expression, msg, __FILE__, __LINE__); }
#else // !NO_ASSERT && !ASSERT_DIALOG
#define ASSERT(expression, msg) if (!(expression)) { LOG_ERROR << msg << ENDLOG; _CrtDbgBreak(); }
#endif // !NO_ASSERT && !ASSERT_DIALOG

#else // !_DEBUG
#ifdef ASSERT
#undef ASSERT
#endif // !ASSERT
#define ASSERT(expression, msg)
#define NULL_ASSERT(x)
#define CHECK(check, statement) { if (!(check)) { statement; } }
#define DEBUG_BREAK
#endif // !_DEBUG


// ----------------------------------------------------------------------------
// Remove the Assert definition
// ----------------------------------------------------------------------------
#ifdef _DEBUG

#ifdef ASSERT_DIALOG
#ifdef Assert
#undef Assert

#endif // Assert


// ----------------------------------------------------------------------------
// Name: Assert (namespace)
// Desc: The Assert namespace
// ----------------------------------------------------------------------------
namespace Assert
{
  // --------------------------------------------------------------------------
  // Name: FailDialog
  // Desc: Show a fail dialog
  // Parm: const char *expression - the failed expression
  // Parm: const char *message    - the message
  // Parm: const char *file       - the file
  // Parm: int line               - the line
  // --------------------------------------------------------------------------
  inline void FailDialog(const char *expression, const char *message, const char *file, int line)
  {
    char buffer[1024];
    sprintf(buffer, "%s:%d\n%s\n%s\nWould You Like To Break?", file, line, message, expression);
    if (MessageBox(0, buffer, "Assertion Failed", MB_ICONERROR | MB_YESNO | MB_TOPMOST) == IDYES)
      _CrtDbgBreak();
  } // FailDialog
}; // namespace Assert


#endif // ASSERT_DIALOG
#endif // _DEBUG


// ----------------------------------------------------------------------------
// Name: StridePointer
// Desc: Interface to a pointer that allows interation to occur using a stride.
// ----------------------------------------------------------------------------
template <class T>
class StridePointer
{
public:
  // ------------------------------------------------------------------------
  // Constructors
  // ------------------------------------------------------------------------
  StridePointer() : m_pdata(0), m_stride(0) {}
  StridePointer(ubyte stride, ubyte offset, void *pdata) : m_pdata((ubyte *)pdata + offset), m_stride(stride) {}

  // ------------------------------------------------------------------------
  // Pointer operators to manipulate and read the m_pdata pointer using the
  // stride of the data.
  // ------------------------------------------------------------------------
  operator T ()                         { return *((T*)(m_pdata)); }
  T &operator * ()                      { return *((T*)(m_pdata)); }
  T *operator ->()                      { return  ((T*)(m_pdata)); }
  T &operator [](uint idx)              { return *((T*)(m_pdata + (idx * m_stride)));   }
  const T &operator [](uint idx) const  { return *((T*)(m_pdata + (idx * m_stride)));   }
  T &operator ++()                      { m_pdata += m_stride; return *((T*)(m_pdata)); }
  T &operator --()                      { m_pdata -= m_stride; return *((T*)(m_pdata)); }
  operator bool()                       { return (m_pdata != 0); }

private:
  // ------------------------------------------------------------------------
  // Private members
  // ------------------------------------------------------------------------
  uchar   *m_pdata;
  ubyte    m_stride;

}; // class StridePointer


// ----------------------------------------------------------------------------
// Macro for deleting and nulling
// ----------------------------------------------------------------------------
#define SafeDelete(x) { delete x; x = NULL; }


// ----------------------------------------------------------------------------
// Name: StackDelete (struct)
// Desc: Delete an object (using delete) when the stack goes out of scope
// ----------------------------------------------------------------------------
template <typename T>
struct StackDelete
{
  StackDelete(T *obj) : obj(obj) {}
  ~StackDelete() { delete obj; }
  T *obj;
}; // struct StackDelete


// ----------------------------------------------------------------------------
// Name: AutoArray (struct)
// Desc: An array that acts like a normal array that gets deleted when the stack
//       goes out of scope
// ----------------------------------------------------------------------------
template <class T>
struct AutoArray
{
public:
  explicit AutoArray(int count) { pdata = (T *) new ubyte[sizeof(T) * count]; }
  ~AutoArray()                  { delete[] pdata; }
  T *get()                      { return pdata; }
  operator T*()                 { return pdata; }

private:
  T *pdata;
}; // struct AutoArray


// ----------------------------------------------------------------------------
// Name: SafeRelease
// Temp: The interface type we are releasing
// Desc: The Right Way to release our COM interfaces. If they're still valid, 
//       release them, then invalidate them.
// Parm: T& iface - the interface to release
// ----------------------------------------------------------------------------
template <class T>
inline void SafeRelease(T& iface)
{
  if (iface)
  {
    iface->Release();
    iface = 0;
  } // if
} // SafeRelease


// ----------------------------------------------------------------------------
// Stick this object on the stack and it will release the supplied pointer when 
// the stack is deleted.
// ----------------------------------------------------------------------------
struct StackRelease
{
  template <typename T>
  StackRelease(T ptr) : ptr(ptr) {}
  ~StackRelease() { SafeRelease<IUnknown *>(ptr); }
  IUnknown *ptr;
}; // struct StackRelease



// ----------------------------------------------------------------------------
// Name: AutoZero  (struct)
// Temp: The DirectX structure type we are going to zero-out
// Desc: This struct takes care of the annoying gruntwork of having to zero-out 
//       and set the size parameter of our Windows and DirectX structures.
// ----------------------------------------------------------------------------
template <class T>
struct AutoZero : public T
{
  AutoZero()
  {
    memset(this, 0, sizeof(T));
    dwSize = sizeof(T);
  } // AutoZero
}; // struct AutoZero


// --------------------------------------------------------------------
// Name: RefCounted (class)
// Desc: Reference counting base class
// --------------------------------------------------------------------
class RefCounted
{
public:
  // ----------------------------------------------------------------
  // Constructor and destructor
  // ----------------------------------------------------------------
  RefCounted()                        : m_ref_ctr(0) {}
  RefCounted(const RefCounted &other) : m_ref_ctr(0) {}
  virtual ~RefCounted()                              {}

  // ----------------------------------------------------------------
  // Increment the reference count
  // ----------------------------------------------------------------
  int Ref() const { return ++m_ref_ctr; }

  // ----------------------------------------------------------------
  // Decrement the reference count
  // ----------------------------------------------------------------
  void UnRef() const
  {
    m_ref_ctr--; 
    if (m_ref_ctr <= 0) 
      delete this; 
  } // UnRef

  // ----------------------------------------------------------------
  // Get the reference count
  // ----------------------------------------------------------------
  int GetRefCount() const { return m_ref_ctr; }

protected:
  // --------------------------------------------------------------------------
  // Set the reference count
  // --------------------------------------------------------------------------
  void SetRefCount(uint ref) const { m_ref_ctr = ref; }

private:
  // ----------------------------------------------------------------
  // Privates for this class
  // ----------------------------------------------------------------
  mutable int m_ref_ctr;  // The reference count

}; // class RefCounted


// --------------------------------------------------------------------
// Name: SafeUnRef
// Desc: Derefernces an object, but checks that teh object exists first 
//       (is not null)
// Parm: RefCounted *pobj - the object to unref
// Retn: int      - the final reference count, or -1 if the object does 
//       not exist
// --------------------------------------------------------------------
inline int SafeUnRef(const RefCounted *pobj)
{
  if (pobj)
  {
    int refCount = pobj->GetRefCount();
    pobj->UnRef();
    return refCount - 1;
  }

  return -1;
} // SafeUnref


// --------------------------------------------------------------------
// Name: SafeRef
// Desc: Refernces an object, but checks that teh object exists first 
//       (is not null)
// Parm: RefCounted *pobj - the object to ref
// Retn: int      - the reference count, or -1 if the object does 
//       not exist
// --------------------------------------------------------------------
inline int SafeRef(const RefCounted *pobj)
{
  if (pobj)
    return pobj->Ref();
  return -1;
} // Saferef


// ----------------------------------------------------------------------------
// Name: AutoRefArray (class)
// Desc: An array that when you add items they are reference counted.  The only 
//       way to decrement the reference count of the items is to destroy the 
//       array
// ----------------------------------------------------------------------------
class AutoRefArray
{
public:
  AutoRefArray() 
  {
  } // AutoRefArray

  ~AutoRefArray()
  {
    for (size_t i = 0; i < m_array.size(); i++)
      m_array[i]->UnRef();
  } // ~AutoRefArray

  void Add(RefCounted *pobj)
  {
    if (pobj)
    {
      pobj->Ref();
      m_array.push_back(pobj);
    } // if
  } // Add

private:
  std::vector<RefCounted *> m_array;

}; // class AutoRefArray



template <typename T>
inline void UnRefArray(Array<T> &array, bool clearArray)
{
  Array<T>::iterator iter(array.begin()), end(array.end());
  for (; iter != end; ++iter)
    SafeUnRef(*iter);

  if (clearArray)
    array.clear();
} // UnRefArray


// ----------------------------------------------------------------------------
// Name: UserData (class)
// Desc: An array of reference counted items
// ----------------------------------------------------------------------------
class UserData
{
public:
  // --------------------------------------------------------------------------
  // Constructor
  // --------------------------------------------------------------------------
  UserData() 
  {
  } // UserData

  // --------------------------------------------------------------------------
  // Destructor
  // --------------------------------------------------------------------------
  virtual ~UserData()
  {
    Map<uint, RefCounted *>::iterator iter = m_user_data.begin();
    for (; iter != m_user_data.end(); ++iter)
      SafeUnRef(iter->second);

    m_user_data.clear();
  } // ~UserData


  // --------------------------------------------------------------------------
  // Name: SetUserData
  // Desc: Set the data for the slot
  // Parm: uint slot        - the slot
  // Parm: RefCounted *pdata - the data
  // --------------------------------------------------------------------------
  void SetUserData(uint slot, RefCounted *pdata)
  {
    Map<uint, RefCounted *>::iterator iter = m_user_data.find(slot);
    if (iter != m_user_data.end())
      SafeUnRef(iter->second);

    SafeRef(pdata);
    m_user_data[slot] = pdata; 
  } // SetUserData


  // --------------------------------------------------------------------------
  // Name: GetUserData
  // Desc: Get the data from the slot
  // Parm: uint slot  - the slot
  // Retn: RefCounted * - the data
  // --------------------------------------------------------------------------
  RefCounted *GetUserData(uint slot)
  { 
    Map<uint, RefCounted *>::iterator iter = m_user_data.find(slot);
    if (iter == m_user_data.end())
      return 0;

    return iter->second;
  } // GetUserData

private:
  // --------------------------------------------------------------------------
  // Private members
  // --------------------------------------------------------------------------
  Map<uint, RefCounted *>  m_user_data;

}; // class UserData


// ----------------------------------------------------------------------------
// Name: CreateUsingNew (struct)
// Temp: The type that is created and destroyed.
// Desc: Implementation of the creation policy used by SingletonHolder. Creates 
//       objects using a straight call to the new operator.
// ----------------------------------------------------------------------------
template <class T>
struct CreateUsingNew
{
  // ------------------------------------------------------------------------
  // Create using new, destroy using delete
  // ------------------------------------------------------------------------
  static T    *Create()       { return new T; }
  static void Destroy(T *p)   { delete p; }
}; // struct CreateUsingNew


// ----------------------------------------------------------------------------
// Name: CreateUsingMalloc (struct)
// Temp: The type that is created and destroyed.
// Desc: Implementation of the creation policy used by SingletonHolder. Creates 
//       objects using a call to std::malloc, followed by a call to the 
//       placement new operator
// ----------------------------------------------------------------------------
template <class T>
struct CreateUsingMalloc
{
  // ------------------------------------------------------------------------
  // Create using malloc followed by placement new
  // ------------------------------------------------------------------------
  static T *Create()
  {
    // Allocate the memory
    void *p = std::malloc(sizeof(T));
    if (!p)
      return 0;

    // Construct the object
    return new(p) T;
  } // Create


  // ------------------------------------------------------------------------
  // Manually call the constructor, then free the memory using free
  // ------------------------------------------------------------------------
  static void Destroy(T *p)
  {
    p->~T();
    std::free(p);
  } // Destroy
}; // struct CreateUsingMalloc


// ----------------------------------------------------------------------------
// Name: CreateStatic (struct)
// Temp: The type that is created and destroyed.
// Desc: Creates an object in static memory. Implementation is slightly non-
//       portable because it uses the MaxAlign trick (a union of all types to 
//       ensure proper memory alignment). This trick is non-portable in theory, 
//       but highly portable in practice.
// ----------------------------------------------------------------------------
template <class T>
struct CreateStatic
{
  // ------------------------------------------------------------------------
  // Create a union to align memory
  // ------------------------------------------------------------------------
  union MaxAlign
  {
    char            m_t[sizeof(T)];
    short int       m_short_int;
    int             m_int;
    long int        m_long_int;
    float           m_float;
    double          m_double;
    long double     m_long_double;
    struct          Test;
    int             Test::* m_pmember;
    int            (Test::*m_pmember_func)(int);
  }; // MaxAlign

  // ------------------------------------------------------------------------
  // Create on the stack (static) and then call placement new
  // ------------------------------------------------------------------------
  static T *Create()
  {
    static MaxAlign s_static_memory;

    // Call the constructor using placement new
    return new(&s_static_memory) T;
  } // Create

  // ------------------------------------------------------------------------
  // Call the destructor - when the stack disappears the memory will be 
  // deallocated
  // ------------------------------------------------------------------------
  static void Destroy(T *p)
  {
    p->~T();
  } // Destroy
}; // struct CreateStatic


// ----------------------------------------------------------------------------
// Name: SingletonHolder (class)
// Temp: T              - the object type to make a singleton instance of.
// Temp: CreationPolicy - the policy used to construct the songleton.  Must
//       have the Create and Destroy functions.
// Desc: Provides singleton amenities for type T. To protect that type from 
//       spurious instantiations, you have to protect it yourself.
// ----------------------------------------------------------------------------
template <typename T, class CreationPolicy>
class SingletonHolder
{
public:
  // ------------------------------------------------------------------------
  // Get the object by reference or pointer
  // ------------------------------------------------------------------------
  static T &Instance();
  static T *GetPtr();


  // ------------------------------------------------------------------------
  // Make the instance and destroy the instance - note these are called 
  // implicitly but may be called explicitly if a specific order of operation 
  // is required.'
  // ------------------------------------------------------------------------
  static void MakeInstance();
  static void DestroyInstance();

private:
  // ------------------------------------------------------------------------
  // Protected constructor so that we can't try to instantiate it manually
  // ------------------------------------------------------------------------
  SingletonHolder();
  SingletonHolder<T, CreationPolicy> &operator=(const SingletonHolder<T, CreationPolicy> &other);
  explicit SingletonHolder(const SingletonHolder<T, CreationPolicy> &other);


  // ----------------------------------------------------------------------------
  // The data pointer type
  // ----------------------------------------------------------------------------
  typedef T *PtrInstanceType;


  // ------------------------------------------------------------------------
  // Privates for this class
  // ------------------------------------------------------------------------
  static PtrInstanceType  s_pinstance;    // The object instance
  static bool             s_destroyed;    // Is the instance destroyed
}; // class SingletonHolder



// ----------------------------------------------------------------------------
// Instantiate the static data
// ----------------------------------------------------------------------------
template <class T, class C>
typename SingletonHolder<T, C>::PtrInstanceType SingletonHolder<T, C>::s_pinstance = 0;
template <class T, class C>
bool SingletonHolder<T, C>::s_destroyed = false;


// ----------------------------------------------------------------------------
// Name: CreationPolicy>::Instance
// Temp: T              - the object type to make a singleton instance of.
// Temp: CreationPolicy - the policy used to construct the songleton.  Must
//       have the Create and Destroy functions.
// Desc: Returns a reference to the singleton class. If the class has not yet 
//       been created it is created now.
// Retn: T &SingletonHolder<T, - A reference to the singleton
// ----------------------------------------------------------------------------
template <class T, class CreationPolicy>
inline T &SingletonHolder<T, CreationPolicy>::Instance()
{
  if (!s_pinstance)
    MakeInstance();

  return *s_pinstance;
} // Instance


// ----------------------------------------------------------------------------
// Name: CreationPolicy>::GetPtr
// Temp: T              - the object type to make a singleton instance of.
// Temp: CreationPolicy - the policy used to construct the songleton.  Must
//       have the Create and Destroy functions.
// Desc: Returns a pointer to the singleton class. If the class has not yet been
//       created it returns 0.
// Retn: T *SingletonHolder<T, - A pointer to the singleton
// ----------------------------------------------------------------------------
template <class T, class CreationPolicy>
inline T *SingletonHolder<T, CreationPolicy>::GetPtr()
{
  return s_pinstance;
} // GetPtr


// ----------------------------------------------------------------------------
// Name: CreationPolicy>::MakeInstance
// Temp: T              - the object type to make a singleton instance of.
// Temp: CreationPolicy - the policy used to construct the singleton.  Must
//       have the Create and Destroy functions.
// Desc: Creates an instance of the singleton object
// ----------------------------------------------------------------------------
template <class T, class CreationPolicy>
inline void SingletonHolder<T, CreationPolicy>::MakeInstance()
{
  if (!s_pinstance)
  {
    s_destroyed = false;
    s_pinstance = CreationPolicy::Create();

    // Reigster with atexit to ensure destruction. If we manually
    // destroy then these extra calls to DestroyInstance will just
    // be without effect
    atexit(&SingletonHolder<T, CreationPolicy>::DestroyInstance);
  } // if
} // MakeInstance


// ----------------------------------------------------------------------------
// Name: CreationPolicy>::DestroyInstance
// Temp: T              - the object type to make a singleton instance of.
// Temp: CreationPolicy - the policy used to construct the singleton.  Must
//       have the Create and Destroy functions.
// Desc: Destroys the singleton instance
// ----------------------------------------------------------------------------
template <class T, class CreationPolicy>
inline void SingletonHolder<T, CreationPolicy>::DestroyInstance()
{
  // Check that we aren't already destroyed
  if (!s_destroyed)
  {
    CreationPolicy::Destroy(s_pinstance);
    s_pinstance = 0;
    s_destroyed = true;
  } // if
} // DestroyInstance


// ----------------------------------------------------------------------------
// Name: Unique (class)
// Desc: A base class for all classes that should not be copied through a copy 
//       constructor or through assignment, making the class unique. Such non-
//       copyable classes should be derived privately from the Unique class.
// ----------------------------------------------------------------------------
class Unique
{
protected:
  // ------------------------------------------------------------------------
  // Constructor and destructor
  // ------------------------------------------------------------------------
  Unique() {}
  virtual ~Unique() {}

private:
  // ------------------------------------------------------------------------
  // Private copy constructor and assignment operator
  // ------------------------------------------------------------------------
  Unique           (const Unique &);
  const Unique &operator=(const Unique &);
}; // class Unique


// ----------------------------------------------------------------------------
// Name: NoInstance (class)
// Desc: A base class for all classes that should not be instantiated - for
//       example a static factory.
// ----------------------------------------------------------------------------
class NoInstance
{
public:
  // ------------------------------------------------------------------------
  // Public destructor
  // ------------------------------------------------------------------------
  virtual ~NoInstance() {}


private:
  // ------------------------------------------------------------------------
  // Private constructor
  // ------------------------------------------------------------------------
  NoInstance() {}

}; // class NoInstance


#endif // _STD_MEMORY_H_

// -- EOF

