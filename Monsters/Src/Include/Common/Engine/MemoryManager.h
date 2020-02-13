// ----------------------------------------------------------------------------
// File: MemoryManager.h
// Desc: A memory manager class that provides seperate copies of memory for 
//       different frames in the render cycle. Each variable that needs to 
//       share data between the application, the culling, or the draw code
//       in your application should be declared as a DataFlux<T>.  Each data
//       flux holds a copy of memory for each of the different threads that
//       the rendered has created. When reading or writing the memory, the
//       current context must be passed into the DataFlux so the correct
//       version of the variable is accessed. This is done through the call
//       operator.
//
// Exam: // Create a Vector3 variable
//       DataFlux<Vector3> position;
//
//       // Done in the APP thread
//       position(APP) = Vector3(0.0f, 0.0f, 100.0f);
//
//       // Done in the CULL thread
//       if (Frustum.IsVisible(position(CULL)))
//
//       // Done in the DRAW thread
//       Matrix worldMatrix = Matrix::Translation(position(DRAW)); 
//
// Auth: Michael Petrou
// (C) Copyright: 2006
// ----------------------------------------------------------------------------
#ifndef __DATA_FLUX_H_
#define __DATA_FLUX_H_


// ----------------------------------------------------------------------------
// Includes
// ----------------------------------------------------------------------------
#include "Kernel/KernelInc.h"


// ----------------------------------------------------------------------------
// Forward declarations
// ----------------------------------------------------------------------------
template <class T> class DataFlux;


// ----------------------------------------------------------------------------
// Singleton accessor
// ----------------------------------------------------------------------------
#define MemoryManager MemoryHeapManager::GetInstance()


// ----------------------------------------------------------------------------
// Name: MemoryHeap (class)
// Desc: A memory heap holds a block of memory and splits it into a number of
//       equally sized sections. When a DataFlux allocates memory from the
//       memory heap, it is given a pointer to some memoey in the first section.
//       It is also given a stride, wich it appends to the memory pointer to
//       get to the other versions of the memory in the other sections.
// ----------------------------------------------------------------------------
class MemoryHeap
{
public:
  // --------------------------------------------------------------------------
  // Constructor and destructor
  // --------------------------------------------------------------------------
  MemoryHeap(unsigned int numProcesses, unsigned int bytesPerHeap);
  ~MemoryHeap();

public:
  // --------------------------------------------------------------------------
  // Allocate some memory, and return the stride of the memory heap or return
  // -1 if the heap has insufficient space to allocate the memory.
  // --------------------------------------------------------------------------
  int Alloc(unsigned char numBytes, unsigned char **ptr);

  // --------------------------------------------------------------------------
  // Copy from the app heap section to the draw heap section
  // --------------------------------------------------------------------------
  void Swap(unsigned int srcId, unsigned int destId);

  // --------------------------------------------------------------------------
  // Manage the linked list of heaps
  // --------------------------------------------------------------------------
  inline MemoryHeap *GetNext();
  inline void SetNext(MemoryHeap *pNext);

private:
  // --------------------------------------------------------------------------
  // Private members
  // --------------------------------------------------------------------------
  unsigned char  *m_Data;         // The data heap
  unsigned int    m_NumProcesses; // The number of processes (heap sections)
  unsigned int    m_Stride;       // The stride between the heap sections
  unsigned int    m_End;          // The end location of the first heap section
  unsigned int    m_Current;      // The next position to allocate from
  MemoryHeap     *m_pNext;        // The next heap in the linked list

}; // class MemoryHeap


// ----------------------------------------------------------------------------
// Name: MemoryHeapManager (class)
// Desc: Manages an array of heaps
// ----------------------------------------------------------------------------
class MemoryHeapManager
{
public:
  // --------------------------------------------------------------------------
  // Static singleton accessor
  // --------------------------------------------------------------------------
  static MemoryHeapManager &GetInstance();
  static void DestroyInstance();

private:
  // --------------------------------------------------------------------------
  // Constructor and Destructor
  // --------------------------------------------------------------------------
  MemoryHeapManager();
  ~MemoryHeapManager();

public:
  // --------------------------------------------------------------------------
  // Initialise the memory pools and the defaults
  // --------------------------------------------------------------------------
  void Init(unsigned int numProcesses, unsigned int bytesPerHeap);

  // --------------------------------------------------------------------------
  // Copy from the app heap to the draw heap
  // --------------------------------------------------------------------------
  void Swap(unsigned int srcId, unsigned int destId);

  // --------------------------------------------------------------------------
  // Allocate a data flux (ie, get a memory pointer)
  // --------------------------------------------------------------------------
  template <class T>
  inline void Alloc(DataFlux<T> *pDataFlux);

  // --------------------------------------------------------------------------
  // Deallocate the data flux (ie, return the memory)
  // --------------------------------------------------------------------------
  template <class T>
  inline void DeAlloc(DataFlux<T> *pDataFlux);

  // --------------------------------------------------------------------------
  // Get the number of processes
  // --------------------------------------------------------------------------
  inline int GetNumProcesses();

private:
  // --------------------------------------------------------------------------
  // Private types
  // --------------------------------------------------------------------------
  typedef std::multimap<unsigned int, unsigned char *>  MemoryMap;

  // --------------------------------------------------------------------------
  // Private members
  // --------------------------------------------------------------------------
  static MemoryHeapManager *s_pInstance;        // The singleton instance
  MemoryHeap               *m_pFirst;           // The first heap in the linked list
  MemoryHeap               *m_pCurrent;         // The current heap to allocate from
  unsigned int              m_NumProcesses;     // The number of processes
  unsigned int              m_BytesPerHeap;     // The size of each heap section
  MemoryMap                 m_ReturnedMemory;   // The array of returned memory

}; // class MemoryHeapManager


// ----------------------------------------------------------------------------
// Name: DataFlux (class)
// Desc: A class that holds a pointer to a number of variables and each can be 
//       accessed through the call operator
// ----------------------------------------------------------------------------
template <class T>
class DataFlux
{
public:
  // --------------------------------------------------------------------------
  // Constructor
  // --------------------------------------------------------------------------
  inline DataFlux();
  ~DataFlux();

  // --------------------------------------------------------------------------
  // Access operator
  // --------------------------------------------------------------------------
  inline T &operator()(unsigned int index);

  // --------------------------------------------------------------------------
  // Set all variables with the given value
  // --------------------------------------------------------------------------
  inline void Set(const T &value);

private:
  // --------------------------------------------------------------------------
  // Allow the heap manager to access our internals
  // --------------------------------------------------------------------------
  friend class MemoryHeapManager;

  // --------------------------------------------------------------------------
  // Private members
  // --------------------------------------------------------------------------
  unsigned char *m_pData;
  unsigned int   m_Stride;

}; // struct DataFlux


// ----------------------------------------------------------------------------
// Name: DataFlux<T>::DataFlux
// Temp: The data flux type
// Desc: Constructor
// ----------------------------------------------------------------------------
template <class T>
inline DataFlux<T>::DataFlux()
{
  MemoryManager.Alloc(this);
} // DataFlux


// ----------------------------------------------------------------------------
// Name: DataFlux<T>::~DataFlux
// Temp: The data flux type
// Desc: Destructor
// ----------------------------------------------------------------------------
template <class T>
inline DataFlux<T>::~DataFlux()
{
  MemoryManager.DeAlloc(this);
} // ~DataFlux


// ----------------------------------------------------------------------------
// Name: MemoryHeap::GetNext
// Desc: Get the next memory heap in the linked list
// Retn: MemoryHeap * - the heap
// ----------------------------------------------------------------------------
inline MemoryHeap *MemoryHeap::GetNext()
{
  return m_pNext;
} // GetNext


// ----------------------------------------------------------------------------
// Name: MemoryHeap::SetNext
// Desc: Set the next memory heap in the linked list
// Parm: MemoryHeap *pNext - the next heap
// ----------------------------------------------------------------------------
inline void MemoryHeap::SetNext(MemoryHeap *pNext)
{
  m_pNext = pNext;
} // SetNext


// ----------------------------------------------------------------------------
// Name: MemoryHeapManager::GetNumProcesses
// Desc: Get the number of processes that the memory heap is allocating for
// Retn: int - the number
// ----------------------------------------------------------------------------
inline int MemoryHeapManager::GetNumProcesses()
{
  return m_NumProcesses;
} // GetNumProcesses


// ----------------------------------------------------------------------------
// Name: MemoryHeapManager::Alloc
// Temp: The type that the flux holds
// Desc: Assign memory to the given flux
// Parm: DataFlux<T> *pDataFlux - the flux
// ----------------------------------------------------------------------------
template <class T>
inline void MemoryHeapManager::Alloc(DataFlux<T> *pDataFlux)
{
  // Check that we have initialised the memory manager
  if (!m_pFirst)
    throw std::bad_alloc();

  // Check if there is any recycled memory available
  MemoryMap::iterator memIter = m_ReturnedMemory.find(sizeof(T));
  if (memIter != m_ReturnedMemory.end())
  {
    // Assign the recycled memory to the flux
    pDataFlux->m_Stride = m_BytesPerHeap;
    pDataFlux->m_pData  = memIter->second;

    // Remove the record from the multimap
    m_ReturnedMemory.erase(memIter);
  } // if
  else
  {
    // Allocate memory from the current heap
    pDataFlux->m_Stride = m_pCurrent->Alloc(sizeof(T), reinterpret_cast<unsigned char **>(&(pDataFlux->m_pData)));

    // If -1 was returned then the current heap is out of memory
    if (pDataFlux->m_Stride == -1)
    {
      // Create a new heap and set it as the current heap
      MemoryHeap *newHeap = new MemoryHeap(m_NumProcesses, m_BytesPerHeap);
      m_pCurrent->SetNext(newHeap);
      m_pCurrent = newHeap;

      // Allocate memory from the new heap
      pDataFlux->m_Stride = m_pCurrent->Alloc(sizeof(T), reinterpret_cast<unsigned char **>(&(pDataFlux->m_pData)));

      // If that fails it's possible that the size of the memory requested is greater than
      // the heap size we are using (m_BytesPerHeap).
      if (pDataFlux->m_Stride == -1)
        throw std::bad_alloc(_MESG("Cant allocate memory. Check that you are allocating less than m_BytesPerHeap."));
    } // if
  } // else
} // Alloc


// ----------------------------------------------------------------------------
// Name: MemoryHeapManager::DeAlloc
// Temp: The type that the flux holds
// Desc: Return memory from the given flux
// Parm: DataFlux<T> *pDataFlux - the flux
// ----------------------------------------------------------------------------
template <class T>
inline void MemoryHeapManager::DeAlloc(DataFlux<T> *pDataFlux)
{
  // Get the size of the memory and a pointer to the memory
  unsigned int numBytes = sizeof(T);
  unsigned char *ptr    = pDataFlux->m_pData;

  // Add the memory to the returned list
  m_ReturnedMemory.insert(std::make_pair(numBytes, ptr));

  // For safety, set the data flux pointer to NULL
  pDataFlux->m_pData = 0;
} // DeAlloc


// ----------------------------------------------------------------------------
// Name: DataFlux<T>::operator
// Temp: The data flux type
// Desc: get access by reference to one of the variables that the flux holds
// Parm: unsigned int index - the process index
// Retn: T & - the variable reference
// ----------------------------------------------------------------------------
template <class T>
inline T &DataFlux<T>::operator()(unsigned int index)
{
  return *(reinterpret_cast<T *> (m_pData + (m_Stride * index)));
} // operator()


// ----------------------------------------------------------------------------
// Name: DataFlux<T>Set
// Temp: The data flux type
// Desc: Set all variables with the given value
// Parm: const T &value - the value
// ----------------------------------------------------------------------------
template <class T>
inline void DataFlux<T>::Set(const T &value)
{
  for (int i = 0; i < MemoryManager.GetNumProcesses(); i++)
  {
    (*(reinterpret_cast<T *> (m_pData + (m_Stride * i)))) = value;
  } // for
} // Set


#endif // __DATA_FLUX_H_

// -- EOF

